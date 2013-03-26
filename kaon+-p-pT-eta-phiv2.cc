// http://sask.web.cern.ch/sask/mc4bsm-pythia8.pdf

/*
pythıa kod : olay içindeki kaon+/- bul. Bunların p, pt, eta(pseudo rapidity), phi histogramları çıkar. 
 */

// Headers and Namespaces.
#include "TFile.h"
#include "TH1F.h"
#include "TF1.h"
#include "Pythia.h"
// Include Pythia headers.
using namespace Pythia8; // Let Pythia8:: be implicit.

// http://stackoverflow.com/questions/1727881/how-to-use-the-pi-constant-in-c
const double PI = 3.141592653589793238462;


//int main() {

int main(int argc, char* argv[]) {

    // Begin main program.
    // Set up generation.
    Pythia pythia;
    // Declare Pythia object
    pythia.readString("Beams:frameType = 4"); // Beam info in LHEF.
    //pythia.readString("Beams:LHEF = events_with_decay.lhe");
    pythia.readString("Beams:LHEF = MC4BSM-single.lhe");
    pythia.init(); // Initialize; incoming pp beams is default.


    // http://stackoverflow.com/questions/12254980/how-to-get-current-running-file-name-c
    // get the name of this code file
    // argv[0] returns "./<executable_File_Created_After_Compiling_This_File>"
    char* histoFile_char1 = argv[0];

    // http://www.cplusplus.com/reference/string/string/string/
    // http://www.cplusplus.com/reference/string/string/operator=/
    string histoFileExt_str = ".root";
    // http://www.cplusplus.com/reference/string/string/operator+/
    string histoFile_str = histoFile_char1 + histoFileExt_str;

    // http://www.cplusplus.com/reference/string/string/replace/
    // http://stackoverflow.com/questions/3418231/c-replace-part-of-a-string-with-another-string
    // remove the "./" substring in the beginning of histoFile_str
    histoFile_str.replace(0, 2, "");
    // TFile constructor accepts type "const char*"
    const char* histoFile_char = histoFile_str.c_str();
    // overwrite existing ".root" file
    TFile f(histoFile_char, "recreate");

    //    Hist h_pAbs("Kaon+- (squared) three-momentum magnitude", 100, 0., 30.);
    //    Hist h_pT("Kaon+- transverse momentum", 100, 0., 20.);
    //    Hist h_eta("Kaon+- pseudorapidity", 100, -5., 5.);
    //    Hist h_phi("Kaon+- phi", 100, -3.5, 3.5);

    TH1F *h_pAbs = new TH1F("h_pAbs", "Kaon+- (squared) three-momentum magnitude", 100, 0., 30.);
    TH1F *h_pT = new TH1F("h_pT", "Kaon+- transverse momentum", 100, 0., 20.);
    TH1F *h_eta = new TH1F("h_eta", "Kaon+- pseudorapidity", 100, -5., 5.);
    TH1F *h_phi = new TH1F("h_phi", "Kaon+- phi", 100, -3.5, 3.5);

    // Allow for possibility of a few faulty events.
    int nAbort = 10;
    int iAbort = 0;
    int kaonID = 321;
    // Generate event(s).  
    // Begin event loop; generate until none left in input file.     
    for (int iEvent = 0;; ++iEvent) {

        // Generate events, and check whether generation failed.
        if (!pythia.next()) {

            // If failure because reached end of file then exit event loop.
            if (pythia.info.atEndOfFile()) break;

            // First few failures write off as "acceptable" errors, then quit.
            if (++iAbort < nAbort) continue;
            break;
        }

        for (int i = 0; i < pythia.event.size(); ++i) {
            if (pythia.event[i].id() == kaonID || pythia.event[i].id() == -1 * kaonID) {
                h_pAbs->Fill(pythia.event[i].pAbs());
                h_pT->Fill(pythia.event[i].pT());
                h_eta->Fill(pythia.event[i].eta());
                h_phi->Fill(pythia.event[i].phi());
            }
        }
        // End of event loop.        
    }
    // Print run statistics.  
    pythia.stat();

    //print histograms
    cout << h_pAbs;
    cout << h_pT;
    cout << h_eta;
    cout << h_phi;


    /* HEP-fragenAnDr.Ozcanv5
     * 
     * phi histo --> pol0 fit yap.
     */
    // http://stackoverflow.com/questions/1727881/how-to-use-the-pi-constant-in-c
    TF1 *fit_pol0_2_h_phi = new TF1("fit_pol0_2_h_phi", "pol0", -PI, PI); // Create the fit function
    h_phi->Fit("fit_pol0_2_h_phi", "R+");

    // h_pAbs->Write(); // no need for this, it already save all histograms to "TFile"
    f.Write();
    return 0;
}

/*
 * All references :
 * // http://sask.web.cern.ch/sask/mc4bsm-pythia8.pdf
 * // http://stackoverflow.com/questions/1727881/how-to-use-the-pi-constant-in-c
 * // http://stackoverflow.com/questions/12254980/how-to-get-current-running-file-name-c
 * // http://www.cplusplus.com/reference/string/string/string/
 * // http://www.cplusplus.com/reference/string/string/operator=/
 * // http://www.cplusplus.com/reference/string/string/operator+/
 * // http://www.cplusplus.com/reference/string/string/replace/
 * // http://stackoverflow.com/questions/3418231/c-replace-part-of-a-string-with-another-string
 */