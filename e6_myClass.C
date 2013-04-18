/*
 * I will have different tasks running on the same ".root" file. If I have all of the jobs in the same single file, then the code will get messy. On the other hand, all these tasks will need the same class made by the same ".root" file. I want to have different ROOT macros for different tasks. But all these different macros will have to kind of implement the same class. So, the difference between those files come from the way they implement the methods of this class. For this case, the only method that is implemented differently is "Loop()".
 * 
 * In short, for different tasks I will have different ROOT macros that require the class made by the ".root" file of interest. Each ROOT macro will implement this class' "Loop()" method in its own way.
 */

/*
 * plots histogram of the Higgs Mass
 */
#define e6_Class_cxx
#include "e6_Class.h"
#include "bounHEP_Fncs.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

/* 
 * how to run :
 * root -l .x e6_myClass.C   // works thanks to "__CINT__"
 */

#ifdef __CINT__

int e6_myClass() {
    TFile *f = new TFile("main42hepMC_e6_by_delphes.root");
    TTree *tree = (TTree*) gDirectory->Get("Delphes");
    e6_Class t(tree);
    //t.Loop();
    loop_HiggsMass(t);          // can call the task from here, no need for calling "e6_Class::Loop()"
    return 0;
}
#endif

/*
 * added the following scope to be able to compile this file like c++ file. 
 * Compilation command :
 *  g++ `root-config --cflags --glibs` e6_myClass.C -o e6_myClass.out
 * 
 * But compiling gives lots of errors due to header file "e6_myClass.h"
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