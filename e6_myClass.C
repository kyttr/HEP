/*
 * I will have different tasks running on the same ".root" file. If I have all of the jobs in the same single file, then the code will get messy. On the other hand, all these tasks will need the same class made by the same ".root" file. I want to have different ROOT macros for different tasks. But all these different macros will have to kind of implement the same class. So, the difference between those files come from the way they implement the methods of this class. For this case, the only method that is implemented differently is "Loop()".
 * 
 * In short, for different tasks I will have different ROOT macros that require the class made by the ".root" file of interest. Each ROOT macro will implement this class' "Loop()" method in its own way.
 */

/* 
 * removed "e6_Class::Loop()", I noticed I can call my tasks within "#ifdef __CINT__" scope, no need for calling "e6_Class::Loop()"
 */

/*
 * plots histogram of the Higgs Mass
 */
#define e6_Class_cxx
#include "e6_Class.h"
#include "bounHEP_Fncs.h"
#include "kayasC_Fncs.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

/* 
 * how to run :
 * root -l .x e6_myClass.C   // works thanks to "__CINT__"
 */

#ifdef __CINT__

int e6_myClass() {
    //TFile *f = new TFile("main42hepMC_E6_v4_by_delphes.root");
    TTree *tree = (TTree*) gDirectory->Get("Delphes");
    e6_Class t(tree);
    //t.Loop();
    //loop_HiggsMass(t);    // can call the task from here, no need for calling "e6_Class::Loop()"


    /*
    // reconstruct Z boson
    string histoFile_str = "loop_Reconstruct_Z.root";
    const char* histoFile_char = histoFile_str.c_str();
    // overwrite existing ".root" file
    TFile f(histoFile_char, "recreate");
    loop_Reconstruct_Z_from_ee(t);
    loop_Reconstruct_Z_from_mumu(t);
    f.Write();
     */

    
//    //loop_Reconstruct_Z(t);
//    //loop_Particle(t);
//    //loop_maxJetPT(t);
//    
//    loop_Reconstruct_Z_from_ee(t);
//    loop_Reconstruct_Z_from_mumu(t);
//
//    loop_Reconstruct_Z(t);
//    loop_Reconstruct_Higgs(t);
//    loop_Reconstruct_de(t);
//    loop_Reconstruct_De(t);
    loop_deltaMass_of_deDe();
//    
//    loop_deltaR_HIGGS_and_JET(t);
    loop_deltaR_Z_and_JET(t);
    
    
    /*
    // merge output files
    // http://stackoverflow.com/questions/9626722/c-string-array-initialization
    string filesToBeMerged[]={loop_Reconstruct_Z_outputName,loop_Reconstruct_Higgs_outputName,loop_Reconstruct_de_outputName,loop_Reconstruct_De_outputName};
    int len_filesToBeMerged=4;
    const char* outputMerge="reconstruction_H_Z_de_De.root";
    mergeROOTFiles(outputMerge, filesToBeMerged, len_filesToBeMerged);
    */
    
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