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

#include "bounHEP_Fncs.h"

//#include <root/TObjArray.h>
#include <math.h>
//#include <root/TH1.h>
//#include <cmath>
#include <stdlib.h>
#include <string>
//#include <root/TVirtualTreePlayer.h>
//#include <root/TTree.h>
//#include <root/Rtypes.h>
//#include <root/TFile.h>

class ExRootTreeReader;

//------------------------------------------------------------------------------

void e6_GenParticleTrees(const char *inputFile) {
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

    string histoFile_str = "e6_GenParticleTrees.root";
    // TFile constructor accepts type "const char*"
    const char* histoFile_char = histoFile_str.c_str();
    // overwrite existing ".root" file
    TFile f(histoFile_char, "recreate");

    // number of particles in an event
    Long64_t numParticles = -1;
    Long64_t numElectrons = -1;
    Long64_t numMuons = -1;
    Long64_t numJets = -1;

    // HEP ID
    int Zboson_id = 23;
    int Higgs_id = 25;

    // Get pointers to branches used in this analysis
    TClonesArray *branchParticle = treeReader->UseBranch("Particle");
    TClonesArray *branchElectron = treeReader->UseBranch("Electron");
    TClonesArray *branchMuon = treeReader->UseBranch("Muon");
    TClonesArray *branchJet = treeReader->UseBranch("Jet");

    // TTree for Z boson as GenParticle
    TTree *t_ZBoson = new TTree("Z_Boson", "ein Baum über Z Boson");
    Double_t fields_t_ZBoson[numOfFields_GenParticle];
    const char* prefix_t_ZBoson = "z"; // must start with lowercase letter, dont know the stupid reason for that
    initializeTTree4GenParticle(t_ZBoson, fields_t_ZBoson, prefix_t_ZBoson);
    
    // TTree for Higgs boson as GenParticle
    TTree *t_Higgs = new TTree("Higgs", "ein Baum über Higgs Boson");
    Double_t fields_t_Higgs[numOfFields_GenParticle];
    const char* prefix_t_Higgs = "h"; // must start with lowercase letter, dont know the stupid reason for that
    initializeTTree4GenParticle(t_Higgs, fields_t_Higgs, prefix_t_Higgs);

    GenParticle *particle;
    Electron *electron;
    Muon *muon;
    Jet *jet;

    // Loop over all events
    for (Int_t entry = 0; entry < numberOfEntries; ++entry) {
        // Load selected branches with data from specified event
        treeReader->ReadEntry(entry);

        numParticles = branchParticle->GetEntries();
        numElectrons = branchElectron->GetEntries();
        numMuons = branchMuon->GetEntries();
        numJets = branchJet->GetEntries();

        // loop over all particles in the event
        for (int i = 0; i < numParticles; i++) {
            particle = (GenParticle*) branchParticle->At(i);

            //  Z bozonunu gorelim.
            fillTTree4GenParticle(t_ZBoson, fields_t_ZBoson, particle, Zboson_id);
            //  Higgs bozonunu gorelim.
            fillTTree4GenParticle(t_Higgs, fields_t_Higgs, particle, Higgs_id);
        }

    }

    f.Write();

    //delete t_ZBoson;
    //delete t_Higgs;
    delete treeReader;
    delete chain;
}
