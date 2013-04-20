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

using namespace std;

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	__cplusplus
}
#endif

static const int numOfFields_GenParticle = 20;
static const int numOfFields_TLorentzVector = 32;


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
    Double_t electron_mass=0.0005;      // mass in GeV
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
            fillTTree4LorentzVector(t_RecoZ,fields_t_RecoZ,reconstructed_Z);
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

    /*
     * no need for ".root" file for this small task
     */
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
    Double_t mu_mass=0.10566;      // mass in GeV
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
            fillTTree4LorentzVector(t_RecoZ,fields_t_RecoZ,reconstructed_Z);
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



void initializeTTree4TLorentzVector(TTree* t, Double_t* adresler, const char* branchNamePrefix) {

    // Elements of "lorentzVector_Fields" will be used as suffix for branch names
    // Length of "lorentzVector_Fields" is 32. So the "adresler" must be of length 32. The user should have allocated "adresler" with length 32 before calling this function.
    // http://stackoverflow.com/questions/3814804/initializing-a-static-const-char-array
    const char* lorentzVector_Fields[] = {"Beta", "CosTheta", "E", "Energy", "Et", "Et2", "Eta", "Gamma", "M", "M2", "Mag", "Mag2", "Minus", "Mt", "Mt2", "P", "Perp", "Perp2", "Phi", "Plus", "PseudoRapidity", "Pt", "Px", "Py", "Pz", "Rapidity", "Rho", "T", "Theta", "X", "Y", "Z"};

    // http://stackoverflow.com/questions/4108313/how-do-i-find-the-length-of-an-array
    int len_Fields = (sizeof (lorentzVector_Fields) / sizeof (*lorentzVector_Fields)); // =32

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
 http://www.cplusplus.com/doc/tutorial/pointers/
 */
void initializeTTree4GenParticle(TTree* t, Double_t* adresler, const char* branchNamePrefix) {

    // Elements of "genParticle_Fields" will be used as suffix for branch names
    // Length of "genParticle_Fields" is 20. So the "adresler" must be of length 20. The user should have allocated "adresler" with length 20 before calling this function.
    // http://stackoverflow.com/questions/3814804/initializing-a-static-const-char-array
    const char* genParticle_Fields[] = {"PID", "Status", "M1", "M2", "D1", "D2", "Charge", "Mass", "E", "Px", "Py", "Pz", "PT", "Eta", "Phi", "Rapidity", "T", "X", "Y", "Z"};

    // http://stackoverflow.com/questions/4108313/how-do-i-find-the-length-of-an-array
    int len_Fields = (sizeof (genParticle_Fields) / sizeof (*genParticle_Fields)); // =20

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
}

class GenParticle; // if this does not exist, ~> Warning: Unknown type 'GenParticle' in function argument handled as int

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
    if (pid == particle->PID) {
        fillTTree4GenParticle(t, adresler, particle);
    }
}

#endif	/* BOUNHEP_FNCS_H */

