#ifndef BARE_MET_H
#define BARE_MET_H

#include "NeroProducer/Core/interface/BareCollection.hpp"
#include "NeroProducer/Core/interface/BareP4.hpp"


class BareMet : virtual public BareP4
{
    public:
        BareMet();
        ~BareMet();
        void init() override;
        void clear() override;
        void defineBranches(TTree*) override;
        void defineBranches(TTree* t, std::string) override { defineBranches(t); }
        void setBranchAddresses(TTree*) override;
        void setBranchAddresses(TTree* t, std::string) override { setBranchAddresses(t); }
        inline string name() override { return "BareMet"; }
        void compress() override;

        // -- variables
        //TClonesArray *p4;
        vector<float> *ptJESUP{0};
        vector<float> *ptJESDOWN{0};

        // Should not stay here, but in MC -> we will esculed it if run on onlyMc
        TClonesArray *genP4{0};

        TLorentzVector *metNoMu{0};
        TLorentzVector *pfMet_e3p0{0};
        TLorentzVector *trackMet{0};
  
        float caloMet_Pt;
        float caloMet_Phi;
        float caloMet_SumEt;
};
#endif
// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
