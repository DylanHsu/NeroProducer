#include "NeroProducer/Core/interface/BareP4.hpp"
#include "NeroProducer/Core/interface/BareFunctions.hpp"

void BareP4::clear(){ 

	p4->Clear() ; 

	if (doMatch_) match->clear(); 
}

void BareP4::defineBranches(TTree * t, string prefix)
{
    p4 = new TClonesArray("TLorentzVector", 20);
    t->Branch( (prefix + "P4").c_str(),"TClonesArray", &p4, 128000, 0);

    if (doMatch_){
    	match = new vector<int>;
    	t->Branch( (prefix+"Match").c_str(),"vector<int>",&match);
    }
}

void BareP4::setBranchAddresses(TTree*t,string prefix)
{
    p4 = new TClonesArray("TLorentzVector", 20);
    t->SetBranchAddress( (prefix+"P4").c_str(), &p4	);

    if ( doMatch_){
    	match = new vector<int>;
    	t->SetBranchAddress((prefix+"Match").c_str()	,&match);
    }
}

void BareP4::compress(){
	for(int i=0;i<p4->GetEntries();++i)
		BareFunctions::Compress( * (TLorentzVector*) p4->At(i)  );
}
