#ifndef NeroProducer_Bambu_MonteCarloFiller_h
#define NeroProducer_Bambu_MonteCarloFiller_h

#include "NeroProducer/Bambu/interface/BaseFiller.h"
#include "NeroProducer/Core/interface/BareMonteCarlo.hpp"

#include "MitAna/DataTree/interface/Names.h"

namespace mithep {
  namespace nero {

    class MonteCarloFiller : public BaseFiller {
    public:
      MonteCarloFiller() {}
      ~MonteCarloFiller() {}

      BareCollection* getObject() override { return &out_; }
      mithep::nero::Collection collection() const override { return kMonteCarlo; }

      void fill() override;

      void SetMCParticlesName(char const* _name) { mcParticlesName_ = _name; }
      void SetGenJetsName(char const* _name) { genJetsName_ = _name; }
      void SetMinParticlePt(Double_t _min) { minParticlePt_ = _min; }
      void SetMinGenJetPt(Double_t _min) { minGenJetPt_ = _min; }

    private:
      BareMonteCarlo out_{};

      TString mcParticlesName_ = mithep::Names::gkMCPartBrn;
      TString genJetsName_ = mithep::Names::gkGenJetBrn;

      Double_t minParticlePt_ = 0.;
      Double_t minGenJetPt_ = 0.;

      ClassDef(MonteCarloFiller, 0)
    };

  }
}

#endif