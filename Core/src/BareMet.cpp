#include "NeroProducer/Core/interface/BareMet.hpp"
#include "NeroProducer/Core/interface/BareFunctions.hpp"


BareMet::BareMet() : BareP4() {
}

BareMet::~BareMet(){
    BareFunctions::Delete(ptJESUP);
    BareFunctions::Delete(ptJESDOWN);
    BareFunctions::Delete(genP4);
    BareFunctions::Delete(metNoMu);
    BareFunctions::Delete(metPuppi);
    BareFunctions::Delete(metNoHF);
    BareFunctions::Delete(pfMet_e3p0);
    BareFunctions::Delete(trackMet);
}

void BareMet::init(){
    BareP4::init();

    BareFunctions::New(ptJESUP);
    BareFunctions::New(ptJESDOWN);
    BareFunctions::New(genP4);
    BareFunctions::New(metPuppi);


    if ( IsExtend() )
    {
        BareFunctions::New(metNoMu);
        BareFunctions::New(metNoHF);
        BareFunctions::New(pfMet_e3p0);
        BareFunctions::New(trackMet);
    }
}

void BareMet::clear(){
    // This function clear all the internal storage and init it to an arbitrary value
    BareP4::clear();

    ptJESUP -> clear();
    ptJESDOWN -> clear();
    genP4 -> Clear();
    *metPuppi *= 0;

    if (extend_)
    {
        *metNoMu *= 0.;
        *metNoHF *= 0.;
        *pfMet_e3p0 *= 0.;
        *trackMet *= 0.;
    }
}

void BareMet::defineBranches(TTree *t){
    //
    BareP4::defineBranches(t, "met" );
    //
    t->Branch("metPtJESUP","vector<float>",&ptJESUP);
    //
    t->Branch("metPtJESDOWN","vector<float>",&ptJESDOWN);
    //	
    t->Branch("metP4_GEN","TClonesArray", &genP4, 128000, 0);
    //
    t->Branch("metPuppi","TLorentzVector",&metPuppi);

    if ( IsExtend() )
    {
        t->Branch("metNoMu","TLorentzVector",&metNoMu);
        t->Branch("metNoHF","TLorentzVector",&metNoHF);
        //
        t->Branch("pfMet_e3p0","TLorentzVector",&pfMet_e3p0);
        //
        t->Branch("trackMet","TLorentzVector",&trackMet);
        // calo Met
        t->Branch("caloMet_Pt",&caloMet_Pt,"caloMet_Pt/F");
        t->Branch("caloMet_Phi",&caloMet_Phi,"caloMet_Phi/F");
        t->Branch("caloMet_SumEt",&caloMet_SumEt,"caloMet_SumEt/F");
    }
    //
}

void BareMet::setBranchAddresses(TTree *t){

    BareP4::setBranchAddresses(t,"met");

    BareFunctions::SetBranchAddress(t,"metPtJESUP"	,&ptJESUP);
    BareFunctions::SetBranchAddress(t,"metPtJESDOWN",&ptJESDOWN);
    BareFunctions::SetBranchAddress(t,"metP4_GEN"	, &genP4 );
    BareFunctions::SetBranchAddress(t,"metPuppi", &metPuppi);

    if ( IsExtend() ) 
    {
        BareFunctions::SetBranchAddress(t,"metNoMu", &metNoMu);
        BareFunctions::SetBranchAddress(t,"metNoHF", &metNoHF);
        BareFunctions::SetBranchAddress(t,"pfMet_e3p0", &pfMet_e3p0);
        BareFunctions::SetBranchAddress(t,"trackMet", &trackMet);
        //calo met
        BareFunctions::SetBranchAddress(t,"caloMet_Pt", &caloMet_Pt);
        BareFunctions::SetBranchAddress(t,"caloMet_Phi", &caloMet_Phi);
        BareFunctions::SetBranchAddress(t,"caloMet_SumEt", &caloMet_SumEt);
    }
}

void BareMet::compress(){

    BareP4::compress();

	for(int i=0;i<genP4->GetEntries();++i)
		BareFunctions::Compress( * (TLorentzVector*) genP4->At(i)  );

    BareFunctions::Compress(*metPuppi);

    if ( IsExtend() ) 
    {
        BareFunctions::Compress(*metNoMu);
        BareFunctions::Compress(*metNoHF);
        BareFunctions::Compress(*pfMet_e3p0);
        BareFunctions::Compress(*trackMet);
    }

}

// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
