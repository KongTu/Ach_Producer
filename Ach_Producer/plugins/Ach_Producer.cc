// -*- C++ -*-
//
// Package:    Ach_Producer/Ach_Producer
// Class:      Ach_Producer
// 
/**\class Ach_Producer Ach_Producer.cc Ach_Producer/Ach_Producer/plugins/Ach_Producer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Zhoudunming Tu
//         Created:  Mon, 08 Aug 2016 12:41:47 GMT
//
//


#include "Ach_Producer/Ach_Producer/interface/Ach_ProducerBase.h"


Ach_Producer::Ach_Producer(const edm::ParameterSet& iConfig):

genSrc_(consumes<reco::GenParticleCollection>(iConfig.getParameter<edm::InputTag>("genSrc")))

{

  trackName_  =  iConfig.getParameter<edm::InputTag>("trackName");
  vertexName_ =  iConfig.getParameter<edm::InputTag>("vertexName");
  towerName_ =  iConfig.getParameter<edm::InputTag>("towerName");

  trackSrc_ = consumes<reco::TrackCollection>(trackName_);
  vertexSrc_ = consumes<reco::VertexCollection>(vertexName_);
  towerSrc_ = consumes<CaloTowerCollection>(towerName_);


  Nmin_ = iConfig.getUntrackedParameter<int>("Nmin");
  Nmax_ = iConfig.getUntrackedParameter<int>("Nmax");

  useCentrality_ = iConfig.getUntrackedParameter<bool>("useCentrality");
  reverseBeam_ = iConfig.getUntrackedParameter<bool>("reverseBeam");
  doEffCorrection_ = iConfig.getUntrackedParameter<bool>("doEffCorrection");
  useEtaGap_ = iConfig.getUntrackedParameter<bool>("useEtaGap");
  doGenParticle_ = iConfig.getUntrackedParameter<bool>("doGenParticle");

  eff_ = iConfig.getUntrackedParameter<int>("eff");

  etaTracker_ = iConfig.getUntrackedParameter<double>("etaTracker");

  gapValue_ = iConfig.getUntrackedParameter<double>("gapValue");
  
  etaLowHF_ = iConfig.getUntrackedParameter<double>("etaLowHF");
  etaHighHF_ = iConfig.getUntrackedParameter<double>("etaHighHF");
  
  vzLow_ = iConfig.getUntrackedParameter<double>("vzLow");
  vzHigh_ = iConfig.getUntrackedParameter<double>("vzHigh");
  
  ptLow_ = iConfig.getUntrackedParameter<double>("ptLow");
  ptHigh_ = iConfig.getUntrackedParameter<double>("ptHigh");

  offlineptErr_ = iConfig.getUntrackedParameter<double>("offlineptErr", 0.0);
  offlineDCA_ = iConfig.getUntrackedParameter<double>("offlineDCA", 0.0);
  offlineChi2_ = iConfig.getUntrackedParameter<double>("offlineChi2", 0.0);
  offlinenhits_ = iConfig.getUntrackedParameter<double>("offlinenhits", 0.0);

  smearFactor_ = iConfig.getUntrackedParameter<double>("smearFactor", 0.0);

  etaBins_ = iConfig.getUntrackedParameter<std::vector<double>>("etaBins");
  dEtaBins_ = iConfig.getUntrackedParameter<std::vector<double>>("dEtaBins");
  ptBins_ = iConfig.getUntrackedParameter<std::vector<double>>("ptBins");
  centBins_ = iConfig.getUntrackedParameter<std::vector<double>>("centBins");

}


Ach_Producer::~Ach_Producer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
Ach_Producer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  using namespace std;

  edm::Handle<reco::VertexCollection> vertices;
  iEvent.getByToken(vertexSrc_,vertices);
  double bestvz=-999.9, bestvx=-999.9, bestvy=-999.9;
  double bestvzError=-999.9, bestvxError=-999.9, bestvyError=-999.9;
  const reco::Vertex & vtx = (*vertices)[0];
  bestvz = vtx.z(); 
  bestvx = vtx.x(); 
  bestvy = vtx.y();
  bestvzError = vtx.zError(); 
  bestvxError = vtx.xError(); 
  bestvyError = vtx.yError();

  //first selection; vertices
  if( fabs(bestvz) < vzLow_ || fabs(bestvz) > vzHigh_ ) return;

  vtxZ->Fill( bestvz );

  Handle<CaloTowerCollection> towers;
  iEvent.getByToken(towerSrc_, towers);

  Handle<reco::TrackCollection> tracks;
  iEvent.getByToken(trackSrc_, tracks);

  int nTracks = 0;
  for(unsigned it = 0; it < tracks->size(); it++){

     const reco::Track & trk = (*tracks)[it];
  
     math::XYZPoint bestvtx(bestvx,bestvy,bestvz);

        double dzvtx = trk.dz(bestvtx);
        double dxyvtx = trk.dxy(bestvtx);
        double dzerror = sqrt(trk.dzError()*trk.dzError()+bestvzError*bestvzError);
        double dxyerror = sqrt(trk.d0Error()*trk.d0Error()+bestvxError*bestvyError); 

        if(!trk.quality(reco::TrackBase::highPurity)) continue;
        if(fabs(trk.ptError())/trk.pt() > 0.1 ) continue;
        if(fabs(dzvtx/dzerror) > 3.0) continue;
        if(fabs(dxyvtx/dxyerror) > 3.0) continue;
        if(trk.pt() < 0.4 || fabs(trk.eta()) > 2.4) continue;
        nTracks++;//count multiplicity

  }

  double etHFtowerSumPlus = 0.0;
  double etHFtowerSumMinus = 0.0;
  double etHFtowerSum = 0.0;

  for( unsigned i = 0; i<towers->size(); ++ i){
       const CaloTower & tower = (*towers)[ i ];
       double eta = tower.eta();
       bool isHF = tower.ietaAbs() > 29;
          if(isHF && eta > 0){
            etHFtowerSumPlus += tower.pt();
          }
          if(isHF && eta < 0){
            etHFtowerSumMinus += tower.pt();
          }
  }
  
  etHFtowerSum=etHFtowerSumPlus + etHFtowerSumMinus;
  
  NtrkHF->Fill(nTracks, etHFtowerSum);
  
  etHFtowerSumPlus = 0.0;
  etHFtowerSumMinus = 0.0;
  etHFtowerSum = 0.0;

  if( useCentrality_ ){

    if( doGenParticle_ ){

      for( unsigned i = 0; i<towers->size(); ++ i){
       const CaloTower & tower = (*towers)[ i ];
       double eta = tower.eta();
       bool isHF = tower.ietaAbs() > 29;
          if(isHF && eta > 0){
            etHFtowerSumPlus += tower.pt();
          }
          if(isHF && eta < 0){
            etHFtowerSumMinus += tower.pt();
          }
      }
      etHFtowerSum=etHFtowerSumPlus + etHFtowerSumMinus;

      if( etHFtowerSum < Nmin_ || etHFtowerSum > Nmax_ ) return;

      HFsumEt->Fill( etHFtowerSum );
    }
    else{

      for( unsigned i = 0; i<towers->size(); ++ i){
       const CaloTower & tower = (*towers)[ i ];
       double eta = tower.eta();
       bool isHF = tower.ietaAbs() > 29;
          if(isHF && eta > 0){
            etHFtowerSumPlus += tower.pt();
          }
          if(isHF && eta < 0){
            etHFtowerSumMinus += tower.pt();
          }
      }
      etHFtowerSum=etHFtowerSumPlus + etHFtowerSumMinus;

      int bin = -1;
      for(int j=0; j<200; j++){
        if( etHFtowerSum >= centBins_[j] ){
           bin = j; break;
        }
      }

      int hiBin = bin;
      cbinHist->Fill( hiBin );
      if( hiBin < Nmin_ || hiBin >= Nmax_ ) return;
    
    }
  }


  if( !useCentrality_ ) if( nTracks < Nmin_ || nTracks >= Nmax_ ) return;

  Ntrk->Fill( nTracks );

  double N_pos_count_uncorr = 0.0;
  double N_neg_count_uncorr = 0.0;

  double N_pos_count_corr = 0.0;
  double N_neg_count_corr = 0.0;

  double N_pos_after_count_uncorr = 0.0;
  double N_neg_after_count_uncorr = 0.0;

  double N_pos_after_count_corr = 0.0;
  double N_neg_after_count_corr = 0.0;


  for(unsigned it = 0; it < tracks->size(); it++){

    const reco::Track & trk = (*tracks)[it];

    math::XYZPoint bestvtx(bestvx,bestvy,bestvz);

    double dzvtx = trk.dz(bestvtx);
    double dxyvtx = trk.dxy(bestvtx);
    double dzerror = sqrt(trk.dzError()*trk.dzError()+bestvzError*bestvzError);
    double dxyerror = sqrt(trk.d0Error()*trk.d0Error()+bestvxError*bestvyError); 
    double nhits = trk.numberOfValidHits();
    double chi2n = trk.normalizedChi2();
    double nlayers = trk.hitPattern().trackerLayersWithMeasurement();
    chi2n = chi2n/nlayers;
    double phi = trk.phi();
    double trkEta = trk.eta();

    double weight = 1.0;
    if( doEffCorrection_ ) { weight = 1.0/effTable[eff_]->GetBinContent( effTable[eff_]->FindBin(trk.eta(), trk.pt()) );}

    if(!trk.quality(reco::TrackBase::highPurity)) continue;
    if(fabs(trk.ptError())/trk.pt() > offlineptErr_ ) continue;
    if(fabs(dzvtx/dzerror) > offlineDCA_) continue;
    if(fabs(dxyvtx/dxyerror) > offlineDCA_) continue;
    if(chi2n > offlineChi2_ ) continue;
    if(nhits < offlinenhits_ ) continue;
    if(trk.pt() < ptLow_ || trk.pt() > ptHigh_ ) continue;
    if(fabs(trkEta) > etaTracker_ ) continue;

    trkPhi->Fill(phi, weight);
    trkPt->Fill(trk.pt(), weight);
    trk_eta->Fill(trkEta, weight);

    double random1 = fRand(0.0, 1.0);
    if( random1 > 0.5 ){

      if( trk.charge() == +1 ){ N_pos_count_uncorr++; N_pos_count_corr += weight;}
      if( trk.charge() == -1 ){ N_neg_count_uncorr++; N_neg_count_corr += weight;}
    }

    double efficiency = effTable[eff_]->GetBinContent(effTable[eff_]->FindBin(trkEta, trk.pt()));
    double random = fRand(0.0, 1.0);
    if( random > efficiency ) continue;

    if( trk.charge() == +1 ){ N_pos_after_count_uncorr++; N_pos_after_count_corr += weight;}
    if( trk.charge() == -1 ){ N_neg_after_count_uncorr++; N_neg_after_count_corr += weight;}

  }

  double GEN_N_pos_count = 0.0;
  double GEN_N_neg_count = 0.0;

  if( doGenParticle_ ){
    edm::Handle<reco::GenParticleCollection> genParticleCollection;
    iEvent.getByToken(genSrc_, genParticleCollection);
    
    for(unsigned it=0; it<genParticleCollection->size(); ++it) {

      const reco::GenParticle & genCand = (*genParticleCollection)[it];
      int status = genCand.status();
      double geneta = genCand.eta();
      int gencharge = genCand.charge();
      double genpt = genCand.pt();
      //int id = genCand.pdgId();

      // if( fabs(id) == 310 || fabs(id) == 3122 
      //                     || fabs(id) == 3322
      //                     || fabs(id) == 3222
      //                     || fabs(id) == 3212
      //                     || fabs(id) == 3112 
      //                     || fabs(id) == 3224
      //                     || fabs(id) == 3214
      //                     || fabs(id) == 3114
      //                     || fabs(id) == 3312 
      //                     || fabs(id) == 3324 
      //                     || fabs(id) == 3314 
      //                     || fabs(id) == 3334) continue;

      if( status != 1 || gencharge == 0 ) continue;
      if( fabs(geneta) > etaTracker_ ) continue;
      if( genpt < 0.3 || genpt > 3.0 ) continue;

      // double efficiency = effTable[eff_]->GetBinContent(effTable[eff_]->FindBin(geneta, genpt));
      // double random = fRand(0.0, 1.0);
      // if( random > efficiency ) continue;

      genPt->Fill( genpt );
      genEta->Fill( geneta );

      double random1 = fRand(0.0, 1.0);
      if( random1 > 0.5 ){
        if( gencharge == +1 ){ GEN_N_pos_count++; }
        if( gencharge == -1 ){ GEN_N_neg_count++; }
      }
    }
  }

  double RECO_Ach_uncorr = (N_pos_count_uncorr - N_neg_count_uncorr) / (N_pos_count_uncorr + N_neg_count_uncorr);
  double RECO_Ach_corr = (N_pos_count_corr - N_neg_count_corr) / (N_pos_count_corr + N_neg_count_corr);  
  double GEN_Ach_uncorr = 0.0;
  double GEN_Ach_corr = 0.0;
  double RECO_2_Ach_uncorr = (N_pos_after_count_uncorr - N_neg_after_count_uncorr) / (N_pos_after_count_uncorr + N_neg_after_count_uncorr); 
  double RECO_2_Ach_corr = (N_pos_after_count_corr - N_neg_after_count_corr) / (N_pos_after_count_corr + N_neg_after_count_corr); 

  if( doGenParticle_){
    
    GEN_Ach_corr = (GEN_N_pos_count - GEN_N_neg_count) / (GEN_N_pos_count + GEN_N_neg_count);
    GEN_Ach_uncorr = GEN_Ach_corr;

    Npos_uncorr->Fill(N_pos_count_uncorr, GEN_N_pos_count);
    Nneg_uncorr->Fill(N_neg_count_uncorr, GEN_N_neg_count);

    Npos_corr->Fill(N_pos_count_corr, GEN_N_pos_count);
    Nneg_corr->Fill(N_neg_count_corr, GEN_N_neg_count);

    Ach_uncorr->Fill(RECO_Ach_uncorr, GEN_Ach_uncorr);
    Ach_corr->Fill(RECO_Ach_corr, GEN_Ach_corr);
  }
  else{

    Npos_uncorr->Fill(N_pos_after_count_uncorr, N_pos_count_uncorr);
    Nneg_uncorr->Fill(N_neg_after_count_uncorr, N_neg_count_uncorr);

    Npos_corr->Fill(N_pos_after_count_corr, N_pos_count_corr);
    Nneg_corr->Fill(N_neg_after_count_corr, N_neg_count_corr);

    Ach_uncorr->Fill(RECO_2_Ach_uncorr, RECO_Ach_uncorr);
    Ach_corr->Fill(RECO_2_Ach_corr, RECO_Ach_corr);
  }

  //double weight = NtrkReweight->GetBinContent( NtrkReweight->FindBin( nTracks ) );//weight = Hydjet/EPOS


  

}
// ------------ method called once each job just before starting event loop  ------------
void 
Ach_Producer::beginJob()
{
  edm::Service<TFileService> fs;
    
  TH1D::SetDefaultSumw2();

  const int NetaBins = etaBins_.size() - 1;
  double etaBinsArray[100];
  for(unsigned i = 0; i < etaBins_.size(); i++){
    etaBinsArray[i] = etaBins_[i];
  }
  const int Nptbins = ptBins_.size() - 1;
  double ptBinsArray[100];
  for(unsigned i = 0; i < ptBins_.size(); i++){
    ptBinsArray[i] = ptBins_[i];
  }

  edm::FileInPath fip1("Ach_Producer/Ach_Producer/data/Hydjet_PbPb_eff_v1.root");
  TFile f1(fip1.fullPath().c_str(),"READ");
  for(int i = 0; i < 5; i++){
     effTable[i] = (TH2D*)f1.Get(Form("eff_%d",i+1));
  }

  edm::FileInPath fip2("Ach_Producer/Ach_Producer/data/Ach_weight.root");
  TFile f2(fip2.fullPath().c_str(),"READ");
  for(int i = 0; i < 3; i++){
     Ach_corr_weight[i] = (TH1D*)f2.Get(Form("ApplyEPOS_%d",i));
  }

  edm::FileInPath fip3("Ach_Producer/Ach_Producer/data/Ach_uncorr_weight.root");
  TFile f3(fip3.fullPath().c_str(),"READ");
  for(int i = 0; i < 3; i++){
     Ach_uncorr_weight[i] = (TH1D*)f3.Get(Form("ApplyEPOS_%d",i));
  }

  edm::FileInPath fip4("Ach_Producer/Ach_Producer/data/Ach_gen_weight.root");
  TFile f4(fip4.fullPath().c_str(),"READ");
  for(int i = 0; i < 3; i++){
     Ach_gen_weight[i] = (TH1D*)f4.Get(Form("ApplyEPOS_%d",i));
  }

  edm::FileInPath fip5("Ach_Producer/Ach_Producer/data/mult300_350_reweighed.root");
  TFile f5(fip5.fullPath().c_str(),"READ");
  NtrkReweight = (TH1D*)f5.Get("Ntrk");

  Ntrk = fs->make<TH1D>("Ntrk",";Ntrk",5000,0,5000);
  vtxZ = fs->make<TH1D>("vtxZ",";vz", 400,-20,20);
  cbinHist = fs->make<TH1D>("cbinHist",";cbin",200,0,200);
  trkPhi = fs->make<TH1D>("trkPhi", ";#phi", 700, -3.5, 3.5);
  trkPt = fs->make<TH1D>("trkPt", ";p_{T}(GeV)", Nptbins,ptBinsArray);
  trk_eta = fs->make<TH1D>("trk_eta", ";#eta", NetaBins, etaBinsArray);
  genPt = fs->make<TH1D>("genPt", ";p_{T}(GeV)", Nptbins,ptBinsArray);
  genEta = fs->make<TH1D>("genEta", ";#eta", NetaBins, etaBinsArray);

  HFsumEt = fs->make<TH1D>("HFsumEt", ";HFsumEt", 10000, 0, 10000);

  Npos_uncorr = fs->make<TH2D>("Npos_uncorr",";Npos_uncorr", 2000, 0, 2000, 2000, 0, 2000);
  Nneg_uncorr = fs->make<TH2D>("Nneg_uncorr",";Nneg_uncorr", 2000, 0, 2000, 2000, 0, 2000);
  Npos_corr = fs->make<TH2D>("Npos_corr",";Npos_corr", 2000, 0, 2000, 2000, 0, 2000);
  Nneg_corr = fs->make<TH2D>("Nneg_corr",";Nneg_corr", 2000, 0, 2000, 2000, 0, 2000);

  Ach_uncorr = fs->make<TH2D>("Ach_uncorr",";Ach_uncorr", 1000, -0.4, 0.4, 1000, -0.4, 0.4 );
  Ach_corr = fs->make<TH2D>("Ach_corr",";Ach_corr", 1000, -0.4, 0.4, 1000, -0.4, 0.4 );

  NtrkHF = fs->make<TH2D>("NtrkHF",";NtrkHF", 2000, 0, 2000, 10000, 0, 10000 );

}
// ------------ method called once each job just after ending the event loop  ------------
void 
Ach_Producer::endJob() 
{
}
double Ach_Producer::fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}
void 
Ach_Producer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
Ach_Producer::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
Ach_Producer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
Ach_Producer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
Ach_Producer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
}

//define this as a plug-in
DEFINE_FWK_MODULE(Ach_Producer);
