import FWCore.ParameterSet.Config as cms

from subprocess import check_output
import os

#------------------------------------------------------
nero = cms.EDAnalyzer("Nero",
    info = cms.string("Nero"),
    head = cms.string( check_output("cd "+os.environ['CMSSW_BASE']+"/src/NeroProducer/ && git rev-parse HEAD && cd - 2>&1 >/dev/null",shell=True) ) ,
    tag  = cms.string( check_output("cd " +os.environ["CMSSW_BASE"] +"/src/NeroProducer && { git describe --tags || true ; } && cd - 2>&1 >/dev/null",shell=True) ) ,

    vertices = cms.InputTag("offlineSlimmedPrimaryVertices"),
    rho = cms.InputTag("fixedGridRhoFastjetAll"),
    muons = cms.InputTag("slimmedMuons"),
    electrons = cms.InputTag("slimmedElectrons"),
    taus = cms.InputTag("slimmedTaus"),
    photons = cms.InputTag("slimmedPhotons"),
    jets = cms.InputTag("slimmedJets"),
    fatjets = cms.InputTag("slimmedJetsAK8"),
    mets = cms.InputTag("slimmedMETs"),
    # gen
    pileup = cms.InputTag("addPileupInfo"),
    generator = cms.InputTag("generator"),
    genruninfo = cms.InputTag("generator"),
    genjets = cms.InputTag("slimmedGenJets"),
    prunedgen = cms.InputTag("prunedGenParticles"),
    packedgen = cms.InputTag("packedGenParticles"),
    ### ID MAP
    eleVetoIdMap = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-PHYS14-PU20bx25-V2-standalone-veto"),
    eleMediumIdMap = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-PHYS14-PU20bx25-V2-standalone-medium"),
    eleTightIdMap = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-PHYS14-PU20bx25-V2-standalone-tight"),
    phoLooseIdMap = cms.InputTag("egmPhotonIDs:cutBasedPhotonID-PHYS14-PU20bx25-V2-standalone-loose"),
    phoMediumIdMap = cms.InputTag("egmPhotonIDs:cutBasedPhotonID-PHYS14-PU20bx25-V2-standalone-medium"),
    phoTightIdMap = cms.InputTag("egmPhotonIDs:cutBasedPhotonID-PHYS14-PU20bx25-V2-standalone-tight"),
    ### ISO MAP
    phoChargedIsolation = cms.InputTag("photonIDValueMapProducer:phoChargedIsolation"),
    phoNeutralHadronIsolation = cms.InputTag("photonIDValueMapProducer:phoNeutralHadronIsolation"),
    phoPhotonIsolation = cms.InputTag("photonIDValueMapProducer:phoPhotonIsolation"),
    #
    ## TRIGGER
    triggerNames = cms.vstring(['HLT_PFMET170_NoiseCleaned',
                                'HLT_PFMETNoMu120_NoiseCleaned_PFMHTNoMu120_IDTight']),
    prescales = cms.InputTag('patTrigger'),
    trigger = cms.InputTag("TriggerResults","","HLT"),
    objects = cms.InputTag('selectedPatTrigger'),
    ## CUSTOM CONFIGURATION
    onlyMc = cms.bool (False),  ## not completely supported yet

    minJetPt  = cms.double (30.),
    minJetEta = cms.double (2.5),
    minJetN   = cms.int32  (0),
    minJetId  = cms.string ('loose'),
    matchJet  = cms.bool (True),
    matchJetDr = cms.double(0.3),

    minElePt  = cms.double (10.),
    minEleEta = cms.double (2.5),
    maxEleIso = cms.double (-1.),

    minMuPt   = cms.double (10.),
    minMuEta  = cms.double (2.4),
    maxMuIso  = cms.double (0.2),
   
    minLepN   = cms.int32 (0),
    matchLep  = cms.bool (True),
    matchLepDr = cms.double (0.1),

    minTauPt  = cms.double (18.),
    minTauEta = cms.double (2.3),
    minTauN   = cms.int32  (0),
    minTauId  = cms.string ('decayModeFindingNewDMs'),
    maxTauIso = cms.double (-1),
    extendTau = cms.bool(False),
    matchTau  = cms.bool (True),
    matchTauDr = cms.double (0.1),

    minGenParticlePt = cms.double(5.),
    minGenJetPt = cms.double(20.),
                      
    minPhoPt  = cms.double (15.),
    minPhoEta = cms.double (2.5),
    minPhoN   = cms.int32  (0),
    maxPhoIso = cms.double (-1.),
    matchPho  = cms.bool (False),
    matchPhoDr = cms.double (0.3),
)
#------------------------------------------------------