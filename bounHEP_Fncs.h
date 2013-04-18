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

void loop_HiggsMass(e6_Class &t) {
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

