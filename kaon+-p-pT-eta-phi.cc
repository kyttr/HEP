// http://sask.web.cern.ch/sask/mc4bsm-pythia8.pdf

/*
pythıa kod : olay içindeki kaon+/- bul. Bunların p, pt, eta(pseudo rapidity), phi histogramları çıkar. 
*/

// Headers and Namespaces.
#include "Pythia.h"
// Include Pythia headers.
using namespace Pythia8; // Let Pythia8:: be implicit.
int main() {
// Begin main program.
// Set up generation.
Pythia pythia;
// Declare Pythia object
pythia.readString("Beams:frameType = 4"); // Beam info in LHEF.
//pythia.readString("Beams:LHEF = events_with_decay.lhe");
pythia.readString("Beams:LHEF = MC4BSM-single.lhe");
pythia.init(); // Initialize; incoming pp beams is default.

Hist h_pAbs("Kaon+- (squared) three-momentum magnitude", 100, 0., 30.);	
Hist h_pT("Kaon+- transverse momentum", 100, 0., 20.);
Hist h_eta("Kaon+- pseudorapidity", 100, -5., 5.);
Hist h_phi("Kaon+- phi", 100, -3.5, 3.5);

  // Allow for possibility of a few faulty events.
  int nAbort = 10;
  int iAbort = 0;
  int kaonID=321;
  // Generate event(s).  
  // Begin event loop; generate until none left in input file.     
  for (int iEvent = 0; ; ++iEvent) {

    // Generate events, and check whether generation failed.
    if (!pythia.next()) {

      // If failure because reached end of file then exit event loop.
      if (pythia.info.atEndOfFile()) break; 

      // First few failures write off as "acceptable" errors, then quit.
      if (++iAbort < nAbort) continue;
      break;
    }
                
    for (int i = 0; i < pythia.event.size(); ++i) {
    if (pythia.event[i].id() == kaonID ||  pythia.event[i].id() == -1*kaonID) {
	h_pAbs.fill( pythia.event[i].pAbs() );	
	h_pT.fill( pythia.event[i].pT() );
	h_eta.fill( pythia.event[i].eta() );
	h_phi.fill( pythia.event[i].phi() );
		}
	}
  // End of event loop.        
  }      
// Print run statistics.  
pythia.stat();

//print histograms
cout<<h_pAbs;
cout<<h_pT;
cout<<h_eta;
cout<<h_phi;

return 0;
}
