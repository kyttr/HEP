#define e6_Class_cxx
#include "e6_Class.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

/*
 * Kaya Tatar
 * 
 * how to run :
 * root -l .x e6_Class.C   // works thanks to "__CINT__"
 */
#ifdef __CINT__

int e6_Class() {
    TFile *f = new TFile("main42hepMC_e6_by_delphes.root");
    TTree *tree = (TTree*) gDirectory->Get("Delphes");
    e6_Class t(tree);
    t.Loop();
    return 0;
}
#endif

void e6_Class::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L e6_Class.C
//      Root > e6_Class t
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
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   }
}

/*
 * added the following scope to be able to compile this file like c++ file. 
 * Compilation command :
 *  g++ `root-config --cflags --glibs` e6_Class.C -o e6_Class.out
 * 
 * But compiling gives lots of errors due to header file "e6_Class.h"
 * 
 * ref :
 * altgraph.C
 */
#if !defined(__CINT__) || defined(__MAKECINT__)

int main() {
    //e6_Class::Loop();
    e6_Class t;
    t.Loop();
    return 0;
}
#endif