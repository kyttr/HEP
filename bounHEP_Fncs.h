/* 
 * File:   bounHEP_Fncs.h
 * Author: kaya
 *
 * Created on April 17, 2013, 12:06 PM
 */

#ifndef BOUNHEP_FNCS_H
#define	BOUNHEP_FNCS_H

using namespace std;

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	__cplusplus
}
#endif

void trialFnc() {
    cout << "asd" << endl;
}

void initializeTTree4GenParticle(TTree* t, void* adres, const char* nameOfAdres) {
    cout << "qweqwe" << endl;
    t->Branch("deneme_12", adres,nameOfAdres);
    //t->Branch("deneme_12",adres);
    //t.Branch("deneme 12",adres);
    cout << "qwzxcgvhbjwe" << endl;
}

void initializeTTree4GenParticle(TTree &t, void* adres, const char* nameOfAdres) {
    
    t.Branch("deneme_34",adres,nameOfAdres);
    
}

#endif	/* BOUNHEP_FNCS_H */

