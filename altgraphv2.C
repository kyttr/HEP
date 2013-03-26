#include <stdio.h>
#include <math.h>
#include "TH1F.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TF1.h"

using namespace std;

//g++ `root-config --cflags --libs` altgraph.C -o altgraph.out

void altgraph() {
    double min=-5;
    double max=10;
    TH1F *h1 = new TH1F("h1", "gaussian", 100, min,max);
    Float_t sigma, mpv;
    sigma = 3.;
    mpv = 2.;
    TF1 *fgaus = new TF1("fgaus", "exp(-((x-[0])/[1])^2)*(x>0)", -5, 10);
    fgaus->SetParameter(0, mpv);
    fgaus->SetParameter(1, sigma);
    h1->FillRandom("fgaus", 1000000);
    TCanvas *c1 = new TCanvas();
    h1->Draw();
    for (int p = 0; p < 20; p++)
        cout << fgaus->GetRandom() << endl;
    c1->SaveAs("alt.pdf");

    TF1 *fitpol0=new TF1("fitpol0","pol0",mpv-sigma,mpv+sigma); // Create the fit function
    h1->Fit("fitpol0","R+");
    
    //TFile f("histos.root", "w");
    TFile f("histos.root","RECREATE");
    h1->Write();
    f.Write();
}

#if !defined(__CINT__) || defined(__MAKECINT__)

int main() {
    altgraph();
    return 0;
}
#endif
