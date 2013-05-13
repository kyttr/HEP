#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "bounHEP_Fncs.h"
#include "kayasC_Fncs.h"

/*
 * Kaya Tatar
 * 
 * how to run :
 * root -l .x mergeROOTFiles.C   // works thanks to "__CINT__"
 */
#ifdef __CINT__

int mergeROOTFiles() {
    return 0;
}
#endif

void mergeROOTFiles() {

    // merge output files
    // http://stackoverflow.com/questions/9626722/c-string-array-initialization
    string filesToBeMerged[] = {loop_Reconstruct_Z_outputName, loop_Reconstruct_Higgs_outputName, loop_Reconstruct_de_outputName, loop_Reconstruct_De_outputName, loop_Reconstruct_All_chiSquared_outputName};
    int len_filesToBeMerged = 5;
    const char* outputMerge = "reconstruction_H_Z_de_De_with_AND_without_chi2.root";
    mergeROOTFiles(outputMerge, filesToBeMerged, len_filesToBeMerged);
}

/*
 * added the following scope to be able to compile this file like c++ file. 
 * Compilation command :
 *  g++ `root-config --cflags --glibs` mergeROOTFiles.C -o mergeROOTFiles.out
 * 
 * But compiling gives lots of errors due to header file "mergeROOTFiles.h"
 * 
 * ref :
 * altgraph.C
 */
#if !defined(__CINT__) || defined(__MAKECINT__)

int main() {

    mergeROOTFiles();
    return 0;
}
#endif