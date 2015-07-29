#include "NeroProducer/Bambu/interface/MetFiller.h"

#include "MitAna/DataTree/interface/MetCol.h"
#include "MitAna/DataTree/interface/GenMetCol.h"
#include "MitAna/DataTree/interface/ParticleCol.h"
#include "MitAna/DataTree/interface/PFCandidateCol.h"
#include "MitAna/DataTree/interface/EventHeader.h"
#include "MitAna/DataTree/interface/Names.h"

ClassImp(mithep::nero::MetFiller)

void
mithep::nero::MetFiller::fill()
{
  auto* metCol = getSource<mithep::MetCol>(metName_);
  auto& met(*metCol->At(0));

  newP4(out_, met);

  // TODO
  out_.ptJESUP->push_back(0.);
  out_.ptJESDOWN->push_back(0.);

  auto metNoMu(met.Mom());
  auto* muons = getSource<mithep::ParticleCol>(muonsName_);
  for (unsigned iM(0); iM != muons->GetEntries(); ++iM)
    metNoMu += muons->At(iM)->Mom();
  out_.metNoMu = metNoMu.Pt();
  out_.phiNoMu = metNoMu.Phi();

  mithep::FourVectorM pChargedHadron;
  mithep::FourVectorM pNeutralHadron;
  mithep::FourVectorM pNeutralEM;
  auto* pfCandidates = getSource<mithep::PFCandidateCol>(pfCandidatesName_);
  for (unsigned iP(0); iP != pfCandidates->GetEntries(); ++iP) {
    auto& cand(*pfCandidates->At(iP));

    switch (cand.PFType()) {
    case mithep::PFCandidate::eHadron:
      pChargedHadron += cand.Mom();
      break;
    case mithep::PFCandidate::eNeutralHadron:
    case mithep::PFCandidate::eHadronHF:
      pNeutralHadron += cand.Mom();
      break;
    case mithep::PFCandidate::eGamma:
    case mithep::PFCandidate::eEGammaHF:
      pNeutralEM += cand.Mom();
      break;
    default:
      break;
    }
  }

  out_.metChargedHadron = pChargedHadron.Pt();
  out_.phiChargedHadron = pChargedHadron.Phi();
  out_.metNeutralHadron = pNeutralHadron.Pt();
  out_.phiNeutralHadron = pNeutralHadron.Phi();
  out_.metNeutralEM = pNeutralEM.Pt();
  out_.phiNeutralEM = pNeutralEM.Phi();

  if (getSource<mithep::EventHeader>(Names::gkEvtHeaderBrn)->IsMC()) {
    auto* genMetCol = getSource<mithep::MetCol>(genMetName_);
    auto& genMet(*genMetCol->At(0));

    newP4(*out_.genP4, genMet);
  }
}