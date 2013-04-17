/*
 * *******************************
 * Erkcan Özcan on 16.04.2013 :  
 * 
        1) e+e- ve mu+mu- invariant mass histogramlarini ekleyelim, Z bozonunu gorelim.
        2) Z bozonu ile olaydaki en yuksek pt'li jeti birlestirip invariant mass histogramina bakalim.
 ***************************
 * 
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
 * other refs.
 * /home/kaya/Documents/particle-physics-kaya/Delphes/Delphes-3.0.5/examples/Example3.C
 * 
 * how to run file:
 * root -l examples/e6_rootMacro1.C\(\"delphes_output.root\"\)
 */

//#include <root/TObjArray.h>
#include <math.h>
//#include <root/TH1.h>
//#include <cmath>
#include <stdlib.h>
//#include <root/TTree.h>
//#include <root/TObjArray.h>
//#include <root/TTree.h>
//#include <root/Rtypes.h>
//#include <root/TH1.h>
//#include <root/TFile.h>

class ExRootTreeReader;

//------------------------------------------------------------------------------

void e6_rootMacro1(const char *inputFile) {
    gSystem->Load("libDelphes");

    // Create chain of root trees
    //    TChain chain("Delphes");
    //    chain.Add(inputFile);
    TChain *chain = new TChain("Delphes"); // adopted from Example3.C of Delphes
    chain->Add(inputFile);

    // Create object of class ExRootTreeReader
    //ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);
    ExRootTreeReader *treeReader = new ExRootTreeReader(chain); // adopted from Example3.C of Delphes
    Long64_t numberOfEntries = treeReader->GetEntries();


    string histoFile_str = "e6_rootMacro1.root";
    // TFile constructor accepts type "const char*"
    const char* histoFile_char = histoFile_str.c_str();
    // overwrite existing ".root" file
    TFile f(histoFile_char, "recreate");

    // number of particles in an event
    Long64_t numParticles = -1;
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

    Double_t currentMass = 0;

    // Get pointers to branches used in this analysis
    TClonesArray *branchParticle = treeReader->UseBranch("Particle");
    TClonesArray *branchElectron = treeReader->UseBranch("Electron");
    TClonesArray *branchMuon = treeReader->UseBranch("Muon");
    TClonesArray *branchJet = treeReader->UseBranch("Jet");

    // Book histograms
    Double_t histMaxPT_upper = 700000.0;
    Double_t histMaxPT_jet_upper = 1000000.0;
    TH1 *histMaxPT_electron = new TH1F("MaxPT_electron", "maximum of electron P_{T}", 100, 0.0, histMaxPT_upper);
    TH1 *histMaxEta_electron = new TH1F("MaxPT_Eta", "maximum of electron abs(Eta)", 100, 0.0, 4);
    TH1 *histMaxPhi_electron = new TH1F("MaxPT_Phi", "maximum of electron abs(Phi)", 100, 0.0, 4);
    TH1 *histMaxPT_muon = new TH1F("MaxPT_muon", "maximum of muon P_{T}", 100, 0.0, histMaxPT_upper);
    TH1 *histMaxPT_jet = new TH1F("MaxPT_jet", "maximum of jet P_{T}", 100, 0.0, histMaxPT_jet_upper);
    TH1 *hist2ndMaxPT_jet = new TH1F("Max2ndPT_jet", "2nd highest of jet P_{T}", 100, 0.0, histMaxPT_jet_upper);

    //  1) e+e- ve mu+mu- invariant mass histogramlarini ekleyelim, Z bozonunu gorelim.
    //  1) e+e- ve mu+mu- invariant mass histogramlarini ekleyelim, 
    Double_t histMassElectron_upper = 0.001;
    Double_t histMassMuon_upper = 0.2;
    TH1 *histMass_electron = new TH1F("Mass_electron", "mass of electron (e+e-)", 100, 0.0, histMassElectron_upper);
    TH1 *histMass_muon = new TH1F("Mass_muon", "mass of muon (mu+mu-)", 100, 0.0, histMassMuon_upper);
    // Z bozonunu gorelim.
    // I will use a tree to study Z boson.
    TTree t_Zboson("Z", "ein Baum über Z Boson");

    int Zboson_id = 23;
    Double_t ch_Z, mass_Z, E_Z, px_Z, py_Z, pz_Z, pt_Z, eta_Z, phi_Z, rapidity_Z, stat_Z, pid_Z;

    t_Zboson.Branch("Z.charge", &ch_Z, "ch_Z/D");
    t_Zboson.Branch("Z.mass", &mass_Z, "mass_Z/D");
    t_Zboson.Branch("Z.energy", &E_Z, "E_Z/D");
    t_Zboson.Branch("Z.Px", &px_Z, "px_Z/D");
    t_Zboson.Branch("Z.Py", &py_Z, "py_Z/D");
    t_Zboson.Branch("Z.Pz", &pz_Z, "pz_Z/D");
    t_Zboson.Branch("Z.PT", &pt_Z, "pt_Z/D");
    t_Zboson.Branch("Z.Eta", &eta_Z, "eta_Z/D");
    t_Zboson.Branch("Z.Phi", &phi_Z, "phi_Z/D");
    t_Zboson.Branch("Z.Rapidity", &rapidity_Z, "rapidity_Z/D");
    t_Zboson.Branch("Z.status", &stat_Z, "stat_Z/D");
    t_Zboson.Branch("Z.PID", &pid_Z, "pid_Z/D");

    // 2) Z bozonu ile olaydaki en yuksek pt'li jeti birlestirip invariant mass histogramina bakalim.
    TTree t_Other("Other", "ein Baum über die anderen Sachen");
    Double_t mass_Jet_AND_Z;
    Double_t massJet_with_maxPT = -1;
    // isim aralarında "boşluk, +, (, ), ]" vs. gibi karakterler kabul edilmiyor ==> totalMass_of_Z_AND_Jet_with_max_PT
    t_Other.Branch("totalMass_of_Z_AND_Jet_with_max_PT", &mass_Jet_AND_Z, "mass_Jet_AND_Z/D");

    GenParticle *particle;
    Electron *electron;
    Muon *muon;
    Jet *jet;

    Int_t tmp = 0;
    // Loop over all events
    for (Int_t entry = 0; entry < numberOfEntries; ++entry) {
        // Load selected branches with data from specified event
        treeReader->ReadEntry(entry);

        numParticles = branchParticle->GetEntries();
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
            particle = (GenParticle*) electron->Particle.GetObject();
            currentMass = particle->Mass;
            // http://www.cplusplus.com/reference/cmath/fabs/
            //            currentEta = fabs(electron->Eta);
            //            currentPhi = fabs(electron->Phi);
            // not necessary to take absolute val.
            currentEta = electron->Eta;
            currentPhi = electron->Phi;


            if (maxPT < currentPT) {
                maxPT = currentPT;
            }
            if (maxEta < currentEta) {
                maxEta = currentEta;
            }
            if (maxPhi < currentPhi) {
                maxPhi = currentPhi;
            }
            histMass_electron->Fill(currentMass);
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
            particle = (GenParticle*) muon->Particle.GetObject();
            currentMass = particle->Mass;

            if (maxPT < currentPT) {
                maxPT = currentPT;
            }
            histMass_muon->Fill(currentMass);
        }
        histMaxPT_muon->Fill(maxPT);

        maxPT = -1;
        max2ndPT = -1;
        currentPT = 0;
        // loop over jets in the event
        for (int i = 0; i < numJets; i++) {
            jet = (Jet *) branchJet->At(i);
            currentPT = jet->PT;
            currentMass = jet->Mass;

            if (maxPT < currentPT) {
                max2ndPT = maxPT; // the current maximum becomes the new 2nd maximum.
                maxPT = currentPT;
                massJet_with_maxPT = currentMass;
            } else if (max2ndPT < currentPT) {
                max2ndPT = currentPT;
            }
        }
        histMaxPT_jet->Fill(maxPT);
        hist2ndMaxPT_jet->Fill(max2ndPT);


        // loop over all particles in the event
        for (int i = 0; i < numParticles; i++) {
            particle = (GenParticle*) branchParticle->At(i);
            tmp = particle->PID;
            //  Z bozonunu gorelim.
            if (abs(tmp) == Zboson_id) {
                ch_Z = particle->Charge;
                mass_Z = particle->Mass;
                E_Z = particle->E;
                px_Z = particle->Px;
                py_Z = particle->Py;
                pz_Z = particle->Pz;
                pt_Z = particle->PT;
                eta_Z = particle->Eta;
                phi_Z = particle->Phi;
                rapidity_Z = particle->Rapidity;
                stat_Z = particle->Status;
                pid_Z = particle->PID;
                t_Zboson.Fill();

                // 2) Z bozonu ile olaydaki en yuksek pt'li jeti birlestirip invariant mass histogramina bakalim.
                mass_Jet_AND_Z = massJet_with_maxPT + mass_Z;
                t_Other.Fill();
            }
        }

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

    delete treeReader;
    delete chain;
}
