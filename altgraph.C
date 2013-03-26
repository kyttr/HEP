#include <stdio.h>
#include <math.h>
#include "TH1F.h"
#include "TF1.h"
#include "TCanvas.h"

using namespace std;

//g++ `root-config --cflags --libs` altgraph.C -o altgraph.out
void altgraph()
{
  TH1F *h1 = new TH1F("h1","gaussian",100,-5,10);
  Float_t sigma,mpv;
  sigma = 3.; mpv = 2.;
  TF1 *fgaus = new TF1("fgaus","exp(-((x-[0])/[1])^2)*(x>0)",-5,10);
  fgaus->SetParameter(0,mpv);
  fgaus->SetParameter(1,sigma);
  h1->FillRandom("fgaus",1000000);
  TCanvas *c1 = new TCanvas();
  h1->Draw();
  for(int p=0; p<20; p++)
  cout<<fgaus->GetRandom()<<endl;
  c1->SaveAs("alt.pdf");
}

#if !defined(__CINT__) || defined(__MAKECINT__)
int main()
{
  altgraph();
  return 0;
}
#endif
