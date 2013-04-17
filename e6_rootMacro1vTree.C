/*
 * aim of this ROOT macro : do the below tasks with usage of "TTree" object.
 * 
 * 
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
//#include <root/Rtypes.h>
//#include <root/TTree.h>
//#include <root/TTree.h>
//#include <root/TObjArray.h>
//#include <root/TTree.h>
//#include <root/Rtypes.h>
//#include <root/TH1.h>
//#include <root/TFile.h>

class ExRootTreeReader;

//------------------------------------------------------------------------------

void e6_rootMacro1vTree(const char *inputFile) {
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


    string histoFile_str = "e6_rootMacro1vTree.root";
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

    Double_t currentMass = 0;

    // Get pointers to branches used in this analysis
    TClonesArray *branchParticle = treeReader->UseBranch("Particle");
    TClonesArray *branchElectron = treeReader->UseBranch("Electron");
    TClonesArray *branchMuon = treeReader->UseBranch("Muon");
    TClonesArray *branchJet = treeReader->UseBranch("Jet");

    // Book histograms
    //////////// I will use a tree to study electron with maximum PT.
    TTree t_electron_with_max_PT("electron_with_max_PT", "ein Baum über Elektronen mit höchsten PT");

    int electron_id = 11;
    Double_t ch_e, mass_e, E_e, px_e, py_e, pz_e, pt_e, eta_e, phi_e, rapidity_e, stat_e, pid_e;

    t_electron_with_max_PT.Branch("electron.charge", &ch_e, "ch_e/D");
    //    t_electron_with_max_PT.Branch("electron.mass", &mass_e, "mass_e/D");
    //    t_electron_with_max_PT.Branch("electron.energy", &E_e, "E_e/D");
    //    t_electron_with_max_PT.Branch("electron.Px", &px_e, "px_e/D");
    //    t_electron_with_max_PT.Branch("electron.Py", &py_e, "py_e/D");
    //    t_electron_with_max_PT.Branch("electron.Pz", &pz_e, "pz_e/D");
    t_electron_with_max_PT.Branch("electron.PT", &pt_e, "pt_e/D");
    t_electron_with_max_PT.Branch("electron.Eta", &eta_e, "eta_e/D");
    t_electron_with_max_PT.Branch("electron.Phi", &phi_e, "phi_e/D");
    //    t_electron_with_max_PT.Branch("electron.Rapidity", &rapidity_e, "rapidity_e/D");
    //    t_electron_with_max_PT.Branch("electron.status", &stat_e, "stat_e/D");
    //    t_electron_with_max_PT.Branch("electron.PID", &pid_e, "pid_e/D");

    //////////// I will use a tree to study muon with maximum PT.
    TTree t_muon_with_max_PT("muon_with_max_PT", "ein Baum über Muonen mit höchsten PT");

    int muon_id = 13;
    Double_t ch_muon, mass_muon, E_muon, px_muon, py_muon, pz_muon, pt_muon, eta_muon, phi_muon, rapidity_muon, stat_muon, pid_muon;

    t_muon_with_max_PT.Branch("muon.charge", &ch_muon, "ch_muon/D");
    //    t_muon_with_max_PT.Branch("muon.mass", &mass_muon, "mass_muon/D");
    //    t_muon_with_max_PT.Branch("muon.energy", &E_muon, "E_muon/D");
    //    t_muon_with_max_PT.Branch("muon.Px", &px_muon, "px_muon/D");
    //    t_muon_with_max_PT.Branch("muon.Py", &py_muon, "py_muon/D");
    //    t_muon_with_max_PT.Branch("muon.Pz", &pz_muon, "pz_muon/D");
    t_muon_with_max_PT.Branch("muon.PT", &pt_muon, "pt_muon/D");
    t_muon_with_max_PT.Branch("muon.Eta", &eta_muon, "eta_muon/D");
    t_muon_with_max_PT.Branch("muon.Phi", &phi_muon, "phi_muon/D");
    //    t_muon_with_max_PT.Branch("muon.Rapidity", &rapidity_muon, "rapidity_muon/D");
    //    t_muon_with_max_PT.Branch("muon.status", &stat_muon, "stat_muon/D");
    //    t_muon_with_max_PT.Branch("muon.PID", &pid_muon, "pid_muon/D");

    //////////// I will use a tree to study jet with maximum PT.
    TTree t_jet_with_max_PT("jet_with_max_PT", "ein Baum über jets mit höchsten PT");

    Double_t ch_jet, mass_jet, E_jet, px_jet, py_jet, pz_jet, pt_jet, eta_jet, phi_jet, rapidity_jet, stat_jet, pid_jet;

    t_jet_with_max_PT.Branch("jet.charge", &ch_jet, "ch_jet/D");
    t_jet_with_max_PT.Branch("jet.mass", &mass_jet, "mass_jet/D");
    //    t_jet_with_max_PT.Branch("jet.energy", &E_jet, "E_jet/D");
    //    t_jet_with_max_PT.Branch("jet.Px", &px_jet, "px_jet/D");
    //    t_jet_with_max_PT.Branch("jet.Py", &py_jet, "py_jet/D");
    //    t_jet_with_max_PT.Branch("jet.Pz", &pz_jet, "pz_jet/D");
    t_jet_with_max_PT.Branch("jet.PT", &pt_jet, "pt_jet/D");
    t_jet_with_max_PT.Branch("jet.Eta", &eta_jet, "eta_jet/D");
    t_jet_with_max_PT.Branch("jet.Phi", &phi_jet, "phi_jet/D");
    //    t_jet_with_max_PT.Branch("jet.Rapidity", &rapidity_jet, "rapidity_jet/D");
    //    t_jet_with_max_PT.Branch("jet.status", &stat_jet, "stat_jet/D");
    //    t_jet_with_max_PT.Branch("jet.PID", &pid_jet, "pid_jet/D");

    //////////// I will use a tree to study jet with 2nd maximum PT.
    TTree t_jet_with_2ndmax_PT("jet_with_2ndmax_PT", "ein Baum über jets mit zweiten höchsten PT");

    Double_t ch_jet2nd, mass_jet2nd, E_jet2nd, px_jet2nd, py_jet2nd, pz_jet2nd, pt_jet2nd, eta_jet2nd, phi_jet2nd, rapidity_jet2nd, stat_jet2nd, pid_jet2nd;

    t_jet_with_2ndmax_PT.Branch("jet.charge", &ch_jet2nd, "ch_jet2nd/D");
    t_jet_with_2ndmax_PT.Branch("jet.mass", &mass_jet2nd, "mass_jet2nd/D");
    //    t_jet_with_2ndmax_PT.Branch("jet.energy", &E_jet2nd, "E_jet2nd/D");
    //    t_jet_with_2ndmax_PT.Branch("jet.Px", &px_jet2nd, "px_jet2nd/D");
    //    t_jet_with_2ndmax_PT.Branch("jet.Py", &py_jet2nd, "py_jet2nd/D");
    //    t_jet_with_2ndmax_PT.Branch("jet.Pz", &pz_jet2nd, "pz_jet2nd/D");
    t_jet_with_2ndmax_PT.Branch("jet.PT", &pt_jet, "pt_jet/D");
    t_jet_with_2ndmax_PT.Branch("jet.Eta", &eta_jet2nd, "eta_jet2nd/D");
    t_jet_with_2ndmax_PT.Branch("jet.Phi", &phi_jet2nd, "phi_jet2nd/D");
    //    t_jet_with_2ndmax_PT.Branch("jet.Rapidity", &rapidity_jet2nd, "rapidity_jet2nd/D");
    //    t_jet_with_2ndmax_PT.Branch("jet.status", &stat_jet, "stat_jet/D");
    //    t_jet_with_2ndmax_PT.Branch("jet.PID", &pid_jet2nd, "pid_jet2nd/D");

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

    Bool_t isParticleFoundInThatEvent = false;
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
        isParticleFoundInThatEvent=false;
        // loop over electrons in the event
        for (int i = 0; i < numElectrons; i++) {
            isParticleFoundInThatEvent = true;

            electron = (Electron *) branchElectron->At(i);

            particle = (GenParticle*) electron->Particle.GetObject();
            currentMass = particle->Mass;
            histMass_electron->Fill(currentMass);

            currentPT = electron->PT;
            // electron with maximum PT.
            if (maxPT < currentPT) {
                maxPT = currentPT;

                ch_e = electron->Charge;
                pt_e = electron->PT;
                eta_e = electron->Eta;
                phi_e = electron->Phi;
            }
        }
        if (isParticleFoundInThatEvent) {
            t_electron_with_max_PT.Fill();
        }

        maxPT = -1;
        currentPT = 0;
        isParticleFoundInThatEvent = false;
        // loop over muons in the event
        for (int i = 0; i < numMuons; i++) {
            isParticleFoundInThatEvent = true;
            muon = (Muon *) branchMuon->At(i);

            particle = (GenParticle*) muon->Particle.GetObject();
            currentMass = particle->Mass;
            histMass_muon->Fill(currentMass);

            currentPT = muon->PT;
            // muon with maximum PT.
            if (maxPT < currentPT) {
                maxPT = currentPT;

                ch_muon = muon->Charge;
                pt_muon = muon->PT;
                eta_muon = muon->Eta;
                phi_muon = muon->Phi;
            }
        }
        if (isParticleFoundInThatEvent) {
            t_muon_with_max_PT.Fill();
        }

        maxPT = -1;
        max2ndPT = 0;
        currentPT = 0;
        isParticleFoundInThatEvent = false;
        // loop over jets in the event
        for (int i = 0; i < numJets; i++) {
            isParticleFoundInThatEvent = true;

            jet = (Jet *) branchJet->At(i);
            currentPT = jet->PT;
            currentMass = jet->Mass;


            if (maxPT < currentPT) {
                max2ndPT = maxPT; // the current maximum becomes the new 2nd maximum.
                ch_jet2nd = ch_jet;
                pt_jet2nd = pt_jet;
                eta_jet2nd = eta_jet;
                phi_jet2nd = phi_jet;
                mass_jet2nd = mass_jet;

                maxPT = currentPT;
                massJet_with_maxPT = currentMass;

                ch_jet = jet->Charge;
                pt_jet = jet->PT;
                eta_jet = jet->Eta;
                phi_jet = jet->Phi;
                mass_jet = jet->Mass;

            } else if (max2ndPT < currentPT) {
                max2ndPT = currentPT;

                ch_jet2nd = jet->Charge;
                pt_jet2nd = jet->PT;
                eta_jet2nd = jet->Eta;
                phi_jet2nd = jet->Phi;
                mass_jet2nd = jet->Mass;
            }
        }
        if (isParticleFoundInThatEvent) {
            t_jet_with_max_PT.Fill();
            t_jet_with_2ndmax_PT.Fill();
        }


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
