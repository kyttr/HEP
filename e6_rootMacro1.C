/*
 * aim of this ROOT macro
 * 3.".root" dosyası --> MakeClass
        in each "event" : 
        maxPT(e) --> histogram (eta,phi,PT)
        maxPT(mu) --> histogram
        maxPT(jet) --> histogram
        2. maxPT(jet)  (ikinci en çok PT)--> histogram
 * 
 * I adopted this code from the following file:
 * /home/kaya/Documents/particle-physics-kaya/Delphes/Delphes-3.0.5/examples/Example1.C
 * 
 * how to run file:
 * root -l examples/e6_rootMacro1.C\(\"delphes_output.root\"\)
 */

//#include <root/TObjArray.h>
#include <math.h>
//#include <cmath>
#include <stdlib.h>
//#include <root/TH1.h>
//#include <root/TFile.h>


//------------------------------------------------------------------------------

void e6_rootMacro1(const char *inputFile) {
    gSystem->Load("libDelphes");

    // Create chain of root trees
    TChain chain("Delphes");
    chain.Add(inputFile);

    // Create object of class ExRootTreeReader
    ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);
    Long64_t numberOfEntries = treeReader->GetEntries();


    string histoFile_str = "e6_rootMacro1.root";
    // TFile constructor accepts type "const char*"
    const char* histoFile_char = histoFile_str.c_str();
    // overwrite existing ".root" file
    TFile f(histoFile_char, "recreate");

    // number of particles in an event
    Long64_t numElectrons = -1;
    Long64_t numMuons = -1;
    Long64_t numJets = -1;

    Double_t maxPT = -1;
    Double_t max2ndPT = 0; // 2nd highest PT
    Double_t currentPT = 0; // initially currentPT>maxPT so that first particle in the loop will have max. PT

    Double_t maxEta = -1;
    Double_t currentEta = 0;
    Double_t maxPhi = -1;
    Double_t currentPhi = 0;

    // Get pointers to branches used in this analysis
    TClonesArray *branchElectron = treeReader->UseBranch("Electron");
    TClonesArray *branchMuon = treeReader->UseBranch("Muon");
    TClonesArray *branchJet = treeReader->UseBranch("Jet");

    // Book histograms
    Double_t histMaxPT_upper=600000.0;
    Double_t histMaxPT_jet_upper=1000000.0;
    TH1 *histMaxPT_electron = new TH1F("MaxPT_electron", "maximum of electron P_{T}", 100, 0.0, histMaxPT_upper);
    TH1 *histMaxEta_electron = new TH1F("MaxPT_Eta", "maximum of electron abs(Eta)", 100, 0.0, 4);
    TH1 *histMaxPhi_electron = new TH1F("MaxPT_Phi", "maximum of electron abs(Phi)", 100, 0.0, 4);
    TH1 *histMaxPT_muon = new TH1F("MaxPT_muon", "maximum of muon P_{T}", 100, 0.0, histMaxPT_upper);
    TH1 *histMaxPT_jet = new TH1F("MaxPT_jet", "maximum of jet P_{T}", 100, 0.0, histMaxPT_jet_upper);
    TH1 *hist2ndMaxPT_jet = new TH1F("Max2ndPT_jet", "2nd highest of jet P_{T}", 100, 0.0, histMaxPT_jet_upper);

    Electron *electron;
    Muon *muon;
    Jet *jet;

    // Loop over all events
    for (Int_t entry = 0; entry < numberOfEntries; ++entry) {
        // Load selected branches with data from specified event
        treeReader->ReadEntry(entry);

        numElectrons = branchElectron->GetEntries();
        numMuons = branchMuon->GetEntries();
        numJets = branchJet->GetEntries();

        maxPT = -1;
        currentPT = 0;
        maxEta = -1;
        currentEta = 0;
        maxPhi = -1;
        currentPhi = 0;
        // loop over electrons in the event
        for (int i = 0; i < numElectrons; i++) {
            electron = (Electron *) branchElectron->At(i);
            currentPT = electron->PT;
            // http://www.cplusplus.com/reference/cmath/fabs/
            currentEta = fabs(electron->Eta);
            currentPhi = fabs(electron->Phi);


            if (maxPT < currentPT) {
                maxPT = currentPT;
            }
            if (maxEta < currentEta) {
                maxEta = currentEta;
            }
            if (maxPhi < currentPhi) {
                maxPhi = currentPhi;
            }
        }
        histMaxPT_electron->Fill(maxPT);
        histMaxEta_electron->Fill(maxEta);
        histMaxPhi_electron->Fill(maxPhi);

        maxPT = -1;
        currentPT = 0;
        // loop over muons in the event
        for (int i = 0; i < numMuons; i++) {
            muon = (Muon *) branchMuon->At(i);
            currentPT = muon->PT;

            if (maxPT < currentPT) {
                maxPT = currentPT;
            }
        }
        histMaxPT_muon->Fill(maxPT);

        maxPT = -1;
        max2ndPT = 0;
        currentPT = 0;
        // loop over jets in the event
        for (int i = 0; i < numJets; i++) {
            jet = (Jet *) branchJet->At(i);
            currentPT = jet->PT;

            if (maxPT < currentPT) {
                max2ndPT = maxPT; // the current maximum becomes the new 2nd maximum.
                maxPT = currentPT;
            } else if (max2ndPT < currentPT) {
                max2ndPT = currentPT;
            }
        }
        histMaxPT_jet->Fill(maxPT);
        hist2ndMaxPT_jet->Fill(max2ndPT);

        //cout << numJets << endl;
    }

    /*
    // Show resulting histograms
    histMaxPT_electron->Draw();
    histMaxPT_muon->Draw();
    histMaxPT_jet->Draw();
    hist2ndMaxPT_jet->Draw();
     */

    f.Write();
}
