#include "NeroProducer/Core/interface/BareMonteCarlo.hpp"
#include "NeroProducer/Core/interface/BareFunctions.hpp"

BareMonteCarlo::BareMonteCarlo() : BareP4(){
    p4 = NULL;
    pdgId = NULL;
    jetP4 = NULL;
}

BareMonteCarlo::~BareMonteCarlo(){
}

void BareMonteCarlo::clear(){
    // This function clear all the internal storage and init it to an arbitrary value
    BareP4::clear();
    pdgId -> clear();
    jetP4 -> Clear();
    puTrueInt = -999;
    mcWeight = 1.0;
    qScale = -999;
    alphaQED = -999;
    alphaQCD = -999;
    x1 = -999;
    x2 = -999;
    pdf1Id = -999;
    pdf2Id = -999;
    scalePdf = -999;
}

void BareMonteCarlo::defineBranches(TTree *t){
    //
    BareP4::defineBranches(t, "gen" );
    //
    jetP4 = new TClonesArray("TLorentzVector", 20);
    t->Branch("genjetP4","TClonesArray", &jetP4, 128000, 0);
    //
    pdgId = new vector<int>;
    t->Branch("genPdgId","vector<int>", &pdgId);
    //
    t->Branch("puTrueInt",&puTrueInt,"puTrueInt/I");
    t->Branch("mcWeight",&mcWeight,"mcWeight/F");
    t->Branch("pdfQscale",&qScale,"pdfQscale/F");
    t->Branch("pdfAlphaQED",&alphaQED,"pdfAlphaQED/F");
    t->Branch("pdfAlphaQCD",&alphaQCD,"pdfAlphaQCD/F");
    t->Branch("pdfX1",&x1,"pdfX1/F");
    t->Branch("pdfX2",&x2,"pdfX2/F");
    t->Branch("pdfId1",&pdf1Id,"pdfId1/I");
    t->Branch("pdfId2",&pdf2Id,"pdfId2/I");
    t->Branch("pdfScalePdf",&scalePdf,"pdfScalePdf/F");
}

void BareMonteCarlo::setBranchAddresses(TTree *t){
    BareP4::setBranchAddresses(t,"gen");
    //
    jetP4 = new TClonesArray("TLorentzVector", 20);
    t->SetBranchAddress("genjetP4"	, &jetP4 );
    pdgId = new vector<int>;
    t->SetBranchAddress("genPdgId"	, &pdgId);
    //
    t->SetBranchAddress("puTrueInt"	,&puTrueInt	);
    t->SetBranchAddress("mcWeight"	,&mcWeight	);
    t->SetBranchAddress("pdfQscale"	,&qScale	);
    t->SetBranchAddress("pdfAlphaQED"	,&alphaQED	);
    t->SetBranchAddress("pdfAlphaQCD"	,&alphaQCD	);
    t->SetBranchAddress("pdfX1"	,&x1		);
    t->SetBranchAddress("pdfX2"	,&x2		);
    t->SetBranchAddress("pdfId1"	,&pdf1Id	);
    t->SetBranchAddress("pdfId2"	,&pdf2Id	);
    t->SetBranchAddress("pdfScalePdf"	,&scalePdf	);
}

void BareMonteCarlo::compress(){
    BareP4::compress();
	for(int i=0;i<jetP4->GetEntries();++i)
		BareFunctions::Compress( * (TLorentzVector*) jetP4->At(i)  );
}

// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
