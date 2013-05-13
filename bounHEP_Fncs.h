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
#include "e6_v3_Class.h"
#include "kayasC_Fncs.h"

using namespace std;

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	__cplusplus
}
#endif

int* optimizeJets4ChiSquared(TLorentzVector* jets, TLorentzVector Z);
double chi_squared(float* jet_Mass); // gives wrong results, will not be used any more
double chi_squared(TLorentzVector* jets, TLorentzVector Z);
double chi_squared(TLorentzVector* jets, TLorentzVector Z,double width);
void filterJets(e6_Class &e6);
void filterJets(e6_Class &e6, bool apply_NO_filter);
void reinitialize_Jet_VALID(int length);
void mergeROOTFiles(const char* outFileName, string* fileNames, int numFiles);

void loop_HiggsMass(e6_Class &e6);
void loop_Reconstruct_Z(e6_Class &e6);
void loop_Reconstruct_Z_from_ee(e6_Class &e6);
void loop_Reconstruct_Z_from_mumu(e6_Class &e6);
void loop_Reconstruct_De(e6_Class &e6);
void loop_Reconstruct_de(e6_Class &e6);
void loop_Reconstruct_Higgs(e6_Class &e6);
void loop_Reconstruct_All(e6_Class &e6);
void loop_Particle(e6_Class &e6);
void loop_maxJetPT(e6_Class &e6);
void loop_deltaMass_of_deDe();
void loop_deltaR_HIGGS_and_JET(e6_Class &e6);
void loop_deltaR_Z_and_JET(e6_Class &e6);

class GenParticle; // if this does not exist, ~> Warning: Unknown type 'GenParticle' in function argument handled as int

void initializeTTree4Particle(TTree* t, Double_t* adresler, const char* branchNamePrefix);
void fillTTree4Particle(TTree* t, Double_t* adresler, e6_Class &e6, int indexOfParticle);
void fillTTree4Particle(TTree* t, Double_t* adresler, e6_Class &e6, int indexOfParticle, int pid);
void initializeTTree4TLorentzVector(TTree* t, Double_t* adresler, const char* branchNamePrefix);
void fillTTree4LorentzVector(TTree* t, Double_t* adresler, TLorentzVector &vec);
void initializeTTree4Jet(TTree* t, Double_t* adresler, const char* branchNamePrefix);
void fillTTree4Jet(TTree* t, Double_t* adresler, e6_Class &e6, int indexOfParticle);
void fillTTree4Jet(TTree* t, Double_t* adresler, int index_VALID_jet);
void initializeTTree(TTree* t, Double_t* adresler, int len_Fields, const char* branchNamePrefix, const char* fields[]);
void initializeTTree4GenParticle(TTree* t, Double_t* adresler, const char* branchNamePrefix);
void initializeTTree4GenParticle(TTree &t, Double_t* adresler, const char* branchNamePrefix);
void fillTTree4GenParticle(TTree* t, Double_t* adresler, GenParticle* particle);
void fillTTree4GenParticle(TTree* t, Double_t* adresler, GenParticle* particle, int pid);

static const int numOfFields_GenParticle = 20;
static const int numOfFields_TLorentzVector = 32;
static const int numOfFields_Particle = 32;
static const int numOfFields_Jet = 32;
static const char* loop_Reconstruct_de_outputName = "loop_Reconstruct_de.root"; // output file name of the function loop_Reconstruct_de()
static const char* loop_Reconstruct_De_outputName = "loop_Reconstruct_De.root"; // output file name of the function loop_Reconstruct_De()
static const char* loop_Reconstruct_Higgs_outputName = "loop_Reconstruct_Higgs.root"; // output file name of the function loop_Reconstruct_Higgs()
static const char* loop_Reconstruct_All_outputName = "loop_Reconstruct_All.root"; // output file name of the function loop_Reconstruct_All()
static const char* loop_Reconstruct_Z_outputName = "loop_Reconstruct_Z.root"; // output file name of the function loop_Reconstruct_Z()
static const char* loop_deltaMass_of_deDe_outputName = "loop_deltaMass_of_deDe.root"; // output file name of the function loop_deltaMass_of_deDe()

static const char* t_Reco_de1_Name = "Recode1"; // for "loop_Reconstruct_de()"
static const char* t_Reco_de2_Name = "Recode2"; // for "loop_Reconstruct_de()"
static const char* t_Reco_De1_Name = "RecoDe1"; // for "loop_Reconstruct_De()"
static const char* t_Reco_De2_Name = "RecoDe2"; // for "loop_Reconstruct_De()"

static const char* prefix_t_Reco_de1 = "de1";
static const char* prefix_t_Reco_de2 = "de2";
static const char* prefix_t_RecoDe1 = "De1";
static const char* prefix_t_RecoDe2 = "De2";

/*
 * 3. electron_size=2 olaylarında deltaR(jet, herhangi e)<0.2 olan jetleri analizden çıkar. Çünkü, bu jetler aslında jet değil, elektron. Elektron olmalarına rağmen dedektörde elektron olarak tespit edilmişler. Bu jetlerin analizden çıkarılması bize H,Z,de,De yeniden yaratılmasında yardımcı olabailir. Çünkü, bu jetler jet1 ve jet4 arası bir yerde olabilir.
 * 
 * As pointed above, not all jets will be used during event analysis. According to our restrictions we will disgard some of the jet. So the objects below will keep the jets that we want to study in an event. For us, the jets kept in the below objects are "valid". They are filtered version of the original "Jet"s.
 * 
 * Obviously, I will need to reassign the below objects. For reinitialization of arrays I refer to :
 * http://www.cplusplus.com/forum/general/8498/
 */
volatile Int_t Jet_VALID_;
volatile UInt_t* Jet_VALID_fUniqueID;
volatile UInt_t* Jet_VALID_fBits;
volatile Float_t* Jet_VALID_PT;
volatile Float_t* Jet_VALID_Eta;
volatile Float_t* Jet_VALID_Phi;
volatile Float_t* Jet_VALID_Mass;
volatile Float_t* Jet_VALID_DeltaEta;
volatile Float_t* Jet_VALID_DeltaPhi;
volatile Int_t* Jet_VALID_BTag;
volatile Int_t* Jet_VALID_TauTag;
volatile Int_t* Jet_VALID_Charge;
volatile Float_t* Jet_VALID_EhadOverEem;
volatile TRefArray* Jet_VALID_Constituents;
volatile TRefArray* Jet_VALID_Particles;
volatile Int_t Jet_VALID_size;

static const double limit_deltaR_jet_AND_e = 0.2;
static const double width_chi_squared = 30000;
static const double h_mass = 120; // mass of Higgs boson in GeV
static const double Z_mass = 91.19; // mass of Higgs boson in GeV
static const double de_mass = 500; // mass of de/De in GeV
static const double h_mass_MeV = 120000; // mass of Higgs boson in MeV
static const double Z_mass_MeV = 91190; // mass of Z boson in MeV
static const double de_mass_MeV = 500000; // mass of de/De in GeV

/*
 * "jets" : array of TLorentzVector objects of jets where PT's of these jets are one of the 4 highest PT's in the event.
 *              "jets[0]" = TLorentzVector for jet with highest PT in the event.
 *              "jets[3]" = TLorentzVector for jet with 4th highest PT in the event.
 * 
 * Using permutations of elements of "jets", find the combination that results in the least value for "chi_squared"
 * 
 * return an "array of indices of jets" which result in the least value for "chi_squared"
 * let us call returned array "result"
 *      jet corresponding to result[0] will be used as jet1 : H + jet1 --> de
 *      jet corresponding to result[1] will be used as jet2 : Z + jet2 --> De
 *      jet corresponding to result[2] will be used as jet3 : jet3 + jet4 --> H
 *      jet corresponding to result[3] will be used as jet4 : jet3 + jet4 --> H
 *      
 *      Ex : {3,1,2,0}
 *      jet with 4th highest PT will be used as jet1 : H + jet1 --> de
 *      jet with 2nd highest PT will be used as jet2 : Z + jet2 --> De
 *      jet with 3rd highest PT will be used as jet3 : jet3 + jet4 --> H
 *      jet with 1st highest PT will be used as jet4 : jet3 + jet4 --> H
 * 
 */
int* optimizeJets4ChiSquared(TLorentzVector* jets, TLorentzVector Z) {
    int len = 4;
    // http://stackoverflow.com/questions/8906545/how-to-initialize-a-vector-in-c
    TLorentzVector* jets_tmp = new TLorentzVector[len];
    int indices[] = {0, 1, 2, 3};

    int* result = new int[len];
    double current_chi_squared;
    // http://cplusplus.com/reference/limits/numeric_limits/
    //float min_chi_squared=std::numeric_limits<float>::max();  // make sure this value will be overwritten
    double min_chi_squared = 99999999; // make sure this value will be overwritten

    //http://www.cplusplus.com/reference/algorithm/next_permutation/
    do {
        //jets_tmp.clear();
        jets_tmp[0] = jets[indices[0]];
        jets_tmp[1] = jets[indices[1]];
        jets_tmp[2] = jets[indices[2]];
        jets_tmp[3] = jets[indices[3]];

        current_chi_squared = chi_squared(jets_tmp, Z);

        //                for (int j = 0; j < 4; j++) {
        //                    cout << indices[j] << " , ";
        //                    cout << jets_tmp[j].M() << " , ";
        //                }
        //                cout << "--> " << current_chi_squared << endl;

        // new best combination
        if (current_chi_squared < min_chi_squared) {
            min_chi_squared = current_chi_squared;

            // http://stackoverflow.com/questions/11530678/copy-all-the-array-into-new-array-without-vectors-c?lq=1
            // http://stackoverflow.com/questions/4729046/memcpy-vs-for-loop-whats-the-proper-way-to-copy-an-array-from-a-pointer
            copy(indices, indices + len, result);
        }
    } while (std::next_permutation(indices, indices + len));

    //        for (int j = 0; j < 4; j++) {
    //            cout << result[j] << " , ";
    //        }
    //        cout << "--> " << min_chi_squared << endl;
    //        cout << " eND " << endl;

    return result;
}

/*
 * 4. kai^2=(mass(jet3+jet4)-120)^2/30^2+(mass(jet1+3+4)-mass(Z+jet2))^2/30^2
        her olay için bütün kai^2 kombinasyonlarını bul.
        En küçük kai^2 değeri veren kombinasyonu kullanarak :
                H, Z, de, De yeniden yarat.
                H.Mass histogramı çıkart. Bu histograma Gaussian Fit yap. "Fit" in döndürdüğü "width" değerini kai^2 hesabının paydasındaki 30^2 yerine yaz.
        H.Mass histogramını keskinleştirmek için kai^2 hesabını 1-2 kere döndür. Her döngüde bir önceki "width" değerini kullan. 1. döngü için "width"=30^2 veya "width"=30.
 *  
 * gives wrong results, will not be used any more
 */
double chi_squared(float* jet_Mass) {
    double width = width_chi_squared;

    //http://stackoverflow.com/questions/6321170/is-there-any-advantage-to-using-powx-2-instead-of-xx-with-x-double
    double chi_sqrd = pow(((jet_Mass[2] + jet_Mass[3]) - h_mass_MeV) / width, 2) + pow(((jet_Mass[0] + jet_Mass[2] + jet_Mass[3])-(Z_mass_MeV + jet_Mass[1])) / width, 2);

    return chi_sqrd;
}

double chi_squared(TLorentzVector* jets, TLorentzVector Z) {

    double width = width_chi_squared;
    
    return chi_squared(jets, Z,width);
}

/*
 * 4. kai^2=(mass(jet3+jet4)-120)^2/30^2+(mass(jet1+3+4)-mass(Z+jet2))^2/30^2
        her olay için bütün kai^2 kombinasyonlarını bul.
        En küçük kai^2 değeri veren kombinasyonu kullanarak :
                H, Z, de, De yeniden yarat.
                H.Mass histogramı çıkart. Bu histograma Gaussian Fit yap. "Fit" in döndürdüğü "width" değerini kai^2 hesabının paydasındaki 30^2 yerine yaz.
        H.Mass histogramını keskinleştirmek için kai^2 hesabını 1-2 kere döndür. Her döngüde bir önceki "width" değerini kullan. 1. döngü için "width"=30^2 veya "width"=30.
 * 
 * !! EDIT : I realized that simply adding masses of 2 jets will not give the mass of the resulting particle ( I do not know the reason for the moment ) . 
 *      So,   higgs_mass != jet3_mass + jet4_mass 
 *      But,  higgs_mass  = (vector_jet3 + vector_jet4).mass;
 * I was getting wrong results just because I did not know this fact. It took me 1-1.5 days.
 * 
 */
double chi_squared(TLorentzVector* jets, TLorentzVector Z,double width)
{
    TLorentzVector jet34_higgs; // in general, jet3 + jet4 --> Higgs
    TLorentzVector jet1higgs_de; // assume, H + jet1 --> de
    TLorentzVector jet2Z_De; // assume, Z + jet2 --> De

    jet34_higgs = jets[2] + jets[3];
    jet1higgs_de = jet34_higgs + jets[0];
    jet2Z_De = Z + jets[1];

    double chi_sqrd = pow((jet34_higgs.M() - h_mass_MeV) / width, 2) + pow((jet1higgs_de.M() - jet2Z_De.M()) / width, 2);
    //    cout<<"h="<<jet34_higgs.M()<<" , de="<<jet1higgs_de.M()<<", De="<<jet2Z_De.M()<<endl;

    return chi_sqrd;
}

/*
 * filter out the jets that do not meet our restrictions. 
 * The jets that we want to study in an event will be assigned to "Jet_VALID_" objects.
 * 
 * for now, I will NOT work with "Jet_VALID_Constituents" and "Jet_VALID_Particles"
 * 
 * The method is divided into 3 main steps.
 * 1. determine the number of jets that are VALID. This information is required for reinitialization of arrays
 * 2. Reinitialize "Jet_VALID_" objects. 
 * 3. Assign "Jet_VALID_" objects.
 */
void filterJets(e6_Class &e6) {

    // STEP 1
    int numOfVALID = 0;
    bool* valid_arr = new bool[e6.Jet_size]; // array keeping the validity of jets
    int i, j, k;

    int numTests = 1; // number of conditions a JET should satisfy.
    int numPassed; // number of conditions a JET has satisfied.

    // variables related to filtering
    double deltaR_jet_AND_e1, deltaR_jet_AND_e2;
    TLorentzVector v_e1, v_e2, v_jet;

    // loop over jets
    for (i = 0; i < e6.Jet_size; i++) {
        // at first every jet is INVALID.
        valid_arr[i] = false;
        // at first every jet has passed no test.
        numPassed = 0;

        // CONDITION 1
        // electron_size=2 olaylarında deltaR(jet, herhangi e)<0.2 olan jetleri analizden çıkar.
        if (e6.Electron_size == 2) {

            v_e1.SetPtEtaPhiM(e6.Electron_PT[0], e6.Electron_Eta[0], e6.Electron_Phi[0], -1);
            v_e2.SetPtEtaPhiM(e6.Electron_PT[1], e6.Electron_Eta[1], e6.Electron_Phi[1], -1);
            // for this case, mass of electron is irrelevant.

            v_jet.SetPtEtaPhiM(e6.Jet_PT[i], e6.Jet_Eta[i], e6.Jet_Phi[i], e6.Jet_Mass[i]);

            deltaR_jet_AND_e1 = v_jet.DeltaR(v_e1);
            deltaR_jet_AND_e2 = v_jet.DeltaR(v_e2);

            // check if VALID
            if (deltaR_jet_AND_e1 >= limit_deltaR_jet_AND_e && deltaR_jet_AND_e2 >= limit_deltaR_jet_AND_e) {
                numPassed++;
            }
        } else {
            numPassed++;
        }


        if (numPassed == numTests) {
            numOfVALID++;
            valid_arr[i] = true;
        }
    }

    // STEP 2
    reinitialize_Jet_VALID(numOfVALID);

    // STEP 3
    j = 0;
    for (i = 0; i < e6.Jet_size; i++) {

        if (valid_arr[i]) // this is a valid jet
        {
            Jet_VALID_fUniqueID[j] = e6.Jet_fUniqueID[i];
            Jet_VALID_fBits[j] = e6.Jet_fBits[i];
            Jet_VALID_PT[j] = e6.Jet_PT[i];
            Jet_VALID_Eta[j] = e6.Jet_Eta[i];
            Jet_VALID_Phi[j] = e6.Jet_Phi[i];
            Jet_VALID_Mass[j] = e6.Jet_Mass[i];
            Jet_VALID_DeltaEta[j] = e6.Jet_DeltaEta[i];
            Jet_VALID_DeltaPhi[j] = e6.Jet_DeltaPhi[i];
            Jet_VALID_BTag[j] = e6.Jet_BTag[i];
            Jet_VALID_TauTag[j] = e6.Jet_TauTag[i];
            Jet_VALID_Charge[j] = e6.Jet_Charge[i];
            Jet_VALID_EhadOverEem[j] = e6.Jet_EhadOverEem[i];
            j++;
        }
    }
}

/*
 * do not apply any filter if apply_NO_filter=true
 */
void filterJets(e6_Class &e6, bool apply_NO_filter) {
    if (apply_NO_filter) {

        reinitialize_Jet_VALID(e6.Jet_size);

        // STEP 3
        int i;
        for (i = 0; i < e6.Jet_size; i++) {
            Jet_VALID_fUniqueID[i] = e6.Jet_fUniqueID[i];
            Jet_VALID_fBits[i] = e6.Jet_fBits[i];
            Jet_VALID_PT[i] = e6.Jet_PT[i];
            Jet_VALID_Eta[i] = e6.Jet_Eta[i];
            Jet_VALID_Phi[i] = e6.Jet_Phi[i];
            Jet_VALID_Mass[i] = e6.Jet_Mass[i];
            Jet_VALID_DeltaEta[i] = e6.Jet_DeltaEta[i];
            Jet_VALID_DeltaPhi[i] = e6.Jet_DeltaPhi[i];
            Jet_VALID_BTag[i] = e6.Jet_BTag[i];
            Jet_VALID_TauTag[i] = e6.Jet_TauTag[i];
            Jet_VALID_Charge[i] = e6.Jet_Charge[i];
            Jet_VALID_EhadOverEem[i] = e6.Jet_EhadOverEem[i];
        }
    } else {
        filterJets(e6);
    }
}

void reinitialize_Jet_VALID(int numOfVALID) {

    delete [] Jet_VALID_fUniqueID;
    delete [] Jet_VALID_fBits;
    delete [] Jet_VALID_PT;
    delete [] Jet_VALID_Eta;
    delete [] Jet_VALID_Phi;
    delete [] Jet_VALID_Mass;
    delete [] Jet_VALID_DeltaEta;
    delete [] Jet_VALID_DeltaPhi;
    delete [] Jet_VALID_BTag;
    delete [] Jet_VALID_TauTag;
    delete [] Jet_VALID_Charge;
    delete [] Jet_VALID_EhadOverEem;

    Jet_VALID_size = numOfVALID;
    if (numOfVALID == 0) // avoid the problem of creating an array of size 0.
        return;

    Jet_VALID_fUniqueID = new UInt_t[numOfVALID];
    Jet_VALID_fBits = new UInt_t[numOfVALID];
    Jet_VALID_PT = new Float_t[numOfVALID];
    Jet_VALID_Eta = new Float_t[numOfVALID];
    Jet_VALID_Phi = new Float_t[numOfVALID];
    Jet_VALID_Mass = new Float_t[numOfVALID];
    Jet_VALID_DeltaEta = new Float_t[numOfVALID];
    Jet_VALID_DeltaPhi = new Float_t[numOfVALID];
    Jet_VALID_BTag = new Int_t[numOfVALID];
    Jet_VALID_TauTag = new Int_t[numOfVALID];
    Jet_VALID_Charge = new Int_t[numOfVALID];
    Jet_VALID_EhadOverEem = new Float_t[numOfVALID];
}

/*
 * Farklı işler/metotlar için farklı ".root" dosyaları oluşturma. Hepsini bir ".root" dosyasında topla.
 * 
 * I spent like 1-1.5 hour to find out the necessary code to perform what I had in my mind. Below are some codes that I used, but which did not work the way I wanted
 * 
 *
    const char* newDirName=f_tmp->GetName();
    const char* newDirName = "hgjkl";
    
    f->mkdir(newDirName);	// WORKS

    // try to change directory and write incoming stuff into that directory
    f->cd(newDirName);		
    gDirectory->cd(newDirName);
    gFile->cd(newDirName);

    f->cd();
    f->WriteTObject(t_De1);	// try to write each TTree in the file "f_tmp"
    f->WriteTObject(t_De2);	
    f->WriteTObject(t_de1);
    gDirectory->WriteTObject(t_de2);

    f->WriteTObject(f_tmp);	// try to write directly the file "f_tmp"
                                // does not WORK
 * 
 * EDIT : this method became more complicated and less trivial than I thought first.
 */
void mergeROOTFiles(const char* outFileName, string* fileNames, int numFiles) {
    TFile* f = new TFile(outFileName, "recreate");

    TFile* f_tmp;
    TList* listTmp;
    TList* listKeys;
    TTree* t_tmp;
    const char* keyName;
    string listName;
    int i, j, n;
    for (i = 0; i < numFiles; i++) {

        f_tmp = new TFile(fileNames[i].c_str());
        //f_tmp->pwd();

        listKeys = f_tmp->GetListOfKeys();
        // As far as I understand, that method gets all objects in the file.

        //cout << listKeys->GetEntries() << endl;
        // loop over "keys" of that file
        for (j = 0; j < listKeys->GetEntries(); j++) {
            keyName = listKeys->At(j)->GetName();
            //            cout << keyName << endl;

            // I assume all "keys" in that file correspond to "TTree" objects
            t_tmp = (TTree*) f_tmp->Get(keyName); // without this, the method writes nothing.
            n = t_tmp->GetEntry(); // without this, the method it writes a "TTree" with no branches, hence no histograms. Hence a blank "TTree"
        }

        // As far as I understand, that method gets all objects in the file.
        // EDIT : I understood wrong, now As far as I understand, that method gets objects that are somehow referred or got above. I returns nothing if I do not call "t_tmp = (TTree*) f_tmp->Get(keyName);"
        listTmp = f_tmp->GetList();

        // I dont use default name for the list. To avoid ambiguity, I call each list with the name of the file from which this is list created. To avoid long names, I will erase the ".root" suffix in the name of files. That is why I use "string::replace()" to erase last 5 letters of the file name.
        // http://www.cplusplus.com/reference/string/string/replace/
        // http://stackoverflow.com/questions/3418231/c-replace-part-of-a-string-with-another-string
        listName = fileNames[i];
        //listName.replace(listName.end()-5,listName.end(),"");   // does not work for some stupid reason, maybe because of iterators
        listName.replace(listName.length() - 5, listName.length(), ""); // WORKS
        listTmp->SetName(listName.c_str());


        f->WriteTObject(listTmp);

        // in the next iteration these objects will be reassigned. Doing modification without calling "clear()" causes error.
        f_tmp->Clear();
        listKeys->Clear();
        t_tmp->Clear();
        listTmp->Clear();
    }
}

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

/*
 * loop over particles (I guess these are generated particles) and store their fields to a "TTree"
 * particles considered:
 *      electron
 *      muon
 *      Higgs
 *      Z
 */
void loop_Particle(e6_Class &e6) {
    if (e6.fChain == 0) return;

    string histoFile_str = "loop_Particle.root";
    // TFile constructor accepts type "const char*"
    const char* histoFile_char = histoFile_str.c_str();
    // overwrite existing ".root" file
    TFile f(histoFile_char, "recreate");

    TTree *t_e = new TTree("electron", "generated electrons");
    Double_t fields_t_e[numOfFields_Particle];
    const char* prefix_t_e = "e"; // must start with lowercase letter, dont know the stupid reason for that
    initializeTTree4Particle(t_e, fields_t_e, prefix_t_e);

    TTree *t_mu = new TTree("muon", "generated muons");
    Double_t fields_t_mu[numOfFields_Particle];
    const char* prefix_t_mu = "mu"; // must start with lowercase letter, dont know the stupid reason for that
    initializeTTree4Particle(t_mu, fields_t_mu, prefix_t_mu);

    TTree *t_h = new TTree("higgs", "generated higgs bosons");
    Double_t fields_t_h[numOfFields_Particle];
    const char* prefix_t_h = "h"; // must start with lowercase letter, dont know the stupid reason for that
    initializeTTree4Particle(t_h, fields_t_h, prefix_t_h);

    TTree *t_Z = new TTree("Z", "generated Z bosons");
    Double_t fields_t_Z[numOfFields_Particle];
    const char* prefix_t_Z = "z"; // must start with lowercase letter, dont know the stupid reason for that
    initializeTTree4Particle(t_Z, fields_t_Z, prefix_t_Z);

    int i = 0;
    int electron_ID = 11;
    int muon_ID = 13;
    int h_ID = 25; // pid of Higgs boson
    int Z_ID = 23; // pid of Z boson

    Long64_t nentries = e6.fChain->GetEntriesFast();

    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry = 0; jentry < nentries; jentry++) {
        Long64_t ientry = e6.LoadTree(jentry);
        if (ientry < 0) break;
        nb = e6.fChain->GetEntry(jentry);
        nbytes += nb;
        // if (Cut(ientry) < 0) continue;

        for (i = 0; i < kMaxParticle; i++) {
            fillTTree4Particle(t_e, fields_t_e, e6, i, electron_ID);
            fillTTree4Particle(t_mu, fields_t_mu, e6, i, muon_ID);
            fillTTree4Particle(t_h, fields_t_h, e6, i, h_ID);
            fillTTree4Particle(t_Z, fields_t_Z, e6, i, Z_ID);
        }

    }

    f.Write();
}

/*
 * sorts the jets in an event according to their PT's.
 */
void loop_maxJetPT(e6_Class &e6) {
    if (e6.fChain == 0) return;

    int i;
    int* sorted_indices;
    int len;
    Long64_t nentries = e6.fChain->GetEntriesFast();

    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry = 0; jentry < nentries; jentry++) {
        Long64_t ientry = e6.LoadTree(jentry);
        if (ientry < 0) break;
        nb = e6.fChain->GetEntry(jentry);
        nbytes += nb;
        // if (Cut(ientry) < 0) continue;

        //DRAFT for the method
        //len = (sizeof (e6.Jet_PT) / sizeof (e6.Jet_PT[0]));
        //len=kMaxJet;
        len = e6.Jet_size;
        cout << "LEN : " << len << "\n";
        cout << "JET.PT : ";
        for (i = 0; i < len; i++) {
            cout << e6.Jet_PT[i] << " , ";
        }
        cout << "\n";
        sorted_indices = sortIndices(e6.Jet_PT, len);
        cout << "ind : ";
        for (i = 0; i < len; i++) {
            cout << sorted_indices[i] << " , ";
        }
        cout << "\n";
        //                cout << "JET.PT : ";
        //        for (i = 0; i < len; i++) {
        //            cout << e6.Jet_PT[i] << " , ";
        //        }
        //        cout << "\n";
        cout << "--------------------------------\n";
    }
}

void loop_HiggsMass(e6_Class &e6) {
    if (e6.fChain == 0) return;

    /*
     * no need for ".root" file for this small task
     * 
    string histoFile_str = "e6_loop_HiggsMass.root";
    // TFile constructor accepts type "const char*"
    const char* histoFile_char = histoFile_str.c_str();
    // overwrite existing ".root" file
    TFile f(histoFile_char, "recreate");
     */

    // create object on stack
    TH1F histMass_Higgs("Mass_Higgs", "mass of Higgs", 100, 0.0, 200);
    // create object on heap
    //    TH1F *histMass_Higgs = new TH1F("Mass_Higgs", "mass of Higgs", 100, 0.0, 200);
    int i = 0;
    int h_ID = 25;


    Long64_t nentries = e6.fChain->GetEntriesFast();

    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry = 0; jentry < nentries; jentry++) {
        Long64_t ientry = e6.LoadTree(jentry);
        if (ientry < 0) break;
        nb = e6.fChain->GetEntry(jentry);
        nbytes += nb;
        // if (Cut(ientry) < 0) continue;

        for (i = 0; i < e6.Particle_size; i++) {
            if (e6.Particle_PID[i] == h_ID) {
                histMass_Higgs.Fill(e6.Particle_Mass[i]);
                //                histMass_Higgs->Fill(t.Particle_Mass[i]);
            }
        }
    }
    //    histMass_Higgs.Draw(); // does not work, generates empty canvas
    //    histMass_Higgs.DrawClone(); // does not work, generates empty canvas
    histMass_Higgs.DrawCopy(); // works

    //    histMass_Higgs->Draw();  // does not work, generates empty canvas   
    //    histMass_Higgs->DrawClone(); // does not work, generates empty canvas
    //    histMass_Higgs->DrawCopy(); //works

    //f.Write();
}

/*
 * reconstruct Z boson both from e-e+ and mu-mu+
 * and save the reconstructed Z boson to a tree.
 * I consider events with exactly 2 electrons or events with exactly 2 muons
 * 
 * !! I think, if Z is to be reconstructed in an event, then in the same event we should have Higgs boson to be reconstructed as well. So before reconstructing a Z in an event, I also should check whether this event can reconstruct a Higgs as well.
 * 
 * To reconstruct a Z, one needs 2 muons or 2 electrons.
 * To reconstuct a Higgs, one needs 4 jets (2 of them will be selected).
 */
void loop_Reconstruct_Z(e6_Class &e6) {
    if (e6.fChain == 0) return;

    /*
     * no need for ".root" file for this small task
     */
    string histoFile_str = loop_Reconstruct_Z_outputName;
    // TFile constructor accepts type "const char*"
    const char* histoFile_char = histoFile_str.c_str();
    // overwrite existing ".root" file
    TFile f(histoFile_char, "recreate");

    // reconstruction of Z such that e-e+ -> Z
    TTree *t_RecoZ_ee = new TTree("RecoZ-from-ee", "e-e+ -> Z");
    Double_t fields_t_RecoZ_ee[numOfFields_TLorentzVector];
    const char* prefix_t_RecoZ_ee = "z"; // must start with lowercase letter, dont know the stupid reason for that
    initializeTTree4TLorentzVector(t_RecoZ_ee, fields_t_RecoZ_ee, prefix_t_RecoZ_ee);


    // reconstruction of Z such that mu-mu+ -> Z
    TTree *t_RecoZ_mumu = new TTree("RecoZ-from-mumu", "mu-mu+ -> Z");
    Double_t fields_t_RecoZ_mumu[numOfFields_TLorentzVector];
    const char* prefix_t_RecoZ_mumu = "z"; // must start with lowercase letter, dont know the stupid reason for that
    initializeTTree4TLorentzVector(t_RecoZ_mumu, fields_t_RecoZ_mumu, prefix_t_RecoZ_mumu);

    // both reconstructions
    // reconstruction of Z such that mu-mu+ -> Z or e-e+ -> Z
    TTree *t_RecoZ = new TTree("RecoZ", "mu-mu+ -> Z");
    Double_t fields_t_RecoZ[numOfFields_TLorentzVector];
    const char* prefix_t_RecoZ = "z"; // must start with lowercase letter, dont know the stupid reason for that
    initializeTTree4TLorentzVector(t_RecoZ, fields_t_RecoZ, prefix_t_RecoZ);

    Double_t electron_mass = 0.0005; // mass in GeV
    int electron_size = 2; // number of electrons we want to observe in the event

    TLorentzVector el1, el2;
    TLorentzVector reconstructed_Z_ee;

    Double_t mu_mass = 0.10566; // mass in GeV
    int mu_size = 2; // number of muons we want to observe in the event

    TLorentzVector mu1, mu2;
    TLorentzVector reconstructed_Z_mumu;

    bool can_reconstruct_Higgs;
    int jet_size = 4; // min number of jets we want to observe in the event

    Long64_t nentries = e6.fChain->GetEntriesFast();

    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry = 0; jentry < nentries; jentry++) {
        Long64_t ientry = e6.LoadTree(jentry);
        if (ientry < 0) break;
        nb = e6.fChain->GetEntry(jentry);
        nbytes += nb;
        // if (Cut(ientry) < 0) continue;

        can_reconstruct_Higgs = (e6.Jet_size >= jet_size);

        if (can_reconstruct_Higgs) {
            if (electron_size == e6.Electron_size) {

                el1.SetPtEtaPhiM(e6.Electron_PT[0], e6.Electron_Eta[0], e6.Electron_Phi[0], electron_mass);
                el2.SetPtEtaPhiM(e6.Electron_PT[1], e6.Electron_Eta[1], e6.Electron_Phi[1], electron_mass);

                reconstructed_Z_ee = el1 + el2;
                fillTTree4LorentzVector(t_RecoZ_ee, fields_t_RecoZ_ee, reconstructed_Z_ee);
                fillTTree4LorentzVector(t_RecoZ, fields_t_RecoZ, reconstructed_Z_ee);
            } else if (mu_size == e6.Muon_size) {

                mu1.SetPtEtaPhiM(e6.Muon_PT[0], e6.Muon_Eta[0], e6.Muon_Phi[0], mu_mass);
                mu2.SetPtEtaPhiM(e6.Muon_PT[1], e6.Muon_Eta[1], e6.Muon_Phi[1], mu_mass);

                reconstructed_Z_mumu = mu1 + mu2;
                fillTTree4LorentzVector(t_RecoZ_mumu, fields_t_RecoZ_mumu, reconstructed_Z_mumu);
                fillTTree4LorentzVector(t_RecoZ, fields_t_RecoZ, reconstructed_Z_mumu);
            }
        }
    }
    //    histMass_RecoZ.Draw(); // does not work, generates empty canvas
    //    histMass_RecoZ.DrawClone(); // does not work, generates empty canvas
    //histMass_RecoZ.DrawCopy(); // works

    //t_RecoZ.Draw();
    //t_RecoZ.DrawClone();
    //t_RecoZ.StartViewer();
    //t_RecoZ_ee.Draw("z.M");

    f.Write();
}

/*
 * reconstruct Z boson from e-e+ and save the reconstructed Z boson to a tree.
 * I consider events with exactly 2 electrons
 */
void loop_Reconstruct_Z_from_ee(e6_Class &e6) {
    if (e6.fChain == 0) return;

    /*
     * no need for ".root" file for this small task
     */
    string histoFile_str = "loop_Reconstruct_Z_from_ee.root";
    // TFile constructor accepts type "const char*"
    const char* histoFile_char = histoFile_str.c_str();
    // overwrite existing ".root" file
    TFile f(histoFile_char, "recreate");

    TTree *t_RecoZ = new TTree("RecoZ", "e-e+ -> Z");
    Double_t fields_t_RecoZ[numOfFields_TLorentzVector];
    const char* prefix_t_RecoZ = "z"; // must start with lowercase letter, dont know the stupid reason for that
    initializeTTree4TLorentzVector(t_RecoZ, fields_t_RecoZ, prefix_t_RecoZ);

    // create object on stack
    //TH1F histMass_RecoZ("Mass_RecoZ", "mass of recontructed Z", 100, 0.0, 200000);
    //TTree t_RecoZ("RecoZ", "e+e- -> Z");

    int i = 0;
    //    int electron_ID = 11;
    Double_t electron_mass = 0.0005; // mass in GeV
    int electron_size = 2; // number of electrons we want to observe in the event

    TLorentzVector el1, el2;
    TLorentzVector reconstructed_Z;

    Long64_t nentries = e6.fChain->GetEntriesFast();

    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry = 0; jentry < nentries; jentry++) {
        Long64_t ientry = e6.LoadTree(jentry);
        if (ientry < 0) break;
        nb = e6.fChain->GetEntry(jentry);
        nbytes += nb;
        // if (Cut(ientry) < 0) continue;
        if (electron_size == e6.Electron_size) {

            el1.SetPtEtaPhiM(e6.Electron_PT[0], e6.Electron_Eta[0], e6.Electron_Phi[0], electron_mass);
            el2.SetPtEtaPhiM(e6.Electron_PT[1], e6.Electron_Eta[1], e6.Electron_Phi[1], electron_mass);

            reconstructed_Z = el1 + el2;
            fillTTree4LorentzVector(t_RecoZ, fields_t_RecoZ, reconstructed_Z);
        }
    }
    //    histMass_RecoZ.Draw(); // does not work, generates empty canvas
    //    histMass_RecoZ.DrawClone(); // does not work, generates empty canvas
    //histMass_RecoZ.DrawCopy(); // works

    //t_RecoZ.Draw();
    //t_RecoZ.DrawClone();
    //t_RecoZ.StartViewer();
    //t_RecoZ.Draw("z.M");

    f.Write();
}

/*
 * reconstruct Z boson from mu-mu+ and save the reconstructed Z boson to a tree.
 * I consider events with exactly 2 muons
 */
void loop_Reconstruct_Z_from_mumu(e6_Class &e6) {
    if (e6.fChain == 0) return;

    string histoFile_str = "loop_Reconstruct_Z_from_mumu.root";
    // TFile constructor accepts type "const char*"
    const char* histoFile_char = histoFile_str.c_str();
    // overwrite existing ".root" file
    TFile f(histoFile_char, "recreate");

    TTree *t_RecoZ = new TTree("RecoZ", "mu-mu+ -> Z");
    Double_t fields_t_RecoZ[numOfFields_TLorentzVector];
    const char* prefix_t_RecoZ = "z"; // must start with lowercase letter, dont know the stupid reason for that
    initializeTTree4TLorentzVector(t_RecoZ, fields_t_RecoZ, prefix_t_RecoZ);

    // create object on stack
    //TH1F histMass_RecoZ("Mass_RecoZ", "mass of recontructed Z", 100, 0.0, 200000);
    //TTree t_RecoZ("RecoZ", "e+e- -> Z");

    int i = 0;
    Double_t mu_mass = 0.10566; // mass in GeV
    int mu_size = 2; // number of muons we want to observe in the event

    TLorentzVector mu1, mu2;
    TLorentzVector reconstructed_Z;

    Long64_t nentries = e6.fChain->GetEntriesFast();

    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry = 0; jentry < nentries; jentry++) {
        Long64_t ientry = e6.LoadTree(jentry);
        if (ientry < 0) break;
        nb = e6.fChain->GetEntry(jentry);
        nbytes += nb;
        // if (Cut(ientry) < 0) continue;
        if (mu_size == e6.Muon_size) {

            mu1.SetPtEtaPhiM(e6.Muon_PT[0], e6.Muon_Eta[0], e6.Muon_Phi[0], mu_mass);
            mu2.SetPtEtaPhiM(e6.Muon_PT[1], e6.Muon_Eta[1], e6.Muon_Phi[1], mu_mass);

            reconstructed_Z = mu1 + mu2;
            fillTTree4LorentzVector(t_RecoZ, fields_t_RecoZ, reconstructed_Z);
        }
    }
    //    histMass_RecoZ.Draw(); // does not work, generates empty canvas
    //    histMass_RecoZ.DrawClone(); // does not work, generates empty canvas
    //histMass_RecoZ.DrawCopy(); // works

    //t_RecoZ.Draw();
    //t_RecoZ.DrawClone();
    //t_RecoZ.StartViewer();
    //t_RecoZ.Draw("z.M");

    f.Write();
}

/*  
 * De'yi "Z bozonu+jet" ikilisi ile yeniden yarat (reconstruct De).
 *    1. jet = PT'si en yüksek olan jet
 *    2. jet = PT'si 2. en yüksek olan jet
 */
void loop_Reconstruct_De(e6_Class &e6) {

    string histoFile_str = loop_Reconstruct_De_outputName;
    // TFile constructor accepts type "const char*"
    const char* histoFile_char = histoFile_str.c_str();
    // overwrite existing ".root" file
    TFile f(histoFile_char, "recreate");
    //TDirectory* dir1=f.mkdir("asdasd");       // ".root" dosyasında dizin oluşturma

    //TTree *t_RecoDe1 = new TTree("RecoDe1", "Z + jet1 -> De");
    TTree *t_RecoDe1 = new TTree(t_Reco_De1_Name, "Z + jet1 -> De");
    //t_RecoDe1->SetDirectory(dir1);    // ".root" dosyasında dizin oluşturma
    Double_t fields_t_RecoDe1[numOfFields_TLorentzVector];
    //const char* prefix_t_RecoDe1 = "De1"; // must start with lowercase letter, dont know the stupid reason for that
    initializeTTree4TLorentzVector(t_RecoDe1, fields_t_RecoDe1, prefix_t_RecoDe1);

    //TTree *t_RecoDe2 = new TTree("RecoDe2", "Z + jet2 -> De");
    TTree *t_RecoDe2 = new TTree(t_Reco_De2_Name, "Z + jet2 -> De");
    Double_t fields_t_RecoDe2[numOfFields_TLorentzVector];
    //const char* prefix_t_RecoDe2 = "De2"; // must start with lowercase letter, dont know the stupid reason for that
    initializeTTree4TLorentzVector(t_RecoDe2, fields_t_RecoDe2, prefix_t_RecoDe2);

    // create object on stack
    //TH1F histMass_RecoZ("Mass_RecoZ", "mass of recontructed Z", 100, 0.0, 200000);
    //TTree t_RecoZ("RecoZ", "e+e- -> Z");

    int i = 0;
    Double_t electron_mass = 0.0005; // mass in GeV
    int electron_size = 2; // number of electrons we want to observe in the event

    TLorentzVector el1, el2;

    Double_t mu_mass = 0.10566; // mass in GeV
    int mu_size = 2; // number of muons we want to observe in the event

    TLorentzVector mu1, mu2;


    TLorentzVector reconstructed_Z;
    TLorentzVector jet1, jet2;
    TLorentzVector reconstructed_De1, reconstructed_De2;

    int* indices_JetPT_descending;
    // indices of the "Jet" sorted such that 
    // indices_JetPT_descending[0] matches the jet with max. PT
    // indices_JetPT_descending[len-1] matches the jet with min. PT
    int index_MaxPT;
    int index_2ndMaxPT;

    bool can_reconstruct_Higgs;
    int jet_size = 4; // min number of jets we want to observe in the event

    Long64_t nentries = e6.fChain->GetEntriesFast();

    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry = 0; jentry < nentries; jentry++) {
        Long64_t ientry = e6.LoadTree(jentry);
        if (ientry < 0) break;
        nb = e6.fChain->GetEntry(jentry);
        nbytes += nb;

        // NOW, this method uses filtered version of JETs.
        filterJets(e6);
        //        cout << e6.Jet_size << " , " << Jet_VALID_size << endl;        

        indices_JetPT_descending = sortIndices_Descending(Jet_VALID_PT, Jet_VALID_size);
        index_MaxPT = indices_JetPT_descending[0];
        index_2ndMaxPT = indices_JetPT_descending[1];

        jet1.SetPtEtaPhiM(Jet_VALID_PT[index_MaxPT], Jet_VALID_Eta[index_MaxPT], Jet_VALID_Phi[index_MaxPT], Jet_VALID_Mass[index_MaxPT]);
        jet2.SetPtEtaPhiM(Jet_VALID_PT[index_2ndMaxPT], Jet_VALID_Eta[index_2ndMaxPT], Jet_VALID_Phi[index_2ndMaxPT], Jet_VALID_Mass[index_2ndMaxPT]);

        // if (Cut(ientry) < 0) continue;

        int i3 = indices_JetPT_descending[2];
        int i4 = indices_JetPT_descending[3];
        float a[] = {Jet_VALID_Mass[index_MaxPT], Jet_VALID_Mass[index_2ndMaxPT], Jet_VALID_Mass[i3], Jet_VALID_Mass[i4]};
        //        int* ptr = optimizeJets4ChiSquared(a);
        //        for (int ii = 0; ii < 4; ii++)
        //            cout << ptr[ii] << " , ";
        //        cout << endl;

        can_reconstruct_Higgs = (Jet_VALID_size >= jet_size);

        if (can_reconstruct_Higgs) {
            if (electron_size == e6.Electron_size) {

                el1.SetPtEtaPhiM(e6.Electron_PT[0], e6.Electron_Eta[0], e6.Electron_Phi[0], electron_mass);
                el2.SetPtEtaPhiM(e6.Electron_PT[1], e6.Electron_Eta[1], e6.Electron_Phi[1], electron_mass);

                reconstructed_Z = el1 + el2;

                reconstructed_De1 = reconstructed_Z + jet1;
                reconstructed_De2 = reconstructed_Z + jet2;

                fillTTree4LorentzVector(t_RecoDe1, fields_t_RecoDe1, reconstructed_De1);
                fillTTree4LorentzVector(t_RecoDe2, fields_t_RecoDe2, reconstructed_De2);
            } else if (mu_size == e6.Muon_size) {

                mu1.SetPtEtaPhiM(e6.Muon_PT[0], e6.Muon_Eta[0], e6.Muon_Phi[0], mu_mass);
                mu2.SetPtEtaPhiM(e6.Muon_PT[1], e6.Muon_Eta[1], e6.Muon_Phi[1], mu_mass);

                reconstructed_Z = mu1 + mu2;

                reconstructed_De1 = reconstructed_Z + jet1;
                reconstructed_De2 = reconstructed_Z + jet2;

                fillTTree4LorentzVector(t_RecoDe1, fields_t_RecoDe1, reconstructed_De1);
                fillTTree4LorentzVector(t_RecoDe2, fields_t_RecoDe2, reconstructed_De2);
            }
        }
    }
    //    histMass_RecoZ.Draw(); // does not work, generates empty canvas
    //    histMass_RecoZ.DrawClone(); // does not work, generates empty canvas
    //histMass_RecoZ.DrawCopy(); // works

    f.Write();
}

/*
 * de'yi "H+jet" ile yeniden yarat.
 *  5.1. H + jet1 --> de
 *  5.2. H + jet2 --> de
 *      (jet1 = PT'si en yüksek olan jet , jet2 = PT'si 2. en yüksek olan jet)
 */
void loop_Reconstruct_de(e6_Class &e6) {

    string histoFile_str = loop_Reconstruct_de_outputName;
    // TFile constructor accepts type "const char*"
    const char* histoFile_char = histoFile_str.c_str();
    // overwrite existing ".root" file
    TFile f(histoFile_char, "recreate");
    //TDirectory* dir1=f.mkdir("asdasd");       // ".root" dosyasında dizin oluşturma

    //TTree *t_Reco_de1 = new TTree("Recode1", "H + jet1 -> de");
    TTree *t_Reco_de1 = new TTree(t_Reco_de1_Name, "H + jet1 -> de");
    //t_RecoDe1->SetDirectory(dir1);    // ".root" dosyasında dizin oluşturma
    Double_t fields_t_Reco_de1[numOfFields_TLorentzVector];
    //const char* prefix_t_Reco_de1 = "de1"; // must start with lowercase letter, dont know the stupid reason for that
    initializeTTree4TLorentzVector(t_Reco_de1, fields_t_Reco_de1, prefix_t_Reco_de1);

    //TTree *t_Reco_de2 = new TTree("Recode2", "H + jet2 -> de");
    TTree *t_Reco_de2 = new TTree(t_Reco_de2_Name, "H + jet2 -> de");
    Double_t fields_t_Reco_de2[numOfFields_TLorentzVector];
    //const char* prefix_t_Reco_de2 = "de2"; // must start with lowercase letter, dont know the stupid reason for that
    initializeTTree4TLorentzVector(t_Reco_de2, fields_t_Reco_de2, prefix_t_Reco_de2);

    // create object on stack
    //TH1F histMass_RecoZ("Mass_RecoZ", "mass of recontructed Z", 100, 0.0, 200000);
    //TTree t_RecoZ("RecoZ", "e+e- -> Z");

    int jet_size = 4; // min number of jets we want to observe in the event

    TLorentzVector jet3, jet4;
    TLorentzVector reconstructed_H;

    TLorentzVector jet1, jet2;
    TLorentzVector reconstructed_de1, reconstructed_de2;

    int* indices_JetPT_descending;
    // indices of the "Jet" sorted such that 
    // indices_JetPT_descending[0] matches the jet with max. PT
    // indices_JetPT_descending[len-1] matches the jet with min. PT
    int index_MaxPT;
    int index_2ndMaxPT;
    int index_3rdMaxPT;
    int index_4thMaxPT;

    bool can_reconstruct_Z;
    int electron_size = 2; // number of electrons we want to observe in the event
    int mu_size = 2; // number of muons we want to observe in the event

    Long64_t nentries = e6.fChain->GetEntriesFast();

    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry = 0; jentry < nentries; jentry++) {
        Long64_t ientry = e6.LoadTree(jentry);
        if (ientry < 0) break;
        nb = e6.fChain->GetEntry(jentry);
        nbytes += nb;

        // NOW, this method uses filtered version of JETs.
        filterJets(e6);

        can_reconstruct_Z = (e6.Electron_size == electron_size) || (e6.Muon_size == mu_size);

        // if (Cut(ientry) < 0) continue;
        if (e6.Jet_size >= jet_size && can_reconstruct_Z) {

            indices_JetPT_descending = sortIndices_Descending(Jet_VALID_PT, Jet_VALID_size);

            index_3rdMaxPT = indices_JetPT_descending[2];
            index_4thMaxPT = indices_JetPT_descending[3];
            jet3.SetPtEtaPhiM(Jet_VALID_PT[index_3rdMaxPT], Jet_VALID_Eta[index_3rdMaxPT], Jet_VALID_Phi[index_3rdMaxPT], Jet_VALID_Mass[index_3rdMaxPT]);
            jet4.SetPtEtaPhiM(Jet_VALID_PT[index_4thMaxPT], Jet_VALID_Eta[index_4thMaxPT], Jet_VALID_Phi[index_4thMaxPT], Jet_VALID_Mass[index_4thMaxPT]);

            reconstructed_H = jet3 + jet4;

            index_MaxPT = indices_JetPT_descending[0];
            index_2ndMaxPT = indices_JetPT_descending[1];
            jet1.SetPtEtaPhiM(Jet_VALID_PT[index_MaxPT], Jet_VALID_Eta[index_MaxPT], Jet_VALID_Phi[index_MaxPT], Jet_VALID_Mass[index_MaxPT]);
            jet2.SetPtEtaPhiM(Jet_VALID_PT[index_2ndMaxPT], Jet_VALID_Eta[index_2ndMaxPT], Jet_VALID_Phi[index_2ndMaxPT], Jet_VALID_Mass[index_2ndMaxPT]);

            reconstructed_de1 = reconstructed_H + jet1;
            reconstructed_de2 = reconstructed_H + jet2;

            fillTTree4LorentzVector(t_Reco_de1, fields_t_Reco_de1, reconstructed_de1);
            fillTTree4LorentzVector(t_Reco_de2, fields_t_Reco_de2, reconstructed_de2);
        }
    }
    //    histMass_RecoZ.Draw(); // does not work, generates empty canvas
    //    histMass_RecoZ.DrawClone(); // does not work, generates empty canvas
    //histMass_RecoZ.DrawCopy(); // works

    f.Write();
}

/*  
 * 4. Higgs bozonunu "jet3+jet4" ikilisi ile yeniden yarat (reconstruct Higgs boson).
 *  jet3 =  PT'si 3. en yüksek olan jet
 *  jet4 =  PT'si 4. en yüksek olan jet
 * 
 * !! I think, if Higgs is to be reconstructed in an event, then in the same event we should have Z boson to be reconstructed as well. So before reconstructing a Higgs in an event, I also should check whether this event can reconstruct a Z as well.
 * 
 * To reconstruct a Z, one needs 2 muons or 2 electrons.
 * To reconstuct a Higgs, one needs 4 jets (2 of them will be selected).
 */
void loop_Reconstruct_Higgs(e6_Class &e6) {

    string histoFile_str = loop_Reconstruct_Higgs_outputName;
    // TFile constructor accepts type "const char*"
    const char* histoFile_char = histoFile_str.c_str();
    // overwrite existing ".root" file
    TFile f(histoFile_char, "recreate");
    //TDirectory* dir1=f.mkdir("asdasd");       // ".root" dosyasında dizin oluşturma

    TTree *t_RecoH = new TTree("RecoHiggs", "jet3 + jet4 -> H");
    //t_RecoDe1->SetDirectory(dir1);    // ".root" dosyasında dizin oluşturma
    Double_t fields_t_RecoH[numOfFields_TLorentzVector];
    const char* prefix_t_RecoH = "h"; // must start with lowercase letter, dont know the stupid reason for that
    initializeTTree4TLorentzVector(t_RecoH, fields_t_RecoH, prefix_t_RecoH);

    // create object on stack
    //TH1F histMass_RecoZ("Mass_RecoZ", "mass of recontructed Z", 100, 0.0, 200000);
    //TTree t_RecoZ("RecoZ", "e+e- -> Z");

    int jet_size = 4; // min number of jets we want to observe in the event

    TLorentzVector jet3, jet4;
    TLorentzVector reconstructed_H;

    int* indices_JetPT_descending;
    // indices of the "Jet" sorted such that 
    // indices_JetPT_descending[0] matches the jet with max. PT
    // indices_JetPT_descending[len-1] matches the jet with min. PT
    int index_3rdMaxPT;
    int index_4thMaxPT;

    bool can_reconstruct_Z;
    int electron_size = 2; // number of electrons we want to observe in the event
    int mu_size = 2; // number of muons we want to observe in the event

    Long64_t nentries = e6.fChain->GetEntriesFast();

    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry = 0; jentry < nentries; jentry++) {
        Long64_t ientry = e6.LoadTree(jentry);
        if (ientry < 0) break;
        nb = e6.fChain->GetEntry(jentry);
        nbytes += nb;
        // if (Cut(ientry) < 0) continue;

        // NOW, this method uses filtered version of JETs.
        filterJets(e6);

        can_reconstruct_Z = (e6.Electron_size == electron_size) || (e6.Muon_size == mu_size);

        if (e6.Jet_size >= jet_size && can_reconstruct_Z) {

            indices_JetPT_descending = sortIndices_Descending(Jet_VALID_PT, Jet_VALID_size);
            index_3rdMaxPT = indices_JetPT_descending[2];
            index_4thMaxPT = indices_JetPT_descending[3];

            jet3.SetPtEtaPhiM(Jet_VALID_PT[index_3rdMaxPT], Jet_VALID_Eta[index_3rdMaxPT], Jet_VALID_Phi[index_3rdMaxPT], Jet_VALID_Mass[index_3rdMaxPT]);
            jet4.SetPtEtaPhiM(Jet_VALID_PT[index_4thMaxPT], Jet_VALID_Eta[index_4thMaxPT], Jet_VALID_Phi[index_4thMaxPT], Jet_VALID_Mass[index_4thMaxPT]);

            reconstructed_H = jet3 + jet4;

            fillTTree4LorentzVector(t_RecoH, fields_t_RecoH, reconstructed_H);

        }

    }
    //    histMass_RecoZ.Draw(); // does not work, generates empty canvas
    //    histMass_RecoZ.DrawClone(); // does not work, generates empty canvas
    //histMass_RecoZ.DrawCopy(); // works

    f.Write();
}

/*
 * 4. kai^2=(mass(jet3+jet4)-120)^2/30^2+(mass(jet1+3+4)-mass(Z+jet2))^2/30^2
        her olay için bütün kai^2 kombinasyonlarını bul.
        En küçük kai^2 değeri veren kombinasyonu kullanarak :
                H, Z, de, De yeniden yarat.
                H.Mass histogramı çıkart. Bu histograma Gaussian Fit yap. "Fit" in döndürdüğü "width" değerini kai^2 hesabının paydasındaki 30^2 yerine yaz.
        H.Mass histogramını keskinleştirmek için kai^2 hesabını 1-2 kere döndür. Her döngüde bir önceki "width" değerini kullan. 1. döngü için "width"=30^2 veya "width"=30.
 * 
 *  * !! I think, if Higgs is to be reconstructed in an event, then in the same event we should have Z boson to be reconstructed as well. So before reconstructing a Higgs in an event, I also should check whether this event can reconstruct a Z as well.
 * 
 * To reconstruct a Z, one needs 2 muons or 2 electrons.
 * To reconstuct a Higgs, one needs 4 jets (2 of them will be selected).
 * 
 * This method will employ 4 highest PT jets. Different from other methods, this time no jet usage in reconstructions is fixed. Jets will be used in reconstruction such that chi^2 will be minimized.
 */
void loop_Reconstruct_All(e6_Class &e6) {
    string histoFile_str = loop_Reconstruct_All_outputName;
    // TFile constructor accepts type "const char*"
    const char* histoFile_char = histoFile_str.c_str();
    // overwrite existing ".root" file
    TFile f(histoFile_char, "recreate");
    //TDirectory* dir1=f.mkdir("asdasd");       // ".root" dosyasında dizin oluşturma

    TTree *t_RecoH = new TTree("RecoHiggs", "jet? + jet? -> H");
    Double_t fields_t_RecoH[numOfFields_TLorentzVector];
    const char* prefix_t_RecoH = "h"; // must start with lowercase letter, dont know the stupid reason for that
    initializeTTree4TLorentzVector(t_RecoH, fields_t_RecoH, prefix_t_RecoH);

    // reconstruction of Z such that mu-mu+ -> Z or e-e+ -> Z
    TTree *t_RecoZ = new TTree("RecoZ", "mu-mu+ -> Z or e-e+ -> Z");
    Double_t fields_t_RecoZ[numOfFields_TLorentzVector];
    const char* prefix_t_RecoZ = "z"; // must start with lowercase letter, dont know the stupid reason for that
    initializeTTree4TLorentzVector(t_RecoZ, fields_t_RecoZ, prefix_t_RecoZ);

    TTree *t_RecoDe = new TTree("RecoDe", "Z + jet? -> De");
    //t_RecoDe1->SetDirectory(dir1);    // ".root" dosyasında dizin oluşturma
    Double_t fields_t_Reco_De[numOfFields_TLorentzVector];
    //const char* prefix_t_RecoDe1 = "De1"; // must start with lowercase letter, dont know the stupid reason for that
    initializeTTree4TLorentzVector(t_RecoDe, fields_t_Reco_De, "De");

    TTree *t_Reco_de = new TTree("Recode", "H + jet? -> de");
    Double_t fields_t_Reco_de[numOfFields_TLorentzVector];
    //const char* prefix_t_Reco_de2 = "de2"; // must start with lowercase letter, dont know the stupid reason for tha
    initializeTTree4TLorentzVector(t_Reco_de, fields_t_Reco_de, "de");

    TTree *t_jet_1234 = new TTree("Jets", "within 4 highest PT");
    Double_t fields_t_jet_1234[numOfFields_Jet];
    const char* prefix_t_jet_1234 = "jet"; // must start with lowercase letter, dont know the stupid reason for that
    initializeTTree4Jet(t_jet_1234, fields_t_jet_1234, prefix_t_jet_1234);

    int jet_size = 4; // min number of jets we want to observe in the event

    // objects for reconstruction : jet? + jet? -> H
    TLorentzVector jet3, jet4;
    TLorentzVector reconstructed_H;

    // objects for reconstruction : e-e+ -> Z
    TLorentzVector el1, el2;
    // objects for reconstruction : mu-mu+ -> Z
    TLorentzVector mu1, mu2;
    TLorentzVector reconstructed_Z;

    // objects for reconstruction : H + jet? -> de 
    // objects for reconstruction : Z + jet? -> De 
    TLorentzVector jet1, jet2;
    TLorentzVector reconstructed_de, reconstructed_De;

    int* indices_JetPT_descending;
    // indices of the "Jet" sorted such that 
    // indices_JetPT_descending[0] matches the jet with max. PT
    // indices_JetPT_descending[len-1] matches the jet with min. PT
    int index_MaxPT;
    int index_2ndMaxPT;
    int index_3rdMaxPT;
    int index_4thMaxPT;
    int* indices_MaxPT = new float[jet_size]; // indices of the jets with highest PT in the array "Jet_VALID_PT" 
    int* jet1234_indicesAfterChiSquared; // combination of jet indices which minimizes Chi^2
    int ind_j1, ind_j2, ind_j3, ind_j4; // indices of jets in "Jet_VALID_PT" after calling "optimizeJets4ChiSquared()"

    bool can_reconstruct_Z;
    bool can_reconstruct_Higgs;
    int electron_size = 2; // number of electrons we want to observe in the event
    int mu_size = 2; // number of muons we want to observe in the event

    Double_t electron_mass = 0.0005; // mass in GeV
    Double_t mu_mass = 0.10566; // mass in GeV

    // to be used in chi^2 optimization
    TLorentzVector* jet1234 = new TLorentzVector[jet_size];
    TLorentzVector jet1234_1, jet1234_2, jet1234_3, jet1234_4;

    Long64_t nentries = e6.fChain->GetEntriesFast();

    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry = 0; jentry < nentries; jentry++) {
        Long64_t ientry = e6.LoadTree(jentry);
        if (ientry < 0) break;
        nb = e6.fChain->GetEntry(jentry);
        nbytes += nb;
        // if (Cut(ientry) < 0) continue;

        // NOW, this method uses filtered version of JETs.
        filterJets(e6);
        //        int jetNumDiff=(e6.Jet_size-Jet_VALID_size);
        //        cout<<"------"<<jetNumDiff<<"----------"<<endl;

        // there should be at least 4 jets and (2 electrons or 2 muons) in the event
        can_reconstruct_Higgs = Jet_VALID_size >= jet_size;
        can_reconstruct_Z = (e6.Electron_size == electron_size) || (e6.Muon_size == mu_size);

        // there should be at least 4 jets and (2 electrons or 2 muons) in the event
        if (can_reconstruct_Higgs && can_reconstruct_Z) {
            // Now, we can reconstruct

            // reconstruct Z
            // reconstruction of Z is irrelevant to optimizing Chi^2, has nothing to do with jets
            //   EDIT : With new version of "optimizeJets4ChiSquared" reconstructed Z became relevant to optimizing Chi^2 in that reconstruct Z will be used during optimization of Chi^2, but reconstruct Z will not be effected by that optimization.
            if (electron_size == e6.Electron_size) {

                el1.SetPtEtaPhiM(e6.Electron_PT[0], e6.Electron_Eta[0], e6.Electron_Phi[0], electron_mass);
                el2.SetPtEtaPhiM(e6.Electron_PT[1], e6.Electron_Eta[1], e6.Electron_Phi[1], electron_mass);

                reconstructed_Z = el1 + el2;
            } else if (mu_size == e6.Muon_size) {

                mu1.SetPtEtaPhiM(e6.Muon_PT[0], e6.Muon_Eta[0], e6.Muon_Phi[0], mu_mass);
                mu2.SetPtEtaPhiM(e6.Muon_PT[1], e6.Muon_Eta[1], e6.Muon_Phi[1], mu_mass);

                reconstructed_Z = mu1 + mu2;
            }

            indices_JetPT_descending = sortIndices_Descending(Jet_VALID_PT, Jet_VALID_size);
            index_MaxPT = indices_JetPT_descending[0];
            index_2ndMaxPT = indices_JetPT_descending[1];
            index_3rdMaxPT = indices_JetPT_descending[2];
            index_4thMaxPT = indices_JetPT_descending[3];
            indices_MaxPT[0] = index_MaxPT;
            indices_MaxPT[1] = index_2ndMaxPT;
            indices_MaxPT[2] = index_3rdMaxPT;
            indices_MaxPT[3] = index_4thMaxPT;

            //            for (int ind = 0; ind < Jet_VALID_size; ind++) {
            //                cout << Jet_VALID_PT[ind] << " , ";
            //            }
            //            cout << " END " << endl;
            //
            //            for (int ind = 0; ind < 4; ind++) {
            //                cout << indices_JetPT_descending[ind] << " , ";
            //            }
            //                        cout << " | ";

            // assign the array which stores 4 jets with highest PT
            // for optimization of chi^2 using chi_squared(vector<TLorentzVector> jets, TLorentzVector Z)
            jet1234_1.SetPtEtaPhiM(Jet_VALID_PT[index_MaxPT], Jet_VALID_Eta[index_MaxPT], Jet_VALID_Phi[index_MaxPT], Jet_VALID_Mass[index_MaxPT]);
            jet1234_2.SetPtEtaPhiM(Jet_VALID_PT[index_2ndMaxPT], Jet_VALID_Eta[index_2ndMaxPT], Jet_VALID_Phi[index_2ndMaxPT], Jet_VALID_Mass[index_2ndMaxPT]);
            jet1234_3.SetPtEtaPhiM(Jet_VALID_PT[index_3rdMaxPT], Jet_VALID_Eta[index_3rdMaxPT], Jet_VALID_Phi[index_3rdMaxPT], Jet_VALID_Mass[index_3rdMaxPT]);
            jet1234_4.SetPtEtaPhiM(Jet_VALID_PT[index_4thMaxPT], Jet_VALID_Eta[index_4thMaxPT], Jet_VALID_Phi[index_4thMaxPT], Jet_VALID_Mass[index_4thMaxPT]);
            jet1234[0] = jet1234_1;
            jet1234[1] = jet1234_2;
            jet1234[2] = jet1234_3;
            jet1234[3] = jet1234_4;

            // combination of jet indices which minimizes Chi^2
            jet1234_indicesAfterChiSquared = optimizeJets4ChiSquared(jet1234, reconstructed_Z);

            //            for (int ind = 0; ind < 4; ind++) {
            //                cout << jet1234_indicesAfterChiSquared[ind] << " , ";
            //            }
            //            cout << " | ";

            /*      Ex : {3,1,2,0}
             *      jet with 4th highest PT will be used as jet1 : H + jet1 --> de
             *      jet with 2nd highest PT will be used as jet2 : Z + jet2 --> De
             *      jet with 3rd highest PT will be used as jet3 : jet3 + jet4 --> H
             *      jet with 1st highest PT will be used as jet4 : jet3 + jet4 --> H
             */
            ind_j1 = indices_MaxPT[jet1234_indicesAfterChiSquared[0]];
            ind_j2 = indices_MaxPT[jet1234_indicesAfterChiSquared[1]];
            ind_j3 = indices_MaxPT[jet1234_indicesAfterChiSquared[2]];
            ind_j4 = indices_MaxPT[jet1234_indicesAfterChiSquared[3]];

            //            for (int ind = 0; ind < 4; ind++) {
            //                cout << indices_MaxPT[jet1234_indicesAfterChiSquared[ind]] << " , ";
            //            }
            //            cout << " | " << endl;

            // reconstruct H
            jet3.SetPtEtaPhiM(Jet_VALID_PT[ind_j3], Jet_VALID_Eta[ind_j3], Jet_VALID_Phi[ind_j3], Jet_VALID_Mass[ind_j3]);
            jet4.SetPtEtaPhiM(Jet_VALID_PT[ind_j4], Jet_VALID_Eta[ind_j4], Jet_VALID_Phi[ind_j4], Jet_VALID_Mass[ind_j4]);
            reconstructed_H = jet3 + jet4;

            // reconstruct De
            jet2.SetPtEtaPhiM(Jet_VALID_PT[ind_j2], Jet_VALID_Eta[ind_j2], Jet_VALID_Phi[ind_j2], Jet_VALID_Mass[ind_j2]);
            reconstructed_De = reconstructed_Z + jet2;

            // reconstruct de
            jet1.SetPtEtaPhiM(Jet_VALID_PT[ind_j1], Jet_VALID_Eta[ind_j1], Jet_VALID_Phi[ind_j1], Jet_VALID_Mass[ind_j1]);
            reconstructed_de = reconstructed_H + jet1;

            // fill trees
            fillTTree4LorentzVector(t_RecoZ, fields_t_RecoZ, reconstructed_Z);
            fillTTree4LorentzVector(t_RecoH, fields_t_RecoH, reconstructed_H);
            fillTTree4LorentzVector(t_RecoDe, fields_t_Reco_De, reconstructed_De);
            fillTTree4LorentzVector(t_Reco_de, fields_t_Reco_de, reconstructed_de);
            fillTTree4Jet(t_jet_1234, fields_t_jet_1234, ind_j1);
            fillTTree4Jet(t_jet_1234, fields_t_jet_1234, ind_j2);
            fillTTree4Jet(t_jet_1234, fields_t_jet_1234, ind_j3);
            fillTTree4Jet(t_jet_1234, fields_t_jet_1234, ind_j4);
        }
    }

    f.Write();
}

/*
 * her olayda "deltaMass_of_deDe" yi minimize eden kombinasyon bul. O kombinasyon kullan, histogram çıkart.
 */
void loop_deltaMass_of_deDe() {
    //const char* reconstructed_de_file=loop_Reconstruct_de_outputName;
    //const char* reconstructed_De_file=loop_Reconstruct_De_outputName;

    // files where data for reconstructed de and De are.
    TFile* f_de = new TFile(loop_Reconstruct_de_outputName);
    TFile* f_De = new TFile(loop_Reconstruct_De_outputName);

    // /root.cern.ch/root/html/TDirectoryFile.html#TDirectoryFile:Get
    TTree *t_de1 = (TTree*) f_de->Get(t_Reco_de1_Name);
    TTree *t_de2 = (TTree*) f_de->Get(t_Reco_de2_Name);
    TTree *t_De1 = (TTree*) f_De->Get(t_Reco_De1_Name);
    TTree *t_De2 = (TTree*) f_De->Get(t_Reco_De2_Name);

    Double_t mass_de1, mass_de2, mass_De1, mass_De2;
    string addr_mass_de1 = string(prefix_t_Reco_de1) + ".M";
    string addr_mass_de2 = string(prefix_t_Reco_de2) + ".M";
    string addr_mass_De1 = string(prefix_t_RecoDe1) + ".M";
    string addr_mass_De2 = string(prefix_t_RecoDe2) + ".M";

    //  root.cern.ch/root/html/TTree.html#TTree:SetBranchAddress@1
    t_de1->SetBranchAddress(addr_mass_de1.c_str(), &mass_de1);
    t_de2->SetBranchAddress(addr_mass_de2.c_str(), &mass_de2);
    t_De1->SetBranchAddress(addr_mass_De1.c_str(), &mass_De1);
    t_De2->SetBranchAddress(addr_mass_De2.c_str(), &mass_De2);

    TFile f(loop_deltaMass_of_deDe_outputName, "recreate");
    TTree *t = new TTree("deltaMass", "difference of masses of de and De");
    double delta_j1_j2; // difference of masses if : H + jet1 --> de and Z + jet2 --> De
    double delta_j2_j1; // difference of masses if : H + jet2 --> de and Z + jet1 --> De
    double delta_Min; // minimum of 2 "deltaMass"es in an event
    double de_Mass, De_Mass; // masses of de and De in an event, for which deltaMass is minimized.
    //t->Branch("H+jet1_and_Z+jet2",&delta_j1_j2,"delta_jet1_jet2/D");
    //t->Branch("H+jet2_and_Z+jet1",&delta_j2_j1,"delta_jet2_jet1/D");
    t->Branch("H,jet1_and_Z,jet2", &delta_j1_j2, "delta_jet1_jet2/D");
    t->Branch("H,jet2_and_Z,jet1", &delta_j2_j1, "delta_jet2_jet1/D");
    t->Branch("minimum_deltaMass", &delta_Min, "delta_Min/D");
    t->Branch("de.M_minimizing_deltaMass", &de_Mass, "de_Mass/D");
    t->Branch("De.M_minimizing_deltaMass", &De_Mass, "De_Mass/D");
    //    t->Branch("j1j2",&delta_j1_j2,"delta_jet1_jet2/D");
    //    t->Branch("j2j1",&delta_j2_j1,"delta_jet2_jet1/D");

    //read all entries
    Int_t nentries = (Int_t) t_de1->GetEntries();
    for (Int_t i = 0; i < nentries; i++) {

        // I assume all 4 "TTree" have same number of entries, actually the condition that I imposed made them have same num. of entries.
        t_de1->GetEntry(i);
        t_de2->GetEntry(i);
        t_De1->GetEntry(i);
        t_De2->GetEntry(i);

        delta_j1_j2 = abs(mass_de1 - mass_De2);
        delta_j2_j1 = abs(mass_de2 - mass_De1);
        delta_Min = min(delta_j1_j2, delta_j2_j1);

        // assign masses of de and De in an event, for which deltaMass is minimized.
        if (delta_Min == delta_j1_j2) {
            de_Mass = mass_de1;
            De_Mass = mass_De2;
        } else {
            de_Mass = mass_de2;
            De_Mass = mass_De1;
        }

        t->Fill();
    }

    f.Write();
}

/*
 * Under "Particle" set, Higgs bosons have mass 80 GeV. The true mass is 120 GeV. This method tries to solve this problem.
 * 
 * 1. "Particle" dalında PID=Higgs olan parçacıkları bul. 85<mass<105 olan jetleri bul. Bu Higgs'ler ile jetler arasındaki "deltaR" bul. deltaR=sqrt(deltaEta^2+deltaPhi^2) gibi bir şey.
 */
void loop_deltaR_HIGGS_and_JET(e6_Class & e6) {
    if (e6.fChain == 0) return;

    string histoFile_str = "loop_deltaR_HIGGS_and_JET.root";
    // TFile constructor accepts type "const char*"
    const char* histoFile_char = histoFile_str.c_str();
    // overwrite existing ".root" file
    TFile f(histoFile_char, "recreate");

    // TTree for Higgs bosons
    TTree *t_h = new TTree("higgs", "generated higgs bosons");
    Double_t fields_t_h[numOfFields_Particle];
    const char* prefix_t_h = "h"; // must start with lowercase letter, dont know the stupid reason for that
    initializeTTree4Particle(t_h, fields_t_h, prefix_t_h);

    // TTree for jets inside the mass range
    //    double jet_massMin = 85;
    //    double jet_massMax = 105;
    double jet_massMin = 85000; // IMPORTANT, for the jet mass unit is MeV
    double jet_massMax = 105000; // IMPORTANT, for the jets mass unit is MeV
    // must concatenate one by one ( alttaki kod çalışmıyor, teker teker eklemek gerekiyor.) 
    //string title_t_jet_inRange_Str = "mass in the range [" + jet_massMin + ", " + jet_massMax + "]";
    string title_t_jet_inRange_Str = "mass in the range [";
    title_t_jet_inRange_Str += Form("%.f", jet_massMin);
    title_t_jet_inRange_Str += ", ";
    title_t_jet_inRange_Str += Form("%.f", jet_massMax);
    title_t_jet_inRange_Str += "]";
    const char* title_t_jet_inRange_char = title_t_jet_inRange_Str.c_str();

    TTree *t_jet_inRange = new TTree("Jets", title_t_jet_inRange_char);
    Double_t fields_t_jet_inRange[numOfFields_Jet];
    const char* prefix_t_jet_inRange = "jet"; // must start with lowercase letter, dont know the stupid reason for that
    initializeTTree4Jet(t_jet_inRange, fields_t_jet_inRange, prefix_t_jet_inRange);

    // TTree for deltaR between Higgs and Jet inside the mass range
    TTree *t_deltaR = new TTree("deltaR", "between H and Jet inside the mass range");
    Double_t deltaR_h, deltaR_h_withM120, deltaR_h_withM80;
    t_deltaR->Branch("deltaR", &deltaR_h, "deltaR_h/D");
    t_deltaR->Branch("deltaR_with_h.M=120", &deltaR_h_withM120, "deltaR_h_withM120/D");
    t_deltaR->Branch("deltaR_with_h.M=80", &deltaR_h_withM80, "deltaR_h_withM80/D");

    int i, j;
    int h_ID = 25; // pid of Higgs boson
    double h_massReal = 120; // mass of Higgs in reality
    double h_massSimulation = 80; // mass of Higgs given by simulation

    TLorentzVector h; // for now this Higgs will take the mass given by the simulation, that is 80 GeV.
    TLorentzVector jet;
    TLorentzVector h_withM120, h_withM80;

    Long64_t nentries = e6.fChain->GetEntriesFast();

    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry = 0; jentry < nentries; jentry++) {
        Long64_t ientry = e6.LoadTree(jentry);
        if (ientry < 0) break;
        nb = e6.fChain->GetEntry(jentry);
        nbytes += nb;
        // if (Cut(ientry) < 0) continue;

        // loop over generated particles in the event
        for (i = 0; i < e6.Particle_size; i++) {

            // this particle is Higgs
            if (e6.Particle_PID[i] == h_ID) {

                h.SetPtEtaPhiM(e6.Particle_PT[i], e6.Particle_Eta[i], e6.Particle_Phi[i], e6.Particle_Mass[i]);
                h_withM80.SetPtEtaPhiM(e6.Particle_PT[i], e6.Particle_Eta[i], e6.Particle_Phi[i], h_massSimulation);
                h_withM120.SetPtEtaPhiM(e6.Particle_PT[i], e6.Particle_Eta[i], e6.Particle_Phi[i], h_massReal);

                for (j = 0; j < e6.Jet_size; j++) {
                    if (e6.Jet_Mass[j] >= jet_massMin && e6.Jet_Mass[j] <= jet_massMax) {
                        jet.SetPtEtaPhiM(e6.Jet_PT[j], e6.Jet_Eta[j], e6.Jet_Phi[j], e6.Jet_Mass[j]);

                        deltaR_h = h.DeltaR(jet);
                        deltaR_h_withM120 = h_withM120.DeltaR(jet);
                        deltaR_h_withM80 = h_withM80.DeltaR(jet);
                        t_deltaR->Fill();
                    }
                }

                fillTTree4Particle(t_h, fields_t_h, e6, i, h_ID);
            }
        }

        // loop over jets in the event
        // this loop is for plotting jets inside the mass range
        for (i = 0; i < e6.Jet_size; i++) {
            if (e6.Jet_Mass[i] >= jet_massMin && e6.Jet_Mass[i] <= jet_massMax) {
                fillTTree4Jet(t_jet_inRange, fields_t_jet_inRange, e6, i);
            }
        }
    }

    f.Write();
}

/*     
 * deltaR( true Z,  85<mass<105 olan jet ). deltaR 0'da yükseliyorsa "bu jetler aslında Z imiş," diyeceğiz. Aslında, "loop_deltaR_HIGGS_and_JET" yerine "loop_deltaR_Z_and_JET" diye bir metot çalışacak.
 * 
 * deltaR(Z,jet) histogramları için 3 farklı duruma bakıyorum.
 *      1. kütlesi belirli bir aralıkta olan jetler (85<mass<105 gibi)
 *      2. deltaR(Z,jet) değeri belirli bir limitin altında olan jetler (limit_deltaR = 0.5 gibi)
 *      3. deltaR(Z,jet) değeri en küçük olan jet (her Z için böyle bir jetten tam 1 tane vardır.)
 */
void loop_deltaR_Z_and_JET(e6_Class & e6) {
    if (e6.fChain == 0) return;

    string histoFile_str = "loop_deltaR_Z_and_JET.root";
    // TFile constructor accepts type "const char*"
    const char* histoFile_char = histoFile_str.c_str();
    // overwrite existing ".root" file
    TFile f(histoFile_char, "recreate");

    // TTree for Z bosons
    TTree *t_Z = new TTree("Z-as-Particle", "generated Z bosons");
    Double_t fields_t_Z[numOfFields_Particle];
    const char* prefix_t_Z = "z"; // must start with lowercase letter, dont know the stupid reason for that
    initializeTTree4Particle(t_Z, fields_t_Z, prefix_t_Z);

    // TTree for jets inside the mass range
    //    double jet_massMin = 85;
    //    double jet_massMax = 105;
    double jet_massMin = 85000; // IMPORTANT, for the jet mass unit is MeV
    double jet_massMax = 105000; // IMPORTANT, for the jets mass unit is MeV
    // must concatenate one by one ( alttaki kod çalışmıyor, teker teker eklemek gerekiyor.) 
    //string title_t_jet_inRange_Str = "mass in the range [" + jet_massMin + ", " + jet_massMax + "]";
    string title_t_jet_inRange_Str = "range [";
    title_t_jet_inRange_Str += Form("%.f", jet_massMin);
    title_t_jet_inRange_Str += ", ";
    title_t_jet_inRange_Str += Form("%.f", jet_massMax);
    title_t_jet_inRange_Str += "]";
    const char* title_t_jet_inRange_char = title_t_jet_inRange_Str.c_str();

    TTree *t_jet_inRange = new TTree("Jets-in-mass-Range", title_t_jet_inRange_char);
    Double_t fields_t_jet_inRange[numOfFields_Jet];
    const char* prefix_t_jet_inRange = "jet"; // must start with lowercase letter, dont know the stupid reason for that
    initializeTTree4Jet(t_jet_inRange, fields_t_jet_inRange, prefix_t_jet_inRange);

    // TTree for deltaR between Z and Jet inside the mass range
    TTree *t_deltaR_massRange = new TTree("deltaR-mass-Range", "between Z and Jet inside the mass range");
    Double_t deltaR_Z;
    t_deltaR_massRange->Branch("deltaR_jet_in_Mass_Range", &deltaR_Z, "deltaR_Z_massRange/D");

    // TTree for jets with under limit deltaR(Z,jet)
    double limit_deltaR = 0.5;
    string title_t_jet_limit_deltaR_Str = "limit is ";
    title_t_jet_limit_deltaR_Str += Form("%.2f", limit_deltaR);
    const char* title_t_jet_limit_deltaR_char = title_t_jet_limit_deltaR_Str.c_str();

    TTree *t_jet_limit_deltaR = new TTree("Jets-with-under-limit-deltaR", title_t_jet_limit_deltaR_char);
    Double_t fields_t_jet_limit_deltaR[numOfFields_Jet];
    const char* prefix_t_jet_limit_deltaR = "jet"; // must start with lowercase letter, dont know the stupid reason for that
    initializeTTree4Jet(t_jet_limit_deltaR, fields_t_jet_limit_deltaR, prefix_t_jet_limit_deltaR);

    // TTree for under limit deltaR between Z and Jet
    TTree *t_deltaR_limit = new TTree("deltaR-under-limit", title_t_jet_limit_deltaR_char);
    Double_t deltaR_Z_limit;
    t_deltaR_limit->Branch("deltaR_jet_limit", &deltaR_Z_limit, "deltaR_Z_limit/D");

    // TTree for jets minimizing deltaR(Z,jet) in the event
    TTree *t_jet_min_deltaR = new TTree("Jets-minimizing-deltaR", "jets for which deltaR(Z,jet) is minimum");
    Double_t fields_t_jet_min_deltaR[numOfFields_Jet];
    const char* prefix_t_jet_min_deltaR = "jet"; // must start with lowercase letter, dont know the stupid reason for that
    initializeTTree4Jet(t_jet_min_deltaR, fields_t_jet_min_deltaR, prefix_t_jet_min_deltaR);

    // TTree for minimum deltaR between Z and Jet
    TTree *t_deltaR_min = new TTree("deltaR-min", "deltaR(Z,jet) is minimum");
    Double_t deltaR_Z_min;
    int indexOfJet_with_min_DeltaR;
    t_deltaR_min->Branch("deltaR_jet_min", &deltaR_Z_min, "deltaR_Z_min/D");

    int i, j;
    int Z_ID = 23; // pid of Z boson
    //    double h_massReal = 120; // mass of Higgs in reality
    //    double h_massSimulation = 80; // mass of Higgs given by simulation

    TLorentzVector z;
    TLorentzVector jet;
    //    TLorentzVector h_withM120, h_withM80;

    Long64_t nentries = e6.fChain->GetEntriesFast();

    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry = 0; jentry < nentries; jentry++) {
        Long64_t ientry = e6.LoadTree(jentry);
        if (ientry < 0) break;
        nb = e6.fChain->GetEntry(jentry);
        nbytes += nb;
        // if (Cut(ientry) < 0) continue;

        // loop over generated particles in the event
        for (i = 0; i < e6.Particle_size; i++) {

            // this particle is Z
            if (e6.Particle_PID[i] == Z_ID) {

                z.SetPtEtaPhiM(e6.Particle_PT[i], e6.Particle_Eta[i], e6.Particle_Phi[i], e6.Particle_Mass[i]);

                deltaR_Z_min = 9999; // assign a big value so that it will be overwritten in first iteration easily
                indexOfJet_with_min_DeltaR = -1;
                for (j = 0; j < e6.Jet_size; j++) {

                    jet.SetPtEtaPhiM(e6.Jet_PT[j], e6.Jet_Eta[j], e6.Jet_Phi[j], e6.Jet_Mass[j]);
                    deltaR_Z = z.DeltaR(jet);
                    if (e6.Jet_Mass[j] >= jet_massMin && e6.Jet_Mass[j] <= jet_massMax) {

                        fillTTree4Jet(t_jet_inRange, fields_t_jet_inRange, e6, j);
                        t_deltaR_massRange->Fill();
                    }
                    if (deltaR_Z <= limit_deltaR) {
                        deltaR_Z_limit = deltaR_Z;
                        t_deltaR_limit->Fill();
                        fillTTree4Jet(t_jet_limit_deltaR, fields_t_jet_limit_deltaR, e6, j);
                    }
                    if (deltaR_Z <= deltaR_Z_min) {
                        deltaR_Z_min = deltaR_Z;
                        indexOfJet_with_min_DeltaR = j;
                    }
                }
                fillTTree4Particle(t_jet_min_deltaR, fields_t_jet_min_deltaR, e6, indexOfJet_with_min_DeltaR);
                if (deltaR_Z_min != 9999) {
                    t_deltaR_min->Fill();
                }

                fillTTree4Particle(t_Z, fields_t_Z, e6, i, Z_ID);
            }
        }
    }

    f.Write();
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
 * in "initializeTTree4Something()" methods, a big piece of code was redundant. I implemented that piece of code in another method to eliminate redundancy of code. From now on, "initializeTTree4Something()" will call this method instead of executing redundant code.
 */
void initializeTTree(TTree* t, Double_t* adresler, int len_Fields, const char* branchNamePrefix, const char* fields[]) {
    const char* branchName;
    string branchName_str;
    const char* leafList;
    string leafList_str;
    for (int i = 0; i < len_Fields; i++) {
        // + does not work for "const char*"
        //branchName_str = branchNamePrefix + "." + genParticle_Fields[i];      
        branchName_str = string(branchNamePrefix) + "." + string(fields[i]);
        branchName = branchName_str.c_str();

        // + does not work for "const char*"
        //leafList_str = genParticle_Fields[i] + "/D";
        leafList_str = string(fields[i]) + "/D";
        leafList = leafList_str.c_str();

        // http://root.cern.ch/root/html/TTree.html#TTree:Branch
        t->Branch(branchName, &adresler[i], leafList);
    }
}

void initializeTTree4Particle(TTree* t, Double_t* adresler, const char* branchNamePrefix) {

    // Elements of "lorentzVector_Fields" will be used as suffix for branch names
    // Length of "lorentzVector_Fields" is 23. So the "adresler" must be of length 23. The user should have allocated "adresler" with length 23 before calling this function.
    // http://stackoverflow.com/questions/3814804/initializing-a-static-const-char-array
    const char* particle_Fields[] = {"fUniqueID", "fBits", "PID", "Status", "IsPU", "M1", "M2", "D1", "D2", "Charge", "Mass", "E", "Px", "Py", "Pz", "PT", "Eta", "Phi", "Rapidity", "T", "X", "Y", "Z"};

    // http://stackoverflow.com/questions/4108313/how-do-i-find-the-length-of-an-array
    int len_Fields = (sizeof (particle_Fields) / sizeof (*particle_Fields)); // =23

    initializeTTree(t, adresler, len_Fields, branchNamePrefix, particle_Fields);

    /*
    const char* branchName;
    string branchName_str;
    const char* leafList;
    string leafList_str;

    for (int i = 0; i < len_Fields; i++) {
        // + does not work for "const char*"
        //branchName_str = branchNamePrefix + "." + genParticle_Fields[i];      
        branchName_str = string(branchNamePrefix) + "." + string(particle_Fields[i]);
        branchName = branchName_str.c_str();

        // + does not work for "const char*"
        //leafList_str = genParticle_Fields[i] + "/D";
        leafList_str = string(particle_Fields[i]) + "/D";
        leafList = leafList_str.c_str();

        // http://root.cern.ch/root/html/TTree.html#TTree:Branch
        t->Branch(branchName, &adresler[i], leafList);
    }
     */
}

/*
 * fills branches of the given TTree "t". "t" is a TTree that contains all the fields of type "e6_Class.Particle_ ...".
 * Values are taken from the e6_Class "e6". Branches of "t" are filled with values like e6.Particle_PT[i], where "i" is the index of the particle in a particular event.
 * 
 * "adresler" must be the same addresses that were used during the initialization of the "TTree" object.
 * 
 *  http://www.cplusplus.com/doc/tutorial/pointers/
 */
void fillTTree4Particle(TTree* t, Double_t* adresler, e6_Class &e6, int indexOfParticle) {

    adresler[0] = e6.Particle_fUniqueID[indexOfParticle];
    adresler[1] = e6.Particle_fBits[indexOfParticle];
    adresler[2] = e6.Particle_PID[indexOfParticle];
    adresler[3] = e6.Particle_Status[indexOfParticle];
    adresler[4] = e6.Particle_IsPU[indexOfParticle];
    adresler[5] = e6.Particle_M1[indexOfParticle];
    adresler[6] = e6.Particle_M2[indexOfParticle];
    adresler[7] = e6.Particle_D1[indexOfParticle];
    adresler[8] = e6.Particle_D2[indexOfParticle];
    adresler[9] = e6.Particle_Charge[indexOfParticle];
    adresler[10] = e6.Particle_Mass[indexOfParticle];
    adresler[11] = e6.Particle_E[indexOfParticle];
    adresler[12] = e6.Particle_Px[indexOfParticle];
    adresler[13] = e6.Particle_Py[indexOfParticle];
    adresler[14] = e6.Particle_Pz[indexOfParticle];
    adresler[15] = e6.Particle_PT[indexOfParticle];
    adresler[16] = e6.Particle_Eta[indexOfParticle];
    adresler[17] = e6.Particle_Phi[indexOfParticle];
    adresler[18] = e6.Particle_Rapidity[indexOfParticle];
    adresler[19] = e6.Particle_T[indexOfParticle];
    adresler[20] = e6.Particle_X[indexOfParticle];
    adresler[21] = e6.Particle_Y[indexOfParticle];
    adresler[22] = e6.Particle_Z[indexOfParticle];

    t->Fill();
    //delete t;
}

/*
 * fills branches of the given TTree "t", if the PID of "particle" is equal to "pid".
 * 
 * This function may look dummy. The reason why I wrote this function is to minimize lots of if checks in the main code, hence to reduce crowd in the main code. Say, im main program I have 4 different particles whose trees I want to fill. Without this function I would have to write 4 different "if" scopes which makes the main code crowded.
 */
void fillTTree4Particle(TTree* t, Double_t* adresler, e6_Class &e6, int indexOfParticle, int pid) {
    if (pid == abs(e6.Particle_PID[indexOfParticle])) {
        fillTTree4Particle(t, adresler, e6, indexOfParticle);
    }
}

void initializeTTree4TLorentzVector(TTree* t, Double_t* adresler, const char* branchNamePrefix) {

    // Elements of "lorentzVector_Fields" will be used as suffix for branch names
    // Length of "lorentzVector_Fields" is 32. So the "adresler" must be of length 32. The user should have allocated "adresler" with length 32 before calling this function.
    // http://stackoverflow.com/questions/3814804/initializing-a-static-const-char-array
    const char* lorentzVector_Fields[] = {"Beta", "CosTheta", "E", "Energy", "Et", "Et2", "Eta", "Gamma", "M", "M2", "Mag", "Mag2", "Minus", "Mt", "Mt2", "P", "Perp", "Perp2", "Phi", "Plus", "PseudoRapidity", "Pt", "Px", "Py", "Pz", "Rapidity", "Rho", "T", "Theta", "X", "Y", "Z"};

    // http://stackoverflow.com/questions/4108313/how-do-i-find-the-length-of-an-array
    int len_Fields = (sizeof (lorentzVector_Fields) / sizeof (*lorentzVector_Fields)); // =32

    initializeTTree(t, adresler, len_Fields, branchNamePrefix, lorentzVector_Fields);

    /*
        const char* branchName;
        string branchName_str;
        const char* leafList;
        string leafList_str;

        for (int i = 0; i < len_Fields; i++) {
            // + does not work for "const char*"
            //branchName_str = branchNamePrefix + "." + genParticle_Fields[i];      
            branchName_str = string(branchNamePrefix) + "." + string(lorentzVector_Fields[i]);
            branchName = branchName_str.c_str();

            // + does not work for "const char*"
            //leafList_str = genParticle_Fields[i] + "/D";
            leafList_str = string(lorentzVector_Fields[i]) + "/D";
            leafList = leafList_str.c_str();

            // http://root.cern.ch/root/html/TTree.html#TTree:Branch
            t->Branch(branchName, &adresler[i], leafList);
        }
     */
}

/*
 * fills branches of the given TTree "t". "t" is a TTree that contains all the fields of type "TLorentzVector".
 * Values are taken from the TLorentzVector "vec". Branches of "t" are filled with values of the fields of "vec".
 * 
 * "adresler" must be the same addresses that were used during the initialization of the "TTree" object.
 * 
 *  http://www.cplusplus.com/doc/tutorial/pointers/
 */
void fillTTree4LorentzVector(TTree* t, Double_t* adresler, TLorentzVector & vec) {

    adresler[0] = vec.Beta();
    adresler[1] = vec.CosTheta();
    adresler[2] = vec.E();
    adresler[3] = vec.Energy();
    adresler[4] = vec.Et();
    adresler[5] = vec.Et2();
    adresler[6] = vec.Eta();
    adresler[7] = vec.Gamma();
    adresler[8] = vec.M();
    adresler[9] = vec.M2();
    adresler[10] = vec.Mag();
    adresler[11] = vec.Mag2();
    adresler[12] = vec.Minus();
    adresler[13] = vec.Mt();
    adresler[14] = vec.Mt2();
    adresler[15] = vec.P();
    adresler[16] = vec.Perp();
    adresler[17] = vec.Perp2();
    adresler[18] = vec.Phi();
    adresler[19] = vec.Plus();
    adresler[20] = vec.PseudoRapidity();
    adresler[21] = vec.Pt();
    adresler[22] = vec.Px();
    adresler[23] = vec.Py();
    adresler[24] = vec.Pz();
    adresler[25] = vec.Rapidity();
    adresler[26] = vec.Rho();
    adresler[27] = vec.T();
    adresler[28] = vec.Theta();
    adresler[29] = vec.X();
    adresler[30] = vec.Y();
    adresler[31] = vec.Z();

    t->Fill();
    //delete t;
}

void initializeTTree4Jet(TTree* t, Double_t* adresler, const char* branchNamePrefix) {

    // Elements of "jet_Fields" will be used as suffix for branch names
    // Length of "jet_Fields" is 12. So the "adresler" must be of length 12. The user should have allocated "adresler" with length 12 before calling this function.
    // http://stackoverflow.com/questions/3814804/initializing-a-static-const-char-array
    const char* jet_Fields[] = {"fUniqueID", "fBits", "PT", "Eta", "Phi", "Mass", "DeltaEta", "DeltaPhi", "BTag", "TauTag", "Charge", "EhadOverEem"};

    // http://stackoverflow.com/questions/4108313/how-do-i-find-the-length-of-an-array
    int len_Fields = (sizeof (jet_Fields) / sizeof (*jet_Fields)); // =12

    initializeTTree(t, adresler, len_Fields, branchNamePrefix, jet_Fields);
}

/*
 * fills branches of the given TTree "t". "t" is a TTree that contains all the fields of type "e6_Class.Jet_ ...".
 * Values are taken from the e6_Class "e6". Branches of "t" are filled with values like e6.Jet_PT[i], where "i" is the index of the particle in a particular event.
 * 
 * "adresler" must be the same addresses that were used during the initialization of the "TTree" object.
 * 
 *  http://www.cplusplus.com/doc/tutorial/pointers/
 */
void fillTTree4Jet(TTree* t, Double_t* adresler, e6_Class &e6, int indexOfParticle) {

    adresler[0] = e6.Jet_fUniqueID[indexOfParticle];
    adresler[1] = e6.Jet_fBits[indexOfParticle];
    adresler[2] = e6.Jet_PT[indexOfParticle];
    adresler[3] = e6.Jet_Eta[indexOfParticle];
    adresler[4] = e6.Jet_Phi[indexOfParticle];
    adresler[5] = e6.Jet_Mass[indexOfParticle];
    adresler[6] = e6.Jet_DeltaEta[indexOfParticle];
    adresler[7] = e6.Jet_DeltaPhi[indexOfParticle];
    adresler[8] = e6.Jet_BTag[indexOfParticle];
    adresler[9] = e6.Jet_TauTag[indexOfParticle];
    adresler[10] = e6.Jet_Charge[indexOfParticle];
    adresler[11] = e6.Jet_EhadOverEem[indexOfParticle];

    t->Fill();
}

/*
 * fills branches of the given TTree "t". "t" is a TTree that contains all the fields of type "Jet_VALID_ ...".
 * Values are taken from the "Jet_VALID_ ..." objects. Branches of "t" are filled with values like Jet_VALID_PT[i], where "i" is the index of the particle in a particular event.
 * 
 * "adresler" must be the same addresses that were used during the initialization of the "TTree" object.
 * 
 *  http://www.cplusplus.com/doc/tutorial/pointers/
 */
void fillTTree4Jet(TTree* t, Double_t* adresler, int index_VALID_jet) {

    adresler[0] = Jet_VALID_fUniqueID[index_VALID_jet];
    adresler[1] = Jet_VALID_fBits[index_VALID_jet];
    adresler[2] = Jet_VALID_PT[index_VALID_jet];
    adresler[3] = Jet_VALID_Eta[index_VALID_jet];
    adresler[4] = Jet_VALID_Phi[index_VALID_jet];
    adresler[5] = Jet_VALID_Mass[index_VALID_jet];
    adresler[6] = Jet_VALID_DeltaEta[index_VALID_jet];
    adresler[7] = Jet_VALID_DeltaPhi[index_VALID_jet];
    adresler[8] = Jet_VALID_BTag[index_VALID_jet];
    adresler[9] = Jet_VALID_TauTag[index_VALID_jet];
    adresler[10] = Jet_VALID_Charge[index_VALID_jet];
    adresler[11] = Jet_VALID_EhadOverEem[index_VALID_jet];

    t->Fill();
}

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

    initializeTTree(t, adresler, len_Fields, branchNamePrefix, genParticle_Fields);
    /*
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
     */
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

    initializeTTree(t, adresler, len_Fields, branchNamePrefix, genParticle_Fields);
    /*
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
     */
}

/*
 * fills branches of the given TTree "t". "t" is a TTree that contains all the fields of type "GenParticle".
 * Values are taken from the GenParticle "particle". Branches of "t" are filled with values of the fields of "particle".
 * 
 * "adresler" must be the same addresses that were used during the initialization of the "TTree" object.
 * 
 *  http://www.cplusplus.com/doc/tutorial/pointers/
 */
void fillTTree4GenParticle(TTree* t, Double_t* adresler, GenParticle * particle) {

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
    if (pid == abs(particle->PID)) {
        fillTTree4GenParticle(t, adresler, particle);
    }
}

#endif	/* BOUNHEP_FNCS_H */

