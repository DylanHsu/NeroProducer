#include "NeroProducer/Nero/interface/NeroMet.hpp"
#include "NeroProducer/Nero/interface/Nero.hpp"

NeroMet::NeroMet() : BareMet() {
}

NeroMet::~NeroMet(){
}


int NeroMet::analyze(const edm::Event& iEvent){

    if ( mOnlyMc  ) return 0; // in principle I would like to have the gen met: TODO

    // maybe handle should be taken before
    iEvent.getByToken(token, handle);
    const pat::MET &met = handle->front();

    //p4 -> AddLast(new TLorentzVector(met.px(),met.py(),met.pz(),met.energy()));
    new ( (*p4)[p4->GetEntriesFast()]) TLorentzVector( met.px(),met.py(),met.pz(),met.energy()  );

    ptJESUP -> push_back( met.shiftedPt(pat::MET::JetEnUp) );
    ptJESDOWN -> push_back( met.shiftedPt(pat::MET::JetEnDown) );

    //MetNoMu
    float metnomu_x = met.px();
    float metnomu_y = met.py();
   
    
    iEvent.getByToken(pfToken_, pfs);
    for (unsigned int i = 0, n = pfs->size(); i < n; ++i) {
        const pat::PackedCandidate &pf = (*pfs)[i];
        if (std::abs(pf.pdgId()) == 13 ){
            metnomu_x += pf.px();
            metnomu_y += pf.py();
        }
    }
    
    metNoMu = sqrt(metnomu_x*metnomu_x + metnomu_y*metnomu_y);

    if ( not iEvent.isRealData () ){
    new ( (*genP4)[genP4->GetEntriesFast()]) TLorentzVector( met.genMET()->px(),met.genMET()->py(),met.genMET()->pz(),met.genMET()->energy()  );
    }


    return 0;
}

// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
