/* 
 * File:   bounHEP_Fncs.h
 * Author: kaya
 *
 * Created on April 17, 2013, 12:06 PM
 */

#ifndef BOUNHEP_FNCS_H
#define	BOUNHEP_FNCS_H

#include <string>
#include "e6_Class.h"
#include "e6_v3_Class.h"
#include "kayasC_Fncs.h"

using namespace std;

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	__cplusplus
}
#endif

void loop_HiggsMass(e6_Class &e6);
void loop_Reconstruct_Z(e6_Class &e6);
void loop_Reconstruct_Z_from_ee(e6_Class &e6);
void loop_Reconstruct_Z_from_mumu(e6_Class &e6);
void loop_Reconstruct_De(e6_Class &e6);
void loop_Reconstruct_de(e6_Class &e6);
void loop_Reconstruct_Higgs(e6_Class &e6);
void loop_Particle(e6_Class &e6);
void loop_maxJetPT(e6_Class &e6);

class GenParticle; // if this does not exist, ~> Warning: Unknown type 'GenParticle' in function argument handled as int

void initializeTTree4Particle(TTree* t, Double_t* adresler, const char* branchNamePrefix);
void fillTTree4Particle(TTree* t, Double_t* adresler, e6_Class &e6, int indexOfParticle);
void fillTTree4Particle(TTree* t, Double_t* adresler, e6_Class &e6, int indexOfParticle, int pid);
void initializeTTree4TLorentzVector(TTree* t, Double_t* adresler, const char* branchNamePrefix);
void fillTTree4LorentzVector(TTree* t, Double_t* adresler, TLorentzVector &vec);
void initializeTTree(TTree* t, Double_t* adresler, int len_Fields, const char* branchNamePrefix, const char* fields[]);
void initializeTTree4GenParticle(TTree* t, Double_t* adresler, const char* branchNamePrefix);
void initializeTTree4GenParticle(TTree &t, Double_t* adresler, const char* branchNamePrefix);
void fillTTree4GenParticle(TTree* t, Double_t* adresler, GenParticle* particle);
void fillTTree4GenParticle(TTree* t, Double_t* adresler, GenParticle* particle, int pid);

static const int numOfFields_GenParticle = 20;
static const int numOfFields_TLorentzVector = 32;
static const int numOfFields_Particle = 32;
static const char* loop_Reconstruct_de_outputName = "loop_Reconstruct_de.root"; // output file name of the function loop_Reconstruct_de()
static const char* loop_Reconstruct_De_outputName = "loop_Reconstruct_De.root"; // output file name of the function loop_Reconstruct_De()
static const char* loop_Reconstruct_Higgs_outputName = "loop_Reconstruct_Higgs.root"; // output file name of the function loop_Reconstruct_Higgs()
static const char* loop_Reconstruct_Z_outputName = "loop_Reconstruct_Z.root"; // output file name of the function loop_Reconstruct_Z()

static const char* t_Reco_de1_Name = "Recode1"; // for "loop_Reconstruct_de()"
static const char* t_Reco_de2_Name = "Recode2"; // for "loop_Reconstruct_de()"
static const char* t_Reco_De1_Name = "RecoDe1"; // for "loop_Reconstruct_De()"
static const char* t_Reco_De2_Name = "RecoDe2"; // for "loop_Reconstruct_De()"

static const char* prefix_t_Reco_de1 = "de1";
static const char* prefix_t_Reco_de2 = "de2";
static const char* prefix_t_RecoDe1 = "De1";
static const char* prefix_t_RecoDe2 = "De2";

/*
 * loop over particles (I guess these are generated particles) and store their fields to a "TTree"
 * particles considered:
 *      electron
 *      muon
 *      Higgs
 *      Z
 */
void loop_Particle(e6_Class &e6) {
    if (e6.fChain == 0) return;

    string histoFile_str = "loop_Particle.root";
    // TFile constructor accepts type "const char*"
    const char* histoFile_char = histoFile_str.c_str();
    // overwrite existing ".root" file
    TFile f(histoFile_char, "recreate");

    TTree *t_e = new TTree("electron", "generated electrons");
    Double_t fields_t_e[numOfFields_Particle];
    const char* prefix_t_e = "e"; // must start with lowercase letter, dont know the stupid reason for that
    initializeTTree4Particle(t_e, fields_t_e, prefix_t_e);

    TTree *t_mu = new TTree("muon", "generated muons");
    Double_t fields_t_mu[numOfFields_Particle];
    const char* prefix_t_mu = "mu"; // must start with lowercase letter, dont know the stupid reason for that
    initializeTTree4Particle(t_mu, fields_t_mu, prefix_t_mu);

    TTree *t_h = new TTree("higgs", "generated higgs bosons");
    Double_t fields_t_h[numOfFields_Particle];
    const char* prefix_t_h = "h"; // must start with lowercase letter, dont know the stupid reason for that
    initializeTTree4Particle(t_h, fields_t_h, prefix_t_h);

    TTree *t_Z = new TTree("Z", "generated Z bosons");
    Double_t fields_t_Z[numOfFields_Particle];
    const char* prefix_t_Z = "z"; // must start with lowercase letter, dont know the stupid reason for that
    initializeTTree4Particle(t_Z, fields_t_Z, prefix_t_Z);

    int i = 0;
    int electron_ID = 11;
    int muon_ID = 13;
    int h_ID = 25; // pid of Higgs boson
    int Z_ID = 23; // pid of Z boson

    Long64_t nentries = e6.fChain->GetEntriesFast();

    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry = 0; jentry < nentries; jentry++) {
        Long64_t ientry = e6.LoadTree(jentry);
        if (ientry < 0) break;
        nb = e6.fChain->GetEntry(jentry);
        nbytes += nb;
        // if (Cut(ientry) < 0) continue;

        for (i = 0; i < kMaxParticle; i++) {
            fillTTree4Particle(t_e, fields_t_e, e6, i, electron_ID);
            fillTTree4Particle(t_mu, fields_t_mu, e6, i, muon_ID);
            fillTTree4Particle(t_h, fields_t_h, e6, i, h_ID);
            fillTTree4Particle(t_Z, fields_t_Z, e6, i, Z_ID);
        }

    }

    f.Write();
}

/*
 * sorts the jets in an event according to their PT's.
 */
void loop_maxJetPT(e6_Class &e6) {
    if (e6.fChain == 0) return;

    int i;
    int* sorted_indices;
    int len;
    Long64_t nentries = e6.fChain->GetEntriesFast();

    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry = 0; jentry < nentries; jentry++) {
        Long64_t ientry = e6.LoadTree(jentry);
        if (ientry < 0) break;
        nb = e6.fChain->GetEntry(jentry);
        nbytes += nb;
        // if (Cut(ientry) < 0) continue;

        //DRAFT for the method
        //len = (sizeof (e6.Jet_PT) / sizeof (e6.Jet_PT[0]));
        //len=kMaxJet;
        len = e6.Jet_size;
        cout << "LEN : " << len << "\n";
        cout << "JET.PT : ";
        for (i = 0; i < len; i++) {
            cout << e6.Jet_PT[i] << " , ";
        }
        cout << "\n";
        sorted_indices = sortIndices(e6.Jet_PT, len);
        cout << "ind : ";
        for (i = 0; i < len; i++) {
            cout << sorted_indices[i] << " , ";
        }
        cout << "\n";
        //                cout << "JET.PT : ";
        //        for (i = 0; i < len; i++) {
        //            cout << e6.Jet_PT[i] << " , ";
        //        }
        //        cout << "\n";
        cout << "--------------------------------\n";
    }
}

/*
 * TEMPLATE for the method "Loop()"
 * 
    if (t.fChain == 0) return;

    Long64_t nentries = t.fChain->GetEntriesFast();

    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry = 0; jentry < nentries; jentry++) {
        Long64_t ientry = t.LoadTree(jentry);
        if (ientry < 0) break;
        nb = t.fChain->GetEntry(jentry);
        nbytes += nb;
        // if (Cut(ientry) < 0) continue;
        cout << t.Electron_size << endl;
    }
 */
void loop_HiggsMass(e6_Class &e6) {
    if (e6.fChain == 0) return;

    /*
     * no need for ".root" file for this small task
     * 
    string histoFile_str = "e6_loop_HiggsMass.root";
    // TFile constructor accepts type "const char*"
    const char* histoFile_char = histoFile_str.c_str();
    // overwrite existing ".root" file
    TFile f(histoFile_char, "recreate");
     */

    // create object on stack
    TH1F histMass_Higgs("Mass_Higgs", "mass of Higgs", 100, 0.0, 200);
    // create object on heap
    //    TH1F *histMass_Higgs = new TH1F("Mass_Higgs", "mass of Higgs", 100, 0.0, 200);
    int i = 0;
    int h_ID = 25;


    Long64_t nentries = e6.fChain->GetEntriesFast();

    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry = 0; jentry < nentries; jentry++) {
        Long64_t ientry = e6.LoadTree(jentry);
        if (ientry < 0) break;
        nb = e6.fChain->GetEntry(jentry);
        nbytes += nb;
        // if (Cut(ientry) < 0) continue;

        for (i = 0; i < e6.Particle_size; i++) {
            if (e6.Particle_PID[i] == h_ID) {
                histMass_Higgs.Fill(e6.Particle_Mass[i]);
                //                histMass_Higgs->Fill(t.Particle_Mass[i]);
            }
        }
    }
    //    histMass_Higgs.Draw(); // does not work, generates empty canvas
    //    histMass_Higgs.DrawClone(); // does not work, generates empty canvas
    histMass_Higgs.DrawCopy(); // works

    //    histMass_Higgs->Draw();  // does not work, generates empty canvas   
    //    histMass_Higgs->DrawClone(); // does not work, generates empty canvas
    //    histMass_Higgs->DrawCopy(); //works

    //f.Write();
}

/*
 * reconstruct Z boson both from e-e+ and mu-mu+
 * and save the reconstructed Z boson to a tree.
 * I consider events with exactly 2 electrons or events with exactly 2 muons
 * 
 * !! I think, if Z is to be reconstructed in an event, then in the same event we should have Higgs boson to be reconstructed as well. So before reconstructing a Z in an event, I also should check whether this event can reconstruct a Higgs as well.
 * 
 * To reconstruct a Z, one needs 2 muons or 2 electrons.
 * To reconstuct a Higgs, one needs 4 jets (2 of them will be selected).
 */
void loop_Reconstruct_Z(e6_Class &e6) {
    if (e6.fChain == 0) return;

    /*
     * no need for ".root" file for this small task
     */
    string histoFile_str = loop_Reconstruct_Z_outputName;
    // TFile constructor accepts type "const char*"
    const char* histoFile_char = histoFile_str.c_str();
    // overwrite existing ".root" file
    TFile f(histoFile_char, "recreate");

    // reconstruction of Z such that e-e+ -> Z
    TTree *t_RecoZ_ee = new TTree("RecoZ-from-ee", "e-e+ -> Z");
    Double_t fields_t_RecoZ_ee[numOfFields_TLorentzVector];
    const char* prefix_t_RecoZ_ee = "z"; // must start with lowercase letter, dont know the stupid reason for that
    initializeTTree4TLorentzVector(t_RecoZ_ee, fields_t_RecoZ_ee, prefix_t_RecoZ_ee);


    // reconstruction of Z such that mu-mu+ -> Z
    TTree *t_RecoZ_mumu = new TTree("RecoZ-from-mumu", "mu-mu+ -> Z");
    Double_t fields_t_RecoZ_mumu[numOfFields_TLorentzVector];
    const char* prefix_t_RecoZ_mumu = "z"; // must start with lowercase letter, dont know the stupid reason for that
    initializeTTree4TLorentzVector(t_RecoZ_mumu, fields_t_RecoZ_mumu, prefix_t_RecoZ_mumu);

    // both reconstructions
    // reconstruction of Z such that mu-mu+ -> Z or e-e+ -> Z
    TTree *t_RecoZ = new TTree("RecoZ", "mu-mu+ -> Z");
    Double_t fields_t_RecoZ[numOfFields_TLorentzVector];
    const char* prefix_t_RecoZ = "z"; // must start with lowercase letter, dont know the stupid reason for that
    initializeTTree4TLorentzVector(t_RecoZ, fields_t_RecoZ, prefix_t_RecoZ);

    Double_t electron_mass = 0.0005; // mass in GeV
    int electron_size = 2; // number of electrons we want to observe in the event

    TLorentzVector el1, el2;
    TLorentzVector reconstructed_Z_ee;

    Double_t mu_mass = 0.10566; // mass in GeV
    int mu_size = 2; // number of muons we want to observe in the event

    TLorentzVector mu1, mu2;
    TLorentzVector reconstructed_Z_mumu;

    bool can_reconstruct_Higgs;
    int jet_size = 4; // min number of jets we want to observe in the event

    Long64_t nentries = e6.fChain->GetEntriesFast();

    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry = 0; jentry < nentries; jentry++) {
        Long64_t ientry = e6.LoadTree(jentry);
        if (ientry < 0) break;
        nb = e6.fChain->GetEntry(jentry);
        nbytes += nb;
        // if (Cut(ientry) < 0) continue;

        can_reconstruct_Higgs = (e6.Jet_size >= jet_size);

        if (can_reconstruct_Higgs) {
            if (electron_size == e6.Electron_size) {

                el1.SetPtEtaPhiM(e6.Electron_PT[0], e6.Electron_Eta[0], e6.Electron_Phi[0], electron_mass);
                el2.SetPtEtaPhiM(e6.Electron_PT[1], e6.Electron_Eta[1], e6.Electron_Phi[1], electron_mass);

                reconstructed_Z_ee = el1 + el2;
                fillTTree4LorentzVector(t_RecoZ_ee, fields_t_RecoZ_ee, reconstructed_Z_ee);
                fillTTree4LorentzVector(t_RecoZ, fields_t_RecoZ, reconstructed_Z_ee);
            }
            if (mu_size == e6.Muon_size) {

                mu1.SetPtEtaPhiM(e6.Muon_PT[0], e6.Muon_Eta[0], e6.Muon_Phi[0], mu_mass);
                mu2.SetPtEtaPhiM(e6.Muon_PT[1], e6.Muon_Eta[1], e6.Muon_Phi[1], mu_mass);

                reconstructed_Z_mumu = mu1 + mu2;
                fillTTree4LorentzVector(t_RecoZ_mumu, fields_t_RecoZ_mumu, reconstructed_Z_mumu);
                fillTTree4LorentzVector(t_RecoZ, fields_t_RecoZ, reconstructed_Z_mumu);
            }
        }
    }
    //    histMass_RecoZ.Draw(); // does not work, generates empty canvas
    //    histMass_RecoZ.DrawClone(); // does not work, generates empty canvas
    //histMass_RecoZ.DrawCopy(); // works

    //t_RecoZ.Draw();
    //t_RecoZ.DrawClone();
    //t_RecoZ.StartViewer();
    //t_RecoZ_ee.Draw("z.M");

    f.Write();
}

/*
 * reconstruct Z boson from e-e+ and save the reconstructed Z boson to a tree.
 * I consider events with exactly 2 electrons
 */
void loop_Reconstruct_Z_from_ee(e6_Class &e6) {
    if (e6.fChain == 0) return;

    /*
     * no need for ".root" file for this small task
     */
    string histoFile_str = "loop_Reconstruct_Z_from_ee.root";
    // TFile constructor accepts type "const char*"
    const char* histoFile_char = histoFile_str.c_str();
    // overwrite existing ".root" file
    TFile f(histoFile_char, "recreate");

    TTree *t_RecoZ = new TTree("RecoZ", "e-e+ -> Z");
    Double_t fields_t_RecoZ[numOfFields_TLorentzVector];
    const char* prefix_t_RecoZ = "z"; // must start with lowercase letter, dont know the stupid reason for that
    initializeTTree4TLorentzVector(t_RecoZ, fields_t_RecoZ, prefix_t_RecoZ);

    // create object on stack
    //TH1F histMass_RecoZ("Mass_RecoZ", "mass of recontructed Z", 100, 0.0, 200000);
    //TTree t_RecoZ("RecoZ", "e+e- -> Z");

    int i = 0;
    //    int electron_ID = 11;
    Double_t electron_mass = 0.0005; // mass in GeV
    int electron_size = 2; // number of electrons we want to observe in the event

    TLorentzVector el1, el2;
    TLorentzVector reconstructed_Z;

    Long64_t nentries = e6.fChain->GetEntriesFast();

    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry = 0; jentry < nentries; jentry++) {
        Long64_t ientry = e6.LoadTree(jentry);
        if (ientry < 0) break;
        nb = e6.fChain->GetEntry(jentry);
        nbytes += nb;
        // if (Cut(ientry) < 0) continue;
        if (electron_size == e6.Electron_size) {

            el1.SetPtEtaPhiM(e6.Electron_PT[0], e6.Electron_Eta[0], e6.Electron_Phi[0], electron_mass);
            el2.SetPtEtaPhiM(e6.Electron_PT[1], e6.Electron_Eta[1], e6.Electron_Phi[1], electron_mass);

            reconstructed_Z = el1 + el2;
            fillTTree4LorentzVector(t_RecoZ, fields_t_RecoZ, reconstructed_Z);
        }
    }
    //    histMass_RecoZ.Draw(); // does not work, generates empty canvas
    //    histMass_RecoZ.DrawClone(); // does not work, generates empty canvas
    //histMass_RecoZ.DrawCopy(); // works

    //t_RecoZ.Draw();
    //t_RecoZ.DrawClone();
    //t_RecoZ.StartViewer();
    t_RecoZ.Draw("z.M");

    f.Write();
}

/*
 * reconstruct Z boson from mu-mu+ and save the reconstructed Z boson to a tree.
 * I consider events with exactly 2 muons
 */
void loop_Reconstruct_Z_from_mumu(e6_Class &e6) {
    if (e6.fChain == 0) return;

    string histoFile_str = "loop_Reconstruct_Z_from_mumu.root";
    // TFile constructor accepts type "const char*"
    const char* histoFile_char = histoFile_str.c_str();
    // overwrite existing ".root" file
    TFile f(histoFile_char, "recreate");

    TTree *t_RecoZ = new TTree("RecoZ", "mu-mu+ -> Z");
    Double_t fields_t_RecoZ[numOfFields_TLorentzVector];
    const char* prefix_t_RecoZ = "z"; // must start with lowercase letter, dont know the stupid reason for that
    initializeTTree4TLorentzVector(t_RecoZ, fields_t_RecoZ, prefix_t_RecoZ);

    // create object on stack
    //TH1F histMass_RecoZ("Mass_RecoZ", "mass of recontructed Z", 100, 0.0, 200000);
    //TTree t_RecoZ("RecoZ", "e+e- -> Z");

    int i = 0;
    Double_t mu_mass = 0.10566; // mass in GeV
    int mu_size = 2; // number of muons we want to observe in the event

    TLorentzVector mu1, mu2;
    TLorentzVector reconstructed_Z;

    Long64_t nentries = e6.fChain->GetEntriesFast();

    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry = 0; jentry < nentries; jentry++) {
        Long64_t ientry = e6.LoadTree(jentry);
        if (ientry < 0) break;
        nb = e6.fChain->GetEntry(jentry);
        nbytes += nb;
        // if (Cut(ientry) < 0) continue;
        if (mu_size == e6.Muon_size) {

            mu1.SetPtEtaPhiM(e6.Muon_PT[0], e6.Muon_Eta[0], e6.Muon_Phi[0], mu_mass);
            mu2.SetPtEtaPhiM(e6.Muon_PT[1], e6.Muon_Eta[1], e6.Muon_Phi[1], mu_mass);

            reconstructed_Z = mu1 + mu2;
            fillTTree4LorentzVector(t_RecoZ, fields_t_RecoZ, reconstructed_Z);
        }
    }
    //    histMass_RecoZ.Draw(); // does not work, generates empty canvas
    //    histMass_RecoZ.DrawClone(); // does not work, generates empty canvas
    //histMass_RecoZ.DrawCopy(); // works

    //t_RecoZ.Draw();
    //t_RecoZ.DrawClone();
    //t_RecoZ.StartViewer();
    t_RecoZ.Draw("z.M");

    f.Write();
}

/*  
 * De'yi "Z bozonu+jet" ikilisi ile yeniden yarat (reconstruct De).
 *    1. jet = PT'si en yüksek olan jet
 *    2. jet = PT'si 2. en yüksek olan jet
 */
void loop_Reconstruct_De(e6_Class &e6) {

    string histoFile_str = loop_Reconstruct_De_outputName;
    // TFile constructor accepts type "const char*"
    const char* histoFile_char = histoFile_str.c_str();
    // overwrite existing ".root" file
    TFile f(histoFile_char, "recreate");
    //TDirectory* dir1=f.mkdir("asdasd");       // ".root" dosyasında dizin oluşturma

    //TTree *t_RecoDe1 = new TTree("RecoDe1", "Z + jet1 -> De");
    TTree *t_RecoDe1 = new TTree(t_Reco_De1_Name, "Z + jet1 -> De");
    //t_RecoDe1->SetDirectory(dir1);    // ".root" dosyasında dizin oluşturma
    Double_t fields_t_RecoDe1[numOfFields_TLorentzVector];
    //const char* prefix_t_RecoDe1 = "De1"; // must start with lowercase letter, dont know the stupid reason for that
    initializeTTree4TLorentzVector(t_RecoDe1, fields_t_RecoDe1, prefix_t_RecoDe1);

    //TTree *t_RecoDe2 = new TTree("RecoDe2", "Z + jet2 -> De");
    TTree *t_RecoDe2 = new TTree(t_Reco_De2_Name, "Z + jet2 -> De");
    Double_t fields_t_RecoDe2[numOfFields_TLorentzVector];
    //const char* prefix_t_RecoDe2 = "De2"; // must start with lowercase letter, dont know the stupid reason for that
    initializeTTree4TLorentzVector(t_RecoDe2, fields_t_RecoDe2, prefix_t_RecoDe2);

    // create object on stack
    //TH1F histMass_RecoZ("Mass_RecoZ", "mass of recontructed Z", 100, 0.0, 200000);
    //TTree t_RecoZ("RecoZ", "e+e- -> Z");

    int i = 0;
    Double_t electron_mass = 0.0005; // mass in GeV
    int electron_size = 2; // number of electrons we want to observe in the event

    TLorentzVector el1, el2;

    Double_t mu_mass = 0.10566; // mass in GeV
    int mu_size = 2; // number of muons we want to observe in the event

    TLorentzVector mu1, mu2;


    TLorentzVector reconstructed_Z;
    TLorentzVector jet1, jet2;
    TLorentzVector reconstructed_De1, reconstructed_De2;

    int* indices_JetPT_descending;
    // indices of the "Jet" sorted such that 
    // indices_JetPT_descending[0] matches the jet with max. PT
    // indices_JetPT_descending[len-1] matches the jet with min. PT
    int index_MaxPT;
    int index_2ndMaxPT;

    bool can_reconstruct_Higgs;
    int jet_size = 4; // min number of jets we want to observe in the event

    Long64_t nentries = e6.fChain->GetEntriesFast();

    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry = 0; jentry < nentries; jentry++) {
        Long64_t ientry = e6.LoadTree(jentry);
        if (ientry < 0) break;
        nb = e6.fChain->GetEntry(jentry);
        nbytes += nb;

        indices_JetPT_descending = sortIndices_Descending(e6.Jet_PT, e6.Jet_size);
        index_MaxPT = indices_JetPT_descending[0];
        index_2ndMaxPT = indices_JetPT_descending[1];

        jet1.SetPtEtaPhiM(e6.Jet_PT[index_MaxPT], e6.Jet_Eta[index_MaxPT], e6.Jet_Phi[index_MaxPT], e6.Jet_Mass[index_MaxPT]);
        jet2.SetPtEtaPhiM(e6.Jet_PT[index_2ndMaxPT], e6.Jet_Eta[index_2ndMaxPT], e6.Jet_Phi[index_2ndMaxPT], e6.Jet_Mass[index_2ndMaxPT]);

        // if (Cut(ientry) < 0) continue;

        can_reconstruct_Higgs = (e6.Jet_size >= jet_size);

        if (can_reconstruct_Higgs) {
            if (electron_size == e6.Electron_size) {

                el1.SetPtEtaPhiM(e6.Electron_PT[0], e6.Electron_Eta[0], e6.Electron_Phi[0], electron_mass);
                el2.SetPtEtaPhiM(e6.Electron_PT[1], e6.Electron_Eta[1], e6.Electron_Phi[1], electron_mass);

                reconstructed_Z = el1 + el2;

                reconstructed_De1 = reconstructed_Z + jet1;
                reconstructed_De2 = reconstructed_Z + jet2;

                fillTTree4LorentzVector(t_RecoDe1, fields_t_RecoDe1, reconstructed_De1);
                fillTTree4LorentzVector(t_RecoDe2, fields_t_RecoDe2, reconstructed_De2);
            }
            if (mu_size == e6.Muon_size) {

                mu1.SetPtEtaPhiM(e6.Muon_PT[0], e6.Muon_Eta[0], e6.Muon_Phi[0], mu_mass);
                mu2.SetPtEtaPhiM(e6.Muon_PT[1], e6.Muon_Eta[1], e6.Muon_Phi[1], mu_mass);

                reconstructed_Z = mu1 + mu2;

                reconstructed_De1 = reconstructed_Z + jet1;
                reconstructed_De2 = reconstructed_Z + jet2;

                fillTTree4LorentzVector(t_RecoDe1, fields_t_RecoDe1, reconstructed_De1);
                fillTTree4LorentzVector(t_RecoDe2, fields_t_RecoDe2, reconstructed_De2);
            }
        }
    }
    //    histMass_RecoZ.Draw(); // does not work, generates empty canvas
    //    histMass_RecoZ.DrawClone(); // does not work, generates empty canvas
    //histMass_RecoZ.DrawCopy(); // works

    f.Write();
}

/*
 * de'yi "H+jet" ile yeniden yarat.
 *  5.1. H + jet1 --> de
 *  5.2. H + jet2 --> de
 *      (jet1 = PT'si en yüksek olan jet , jet2 = PT'si 2. en yüksek olan jet)
 */
void loop_Reconstruct_de(e6_Class &e6) {

    string histoFile_str = loop_Reconstruct_de_outputName;
    // TFile constructor accepts type "const char*"
    const char* histoFile_char = histoFile_str.c_str();
    // overwrite existing ".root" file
    TFile f(histoFile_char, "recreate");
    //TDirectory* dir1=f.mkdir("asdasd");       // ".root" dosyasında dizin oluşturma

    //TTree *t_Reco_de1 = new TTree("Recode1", "H + jet1 -> de");
    TTree *t_Reco_de1 = new TTree(t_Reco_de1_Name, "H + jet1 -> de");
    //t_RecoDe1->SetDirectory(dir1);    // ".root" dosyasında dizin oluşturma
    Double_t fields_t_Reco_de1[numOfFields_TLorentzVector];
    //const char* prefix_t_Reco_de1 = "de1"; // must start with lowercase letter, dont know the stupid reason for that
    initializeTTree4TLorentzVector(t_Reco_de1, fields_t_Reco_de1, prefix_t_Reco_de1);

    //TTree *t_Reco_de2 = new TTree("Recode2", "H + jet2 -> de");
    TTree *t_Reco_de2 = new TTree(t_Reco_de2_Name, "H + jet2 -> de");
    Double_t fields_t_Reco_de2[numOfFields_TLorentzVector];
    //const char* prefix_t_Reco_de2 = "de2"; // must start with lowercase letter, dont know the stupid reason for that
    initializeTTree4TLorentzVector(t_Reco_de2, fields_t_Reco_de2, prefix_t_Reco_de2);

    // create object on stack
    //TH1F histMass_RecoZ("Mass_RecoZ", "mass of recontructed Z", 100, 0.0, 200000);
    //TTree t_RecoZ("RecoZ", "e+e- -> Z");

    int jet_size = 4; // min number of jets we want to observe in the event

    TLorentzVector jet3, jet4;
    TLorentzVector reconstructed_H;

    TLorentzVector jet1, jet2;
    TLorentzVector reconstructed_de1, reconstructed_de2;

    int* indices_JetPT_descending;
    // indices of the "Jet" sorted such that 
    // indices_JetPT_descending[0] matches the jet with max. PT
    // indices_JetPT_descending[len-1] matches the jet with min. PT
    int index_MaxPT;
    int index_2ndMaxPT;
    int index_3rdMaxPT;
    int index_4thMaxPT;

    bool can_reconstruct_Z;
    int electron_size = 2; // number of electrons we want to observe in the event
    int mu_size = 2; // number of muons we want to observe in the event

    Long64_t nentries = e6.fChain->GetEntriesFast();

    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry = 0; jentry < nentries; jentry++) {
        Long64_t ientry = e6.LoadTree(jentry);
        if (ientry < 0) break;
        nb = e6.fChain->GetEntry(jentry);
        nbytes += nb;

        can_reconstruct_Z = (e6.Electron_size == electron_size) || (e6.Muon_size == mu_size);

        // if (Cut(ientry) < 0) continue;
        if (e6.Jet_size >= jet_size && can_reconstruct_Z) {

            indices_JetPT_descending = sortIndices_Descending(e6.Jet_PT, e6.Jet_size);

            index_3rdMaxPT = indices_JetPT_descending[2];
            index_4thMaxPT = indices_JetPT_descending[3];
            jet3.SetPtEtaPhiM(e6.Jet_PT[index_3rdMaxPT], e6.Jet_Eta[index_3rdMaxPT], e6.Jet_Phi[index_3rdMaxPT], e6.Jet_Mass[index_3rdMaxPT]);
            jet4.SetPtEtaPhiM(e6.Jet_PT[index_4thMaxPT], e6.Jet_Eta[index_4thMaxPT], e6.Jet_Phi[index_4thMaxPT], e6.Jet_Mass[index_4thMaxPT]);

            reconstructed_H = jet3 + jet4;

            index_MaxPT = indices_JetPT_descending[0];
            index_2ndMaxPT = indices_JetPT_descending[1];
            jet1.SetPtEtaPhiM(e6.Jet_PT[index_MaxPT], e6.Jet_Eta[index_MaxPT], e6.Jet_Phi[index_MaxPT], e6.Jet_Mass[index_MaxPT]);
            jet2.SetPtEtaPhiM(e6.Jet_PT[index_2ndMaxPT], e6.Jet_Eta[index_2ndMaxPT], e6.Jet_Phi[index_2ndMaxPT], e6.Jet_Mass[index_2ndMaxPT]);

            reconstructed_de1 = reconstructed_H + jet1;
            reconstructed_de2 = reconstructed_H + jet2;

            fillTTree4LorentzVector(t_Reco_de1, fields_t_Reco_de1, reconstructed_de1);
            fillTTree4LorentzVector(t_Reco_de2, fields_t_Reco_de2, reconstructed_de2);
        }
    }
    //    histMass_RecoZ.Draw(); // does not work, generates empty canvas
    //    histMass_RecoZ.DrawClone(); // does not work, generates empty canvas
    //histMass_RecoZ.DrawCopy(); // works

    f.Write();
}

/*  
 * 4. Higgs bozonunu "jet3+jet4" ikilisi ile yeniden yarat (reconstruct Higgs boson).
 *  jet3 =  PT'si 3. en yüksek olan jet
 *  jet4 =  PT'si 4. en yüksek olan jet
 * 
 * !! I think, if Higgs is to be reconstructed in an event, then in the same event we should have Z boson to be reconstructed as well. So before reconstructing a Higgs in an event, I also should check whether this event can reconstruct a Z as well.
 * 
 * To reconstruct a Z, one needs 2 muons or 2 electrons.
 * To reconstuct a Higgs, one needs 4 jets (2 of them will be selected).
 */
void loop_Reconstruct_Higgs(e6_Class &e6) {

    string histoFile_str = loop_Reconstruct_Higgs_outputName;
    // TFile constructor accepts type "const char*"
    const char* histoFile_char = histoFile_str.c_str();
    // overwrite existing ".root" file
    TFile f(histoFile_char, "recreate");
    //TDirectory* dir1=f.mkdir("asdasd");       // ".root" dosyasında dizin oluşturma

    TTree *t_RecoH = new TTree("RecoHiggs", "jet3 + jet4 -> H");
    //t_RecoDe1->SetDirectory(dir1);    // ".root" dosyasında dizin oluşturma
    Double_t fields_t_RecoH[numOfFields_TLorentzVector];
    const char* prefix_t_RecoH = "h"; // must start with lowercase letter, dont know the stupid reason for that
    initializeTTree4TLorentzVector(t_RecoH, fields_t_RecoH, prefix_t_RecoH);

    // create object on stack
    //TH1F histMass_RecoZ("Mass_RecoZ", "mass of recontructed Z", 100, 0.0, 200000);
    //TTree t_RecoZ("RecoZ", "e+e- -> Z");

    int jet_size = 4; // min number of jets we want to observe in the event

    TLorentzVector jet3, jet4;
    TLorentzVector reconstructed_H;

    int* indices_JetPT_descending;
    // indices of the "Jet" sorted such that 
    // indices_JetPT_descending[0] matches the jet with max. PT
    // indices_JetPT_descending[len-1] matches the jet with min. PT
    int index_3rdMaxPT;
    int index_4thMaxPT;

    bool can_reconstruct_Z;
    int electron_size = 2; // number of electrons we want to observe in the event
    int mu_size = 2; // number of muons we want to observe in the event

    Long64_t nentries = e6.fChain->GetEntriesFast();

    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry = 0; jentry < nentries; jentry++) {
        Long64_t ientry = e6.LoadTree(jentry);
        if (ientry < 0) break;
        nb = e6.fChain->GetEntry(jentry);
        nbytes += nb;

        // if (Cut(ientry) < 0) continue;

        can_reconstruct_Z = (e6.Electron_size == electron_size) || (e6.Muon_size == mu_size);

        if (e6.Jet_size >= jet_size && can_reconstruct_Z) {

            indices_JetPT_descending = sortIndices_Descending(e6.Jet_PT, e6.Jet_size);
            index_3rdMaxPT = indices_JetPT_descending[2];
            index_4thMaxPT = indices_JetPT_descending[3];

            jet3.SetPtEtaPhiM(e6.Jet_PT[index_3rdMaxPT], e6.Jet_Eta[index_3rdMaxPT], e6.Jet_Phi[index_3rdMaxPT], e6.Jet_Mass[index_3rdMaxPT]);
            jet4.SetPtEtaPhiM(e6.Jet_PT[index_4thMaxPT], e6.Jet_Eta[index_4thMaxPT], e6.Jet_Phi[index_4thMaxPT], e6.Jet_Mass[index_4thMaxPT]);

            reconstructed_H = jet3 + jet4;

            fillTTree4LorentzVector(t_RecoH, fields_t_RecoH, reconstructed_H);

        }

    }
    //    histMass_RecoZ.Draw(); // does not work, generates empty canvas
    //    histMass_RecoZ.DrawClone(); // does not work, generates empty canvas
    //histMass_RecoZ.DrawCopy(); // works

    f.Write();
}

void loop_deltaMass_of_deDe() {
    //const char* reconstructed_de_file=loop_Reconstruct_de_outputName;
    //const char* reconstructed_De_file=loop_Reconstruct_De_outputName;

    // files where data for reconstructed de and De are.
    TFile* f_de = new TFile(loop_Reconstruct_de_outputName);
    TFile* f_De = new TFile(loop_Reconstruct_De_outputName);

    // /root.cern.ch/root/html/TDirectoryFile.html#TDirectoryFile:Get
    TTree *t_de1 = (TTree*) f_de->Get(t_Reco_de1_Name);
    TTree *t_de2 = (TTree*) f_de->Get(t_Reco_de2_Name);
    TTree *t_De1 = (TTree*) f_De->Get(t_Reco_De1_Name);
    TTree *t_De2 = (TTree*) f_De->Get(t_Reco_De2_Name);

    Float_t mass_de1, mass_de2, mass_De1, mass_De2;
    string addr_mass_de1 = prefix_t_Reco_de1 + ".M";
    string addr_mass_de2 = prefix_t_Reco_de2 + ".M";
    string addr_mass_De1 = prefix_t_RecoDe1 + ".M";
    string addr_mass_De2 = prefix_t_RecoDe2 + ".M";

    //  root.cern.ch/root/html/TTree.html#TTree:SetBranchAddress@1
    t_de1->SetBranchAddress(addr_mass_de1.c_str(), &mass_de1);
    t_de2->SetBranchAddress(addr_mass_de2.c_str(), &mass_de2);
    t_De1->SetBranchAddress(addr_mass_De1.c_str(), &mass_De1);
    t_De2->SetBranchAddress(addr_mass_De2.c_str(), &mass_De2);
}

/*
 * Delphes-3.0.5/doc/RootTreeDescription.html
 GenParticle
PID 	particle HEP ID number 	hepevt.idhep[number]
Status 	particle status 	hepevt.isthep[number]
M1 	particle 1st mother 	hepevt.jmohep[number][0] - 1
M2 	particle 2nd mother 	hepevt.jmohep[number][1] - 1
D1 	particle 1st daughter 	hepevt.jdahep[number][0] - 1
D2 	particle last daughter 	hepevt.jdahep[number][1] - 1
Charge 	particle charge 	
Mass 	particle mass 	
E 	particle energy 	hepevt.phep[number][3]
Px 	particle momentum vector (x component) 	hepevt.phep[number][0]
Py 	particle momentum vector (y component) 	hepevt.phep[number][1]
Pz 	particle momentum vector (z component) 	hepevt.phep[number][2]
PT 	particle transverse momentum 	
Eta 	particle pseudorapidity 	
Phi 	particle azimuthal angle 	
Rapidity 	particle rapidity 	
T 	particle vertex position (t component) 	hepevt.vhep[number][3]
X 	particle vertex position (x component) 	hepevt.vhep[number][0]
Y 	particle vertex position (y component) 	hepevt.vhep[number][1]
Z 	particle vertex position (z component) 	hepevt.vhep[number][2]
 */

/*
 * in "initializeTTree4Something()" methods, a big piece of code was redundant. I implemented that piece of code in another method to eliminate redundancy of code. From now on, "initializeTTree4Something()" will call this method instead of executing redundant code.
 */
void initializeTTree(TTree* t, Double_t* adresler, int len_Fields, const char* branchNamePrefix, const char* fields[]) {
    const char* branchName;
    string branchName_str;
    const char* leafList;
    string leafList_str;
    for (int i = 0; i < len_Fields; i++) {
        // + does not work for "const char*"
        //branchName_str = branchNamePrefix + "." + genParticle_Fields[i];      
        branchName_str = string(branchNamePrefix) + "." + string(fields[i]);
        branchName = branchName_str.c_str();

        // + does not work for "const char*"
        //leafList_str = genParticle_Fields[i] + "/D";
        leafList_str = string(fields[i]) + "/D";
        leafList = leafList_str.c_str();

        // http://root.cern.ch/root/html/TTree.html#TTree:Branch
        t->Branch(branchName, &adresler[i], leafList);
    }
}

void initializeTTree4Particle(TTree* t, Double_t* adresler, const char* branchNamePrefix) {

    // Elements of "lorentzVector_Fields" will be used as suffix for branch names
    // Length of "lorentzVector_Fields" is 23. So the "adresler" must be of length 23. The user should have allocated "adresler" with length 23 before calling this function.
    // http://stackoverflow.com/questions/3814804/initializing-a-static-const-char-array
    const char* particle_Fields[] = {"fUniqueID", "fBits", "PID", "Status", "IsPU", "M1", "M2", "D1", "D2", "Charge", "Mass", "E", "Px", "Py", "Pz", "PT", "Eta", "Phi", "Rapidity", "T", "X", "Y", "Z"};

    // http://stackoverflow.com/questions/4108313/how-do-i-find-the-length-of-an-array
    int len_Fields = (sizeof (particle_Fields) / sizeof (*particle_Fields)); // =23

    initializeTTree(t, adresler, len_Fields, branchNamePrefix, particle_Fields);

    /*
    const char* branchName;
    string branchName_str;
    const char* leafList;
    string leafList_str;

    for (int i = 0; i < len_Fields; i++) {
        // + does not work for "const char*"
        //branchName_str = branchNamePrefix + "." + genParticle_Fields[i];      
        branchName_str = string(branchNamePrefix) + "." + string(particle_Fields[i]);
        branchName = branchName_str.c_str();

        // + does not work for "const char*"
        //leafList_str = genParticle_Fields[i] + "/D";
        leafList_str = string(particle_Fields[i]) + "/D";
        leafList = leafList_str.c_str();

        // http://root.cern.ch/root/html/TTree.html#TTree:Branch
        t->Branch(branchName, &adresler[i], leafList);
    }
     */
}

/*
 * fills branches of the given TTree "t". "t" is a TTree that contains all the fields of type "e6_Class.Particle_ ...".
 * Values are taken from the e6_Class "e6". Branches of "t" are filled with values like e6.Particle_PT[i], where "i" is the index of the particle in a particular event.
 * 
 * "adresler" must be the same addresses that were used during the initialization of the "TTree" object.
 * 
 *  http://www.cplusplus.com/doc/tutorial/pointers/
 */
void fillTTree4Particle(TTree* t, Double_t* adresler, e6_Class &e6, int indexOfParticle) {

    adresler[0] = e6.Particle_fUniqueID[indexOfParticle];
    adresler[1] = e6.Particle_fBits[indexOfParticle];
    adresler[2] = e6.Particle_PID[indexOfParticle];
    adresler[3] = e6.Particle_Status[indexOfParticle];
    adresler[4] = e6.Particle_IsPU[indexOfParticle];
    adresler[5] = e6.Particle_M1[indexOfParticle];
    adresler[6] = e6.Particle_M2[indexOfParticle];
    adresler[7] = e6.Particle_D1[indexOfParticle];
    adresler[8] = e6.Particle_D2[indexOfParticle];
    adresler[9] = e6.Particle_Charge[indexOfParticle];
    adresler[10] = e6.Particle_Mass[indexOfParticle];
    adresler[11] = e6.Particle_E[indexOfParticle];
    adresler[12] = e6.Particle_Px[indexOfParticle];
    adresler[13] = e6.Particle_Py[indexOfParticle];
    adresler[14] = e6.Particle_Pz[indexOfParticle];
    adresler[15] = e6.Particle_PT[indexOfParticle];
    adresler[16] = e6.Particle_Eta[indexOfParticle];
    adresler[17] = e6.Particle_Phi[indexOfParticle];
    adresler[18] = e6.Particle_Rapidity[indexOfParticle];
    adresler[19] = e6.Particle_T[indexOfParticle];
    adresler[20] = e6.Particle_X[indexOfParticle];
    adresler[21] = e6.Particle_Y[indexOfParticle];
    adresler[22] = e6.Particle_Z[indexOfParticle];

    t->Fill();
    //delete t;
}

/*
 * fills branches of the given TTree "t", if the PID of "particle" is equal to "pid".
 * 
 * This function may look dummy. The reason why I wrote this function is to minimize lots of if checks in the main code, hence to reduce crowd in the main code. Say, im main program I have 4 different particles whose trees I want to fill. Without this function I would have to write 4 different "if" scopes which makes the main code crowded.
 */
void fillTTree4Particle(TTree* t, Double_t* adresler, e6_Class &e6, int indexOfParticle, int pid) {
    if (pid == abs(e6.Particle_PID[indexOfParticle])) {
        fillTTree4Particle(t, adresler, e6, indexOfParticle);
    }
}

void initializeTTree4TLorentzVector(TTree* t, Double_t* adresler, const char* branchNamePrefix) {

    // Elements of "lorentzVector_Fields" will be used as suffix for branch names
    // Length of "lorentzVector_Fields" is 32. So the "adresler" must be of length 32. The user should have allocated "adresler" with length 32 before calling this function.
    // http://stackoverflow.com/questions/3814804/initializing-a-static-const-char-array
    const char* lorentzVector_Fields[] = {"Beta", "CosTheta", "E", "Energy", "Et", "Et2", "Eta", "Gamma", "M", "M2", "Mag", "Mag2", "Minus", "Mt", "Mt2", "P", "Perp", "Perp2", "Phi", "Plus", "PseudoRapidity", "Pt", "Px", "Py", "Pz", "Rapidity", "Rho", "T", "Theta", "X", "Y", "Z"};

    // http://stackoverflow.com/questions/4108313/how-do-i-find-the-length-of-an-array
    int len_Fields = (sizeof (lorentzVector_Fields) / sizeof (*lorentzVector_Fields)); // =32

    initializeTTree(t, adresler, len_Fields, branchNamePrefix, lorentzVector_Fields);

    /*
        const char* branchName;
        string branchName_str;
        const char* leafList;
        string leafList_str;

        for (int i = 0; i < len_Fields; i++) {
            // + does not work for "const char*"
            //branchName_str = branchNamePrefix + "." + genParticle_Fields[i];      
            branchName_str = string(branchNamePrefix) + "." + string(lorentzVector_Fields[i]);
            branchName = branchName_str.c_str();

            // + does not work for "const char*"
            //leafList_str = genParticle_Fields[i] + "/D";
            leafList_str = string(lorentzVector_Fields[i]) + "/D";
            leafList = leafList_str.c_str();

            // http://root.cern.ch/root/html/TTree.html#TTree:Branch
            t->Branch(branchName, &adresler[i], leafList);
        }
     */
}

/*
 * fills branches of the given TTree "t". "t" is a TTree that contains all the fields of type "TLorentzVector".
 * Values are taken from the TLorentzVector "vec". Branches of "t" are filled with values of the fields of "vec".
 * 
 * "adresler" must be the same addresses that were used during the initialization of the "TTree" object.
 * 
 *  http://www.cplusplus.com/doc/tutorial/pointers/
 */
void fillTTree4LorentzVector(TTree* t, Double_t* adresler, TLorentzVector &vec) {

    adresler[0] = vec.Beta();
    adresler[1] = vec.CosTheta();
    adresler[2] = vec.E();
    adresler[3] = vec.Energy();
    adresler[4] = vec.Et();
    adresler[5] = vec.Et2();
    adresler[6] = vec.Eta();
    adresler[7] = vec.Gamma();
    adresler[8] = vec.M();
    adresler[9] = vec.M2();
    adresler[10] = vec.Mag();
    adresler[11] = vec.Mag2();
    adresler[12] = vec.Minus();
    adresler[13] = vec.Mt();
    adresler[14] = vec.Mt2();
    adresler[15] = vec.P();
    adresler[16] = vec.Perp();
    adresler[17] = vec.Perp2();
    adresler[18] = vec.Phi();
    adresler[19] = vec.Plus();
    adresler[20] = vec.PseudoRapidity();
    adresler[21] = vec.Pt();
    adresler[22] = vec.Px();
    adresler[23] = vec.Py();
    adresler[24] = vec.Pz();
    adresler[25] = vec.Rapidity();
    adresler[26] = vec.Rho();
    adresler[27] = vec.T();
    adresler[28] = vec.Theta();
    adresler[29] = vec.X();
    adresler[30] = vec.Y();
    adresler[31] = vec.Z();

    t->Fill();
    //delete t;
}

/*
 http://www.cplusplus.com/doc/tutorial/pointers/
 */
void initializeTTree4GenParticle(TTree* t, Double_t* adresler, const char* branchNamePrefix) {

    // Elements of "genParticle_Fields" will be used as suffix for branch names
    // Length of "genParticle_Fields" is 20. So the "adresler" must be of length 20. The user should have allocated "adresler" with length 20 before calling this function.
    // http://stackoverflow.com/questions/3814804/initializing-a-static-const-char-array
    const char* genParticle_Fields[] = {"PID", "Status", "M1", "M2", "D1", "D2", "Charge", "Mass", "E", "Px", "Py", "Pz", "PT", "Eta", "Phi", "Rapidity", "T", "X", "Y", "Z"};

    // http://stackoverflow.com/questions/4108313/how-do-i-find-the-length-of-an-array
    int len_Fields = (sizeof (genParticle_Fields) / sizeof (*genParticle_Fields)); // =20

    initializeTTree(t, adresler, len_Fields, branchNamePrefix, genParticle_Fields);
    /*
        const char* branchName;
        string branchName_str;
        const char* leafList;
        string leafList_str;
        for (int i = 0; i < len_Fields; i++) {
            // + does not work for "const char*"
            //branchName_str = branchNamePrefix + "." + genParticle_Fields[i];      
            branchName_str = string(branchNamePrefix) + "." + string(genParticle_Fields[i]);
            branchName = branchName_str.c_str();

            // + does not work for "const char*"
            //leafList_str = genParticle_Fields[i] + "/D";
            leafList_str = string(genParticle_Fields[i]) + "/D";
            leafList = leafList_str.c_str();

            // http://root.cern.ch/root/html/TTree.html#TTree:Branch
            t->Branch(branchName, &adresler[i], leafList);
        }
     */
}

/*
 http://www.cplusplus.com/doc/tutorial/pointers/
 */
void initializeTTree4GenParticle(TTree &t, Double_t* adresler, const char* branchNamePrefix) {

    // Elements of "genParticle_Fields" will be used as suffix for branch names
    // Length of "genParticle_Fields" is 20. So the "adresler" must be of length 20. The user should have allocated "adresler" with length 20 before calling this function.
    // http://stackoverflow.com/questions/3814804/initializing-a-static-const-char-array
    const char* genParticle_Fields[] = {"PID", "Status", "M1", "M2", "D1", "D2", "Charge", "Mass", "E", "Px", "Py", "Pz", "PT", "Eta", "Phi", "Rapidity", "T", "X", "Y", "Z"};

    // http://stackoverflow.com/questions/4108313/how-do-i-find-the-length-of-an-array
    int len_Fields = (sizeof (genParticle_Fields) / sizeof (*genParticle_Fields)); // =20

    initializeTTree(t, adresler, len_Fields, branchNamePrefix, genParticle_Fields);
    /*
    const char* branchName;
    string branchName_str;
    const char* leafList;
    string leafList_str;
    for (int i = 0; i < len_Fields; i++) {
        // + does not work for "const char*"
        //branchName_str = branchNamePrefix + "." + genParticle_Fields[i];      
        branchName_str = string(branchNamePrefix) + "." + string(genParticle_Fields[i]);
        branchName = branchName_str.c_str();

        // + does not work for "const char*"
        //leafList_str = genParticle_Fields[i] + "/D";
        leafList_str = string(genParticle_Fields[i]) + "/D";
        leafList = leafList_str.c_str();

        // http://root.cern.ch/root/html/TTree.html#TTree:Branch
        t.Branch(branchName, &adresler[i], leafList);
    }
     */
}

/*
 * fills branches of the given TTree "t". "t" is a TTree that contains all the fields of type "GenParticle".
 * Values are taken from the GenParticle "particle". Branches of "t" are filled with values of the fields of "particle".
 * 
 * "adresler" must be the same addresses that were used during the initialization of the "TTree" object.
 * 
 *  http://www.cplusplus.com/doc/tutorial/pointers/
 */
void fillTTree4GenParticle(TTree* t, Double_t* adresler, GenParticle* particle) {

    adresler[0] = particle->PID;
    adresler[1] = particle->Status;
    adresler[2] = particle->M1;
    adresler[3] = particle->M2;
    adresler[4] = particle->D1;
    adresler[5] = particle->D2;
    adresler[6] = particle->Charge;
    adresler[7] = particle->Mass;
    adresler[8] = particle->E;
    adresler[9] = particle->Px;
    adresler[10] = particle->Py;
    adresler[11] = particle->Pz;
    adresler[12] = particle->PT;
    adresler[13] = particle->Eta;
    adresler[14] = particle->Phi;
    adresler[15] = particle->Rapidity;
    adresler[16] = particle->T;
    adresler[17] = particle->X;
    adresler[18] = particle->Y;
    adresler[19] = particle->Z;

    t->Fill();
    //delete t;
}

/*
 * fills branches of the given TTree "t", if the PID of "particle" is equal to "pid".
 * 
 * This function may look dummy. The reason why I wrote this function is to minimize lots of if checks in the main code, hence to reduce crowd in the main code. Say, im main program I have 4 different particles whose trees I want to fill. Without this function I would have to write 4 different "if" scopes which makes the main code crowded.
 */
void fillTTree4GenParticle(TTree* t, Double_t* adresler, GenParticle* particle, int pid) {
    if (pid == abs(particle->PID)) {
        fillTTree4GenParticle(t, adresler, particle);
    }
}

#endif	/* BOUNHEP_FNCS_H */

