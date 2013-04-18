/*
 * I will have different tasks running on the same ".root" file. If I have all of the jobs in the same single file, then the code will get messy. On the other hand, all these tasks will need the same class made by the same ".root" file. I want to have different ROOT macros for different tasks. But all these different macros will have to kind of implement the same class. So, the difference between those files come from the way they implement the methods of this class. For this case, the only method that is implemented differently is "Loop()".
 * 
 * In short, for different tasks I will have different ROOT macros that require the class made by the ".root" file of interest. Each ROOT macro will implement this class' "Loop()" method in its own way.
 */

/*
 * plots histogram of the Higgs Mass
 */
#define e6_v3_Class_cxx
#include "e6_v3_Class.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

/* 
 * how to run :
 * root -l .x e6_v3_HiggsMass.C   // works thanks to "__CINT__"
 */

#ifdef __CINT__

int e6_v3_HiggsMass() {
    TFile *f = new TFile("main42hepMC_E6_v3_by_delphes.root");
    TTree *tree = (TTree*) gDirectory->Get("Delphes");
    e6_v3_Class t(tree);
    t.Loop();
    return 0;
}
#endif

void e6_v3_Class::Loop() {
    //   In a ROOT session, you can do:
    //      Root > .L e6_v3_HiggsMass.C
    //      Root > e6_v3_Class t
    //      Root > t.GetEntry(12); // Fill t data members with entry number 12
    //      Root > t.Show();       // Show values of entry 12
    //      Root > t.Show(16);     // Read and show values of entry 16
    //      Root > t.Loop();       // Loop on all entries
    //

    //     This is the loop skeleton where:
    //    jentry is the global entry number in the chain
    //    ientry is the entry number in the current Tree
    //  Note that the argument to GetEntry must be:
    //    jentry for TChain::GetEntry
    //    ientry for TTree::GetEntry and TBranch::GetEntry
    //
    //       To read only selected branches, Insert statements like:
    // METHOD1:
    //    fChain->SetBranchStatus("*",0);  // disable all branches
    //    fChain->SetBranchStatus("branchname",1);  // activate branchname
    // METHOD2: replace line
    //    fChain->GetEntry(jentry);       //read all branches
    //by  b_branchname->GetEntry(ientry); //read only this branch
    if (fChain == 0) return;

    Long64_t nentries = fChain->GetEntriesFast();

    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry = 0; jentry < nentries; jentry++) {
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);
        nbytes += nb;
        // if (Cut(ientry) < 0) continue;
        cout << Electron_size << endl;
    }
}

/*
 * added the following scope to be able to compile this file like c++ file. 
 * Compilation command :
 *  g++ `root-config --cflags --glibs` e6_v3_HiggsMass.C -o e6_v3_HiggsMass.out
 * 
 * But compiling gives lots of errors due to header file "e6_v3_HiggsMass.h"
 * 
 * ref :
 * altgraph.C
 */
#if !defined(__CINT__) || defined(__MAKECINT__)

int main() {
    //e6_v3_Class::Loop();
    e6_v3_Class t;
    t.Loop();
    return 0;
}
#endif