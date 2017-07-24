////////////////////////////////////////////////////////////////////////
// Class:       CaloNearlineHistograms
// Plugin Type: analyzer (art v2_03_00)
// File:        CaloNearlineHistograms_module.cc
//
// Calo oriented histograms to be generated after every run
//
// Generated at Mon Mar 27 16:42:59 2017 by Aaron Fienberg using cetskelgen
// from cetlib version v1_19_01.
////////////////////////////////////////////////////////////////////////

#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Principal/Handle.h"
#include "art/Framework/Principal/Run.h"
#include "art/Framework/Principal/SubRun.h"
#include "canvas/Utilities/InputTag.h"
#include "fhiclcpp/ParameterSet.h"
#include "messagefacility/MessageLogger/MessageLogger.h"

#include "art/Framework/Services/Optional/TFileService.h"
#include "art/Framework/Services/Registry/ServiceHandle.h"

// Database service
#include "gm2util/database/Database_service.hh"

#include "gm2dataproducts/calo/ClusterArtRecord.hh"
#include "gm2dataproducts/calo/GpuCTagArtRecord.hh"

#include "gm2calo/util/CaloForEach.hh"

#include "TH1.h"
#include "TH2.h"

namespace gm2calo {
class CaloNearlineHistograms;
}

class gm2calo::CaloNearlineHistograms : public art::EDAnalyzer {
 public:
  explicit CaloNearlineHistograms(fhicl::ParameterSet const &p);
  // The compiler-generated destructor is fine for non-base
  // classes without bare pointers or other resource use.

  // Plugins should not be copied or assigned.
  CaloNearlineHistograms(CaloNearlineHistograms const &) = delete;
  CaloNearlineHistograms(CaloNearlineHistograms &&) = delete;
  CaloNearlineHistograms &operator=(CaloNearlineHistograms const &) = delete;
  CaloNearlineHistograms &operator=(CaloNearlineHistograms &&) = delete;

  void endJob() override;
  // Required functions.
  void analyze(art::Event const &e) override;

 private:
  int runNumber_;
  int subrunNumber_;

  int nCalos_;
  int nXtals_;
  double wiggleThreshold_;
  double positionThreshold_;
  double ctagTimeCut_;
  double ctagECut_;
  double eHistMax_;
  double hitThreshold_;

  bool useDatabase_;

  std::string unpackerModuleLabel_;
  std::string unpackerInstanceLabel_;
  std::string xtalhitModuleLabel_;
  std::string xtalhitInstanceLabel_;
  std::string clusterModuleLabel_;
  std::string clusterInstanceLabel_;

  // histograms
  TH1D *allEnergies_;
  TH1D *allWiggle_;
  TH1D *allTimes_;
  TH1D *gpuCTag_;
  TH1D *nearlineCTag_;

  std::vector<TH1D *> caloEnergies_;
  std::vector<TH1D *> caloWiggles_;
  std::vector<TH1D *> caloTimes_;
  std::vector<TH2D *> hitPositions_;
  std::vector<TH2D *> nXtalHits_;
  std::vector<std::vector<TH1D *>> xtalEnergies_;
};

gm2calo::CaloNearlineHistograms::CaloNearlineHistograms(
    fhicl::ParameterSet const &p)
    : EDAnalyzer(p),
      runNumber_(-1),
      subrunNumber_(-1),
      nCalos_(p.get<int>("nCalos", 24)),
      nXtals_(p.get<int>("nXtals", 54)),
      wiggleThreshold_(p.get<double>("wiggleThreshold", 1400)),
      positionThreshold_(p.get<double>("positionThreshold", 1400)),
      ctagTimeCut_(p.get<double>("ctagTimeCut", 10000)),
      ctagECut_(p.get<double>("ctagEnergyCut", 1300)),
      eHistMax_(p.get<double>("eHistMax", 4000)),
      hitThreshold_(p.get<double>("hitThreshold", 150)),
      useDatabase_(p.get<bool>("useDatabase", false)),
      unpackerModuleLabel_(
          p.get<std::string>("unpackerModuleLabel", "islandUnpacker")),
      unpackerInstanceLabel_(
          p.get<std::string>("unpackerInstanceLabel", "unpacker")),
      xtalhitModuleLabel_(
          p.get<std::string>("xtalhitModuleLabel", "gainCorrector")),
      xtalhitInstanceLabel_(
          p.get<std::string>("xtalhitInstanceLabel", "corrector")),
      clusterModuleLabel_(
          p.get<std::string>("clusterModuleLabel", "hitCluster")),
      clusterInstanceLabel_(
          p.get<std::string>("clusterInstanceLabel", "cluster")) {
  art::TFileDirectory allCaloDir = *art::ServiceHandle<art::TFileService>();

  allEnergies_ = allCaloDir.make<TH1D>(
      "allCaloEnergies", "all energies; energy [p.e.]; N;", 250, 0, eHistMax_);
  allWiggle_ = allCaloDir.make<TH1D>(
      "allCaloWiggle", "T Method, all calos; time [clock ticks]; N;", 4700, 0,
      560000);
  allTimes_ = allCaloDir.make<TH1D>(
      "allCaloTimes", "hit times, all calos; time [clock ticks]; N;", 4700, 0,
      560000);

  // will be filled at end of run by integrating wiggle
  gpuCTag_ = allCaloDir.make<TH1D>("gpuCTag", "gpuCTag; calo num; N", nCalos_,
                                   1, nCalos_ + 1);

  nearlineCTag_ = allCaloDir.make<TH1D>(
      "nearlineCTag", "nearlineCTag; calo num; N", nCalos_, 1, nCalos_ + 1);

  caloEnergies_.resize(nCalos_);
  caloWiggles_.resize(nCalos_);
  caloTimes_.resize(nCalos_);
  hitPositions_.resize(nCalos_);
  xtalEnergies_.resize(nCalos_);
  nXtalHits_.resize(nCalos_);
  for (int iCalo = 0; iCalo < nCalos_; ++iCalo) {
    auto thisCaloDir = allCaloDir.mkdir("calo" + std::to_string(iCalo + 1));
    caloEnergies_[iCalo] = thisCaloDir.make<TH1D>(
        "energy", Form("calo %i energies; energy [p.e.]; N", iCalo + 1), 250, 0,
        eHistMax_);

    caloWiggles_[iCalo] = thisCaloDir.make<TH1D>(
        "wiggle", Form("calo %i T Method; time; N", iCalo + 1), 4700, 0,
        560000);
    caloTimes_[iCalo] = thisCaloDir.make<TH1D>(
        "times", Form("calo %i hit times; time; N", iCalo + 1), 4700, 0,
        560000);

    hitPositions_[iCalo] = thisCaloDir.make<TH2D>(
        "hitPositions",
        Form("calo %i hit positions;column num; row num;", iCalo + 1), 900, 0,
        9, 600, 0, 6);

    nXtalHits_[iCalo] = thisCaloDir.make<TH2D>(
        "nXtalHits",
        Form("calo %i n xtal hits;column num; row num;", iCalo + 1), 9, 0, 9, 6,
        0, 6);

    xtalEnergies_[iCalo].resize(nXtals_);
    for (int iXtal = 0; iXtal < nXtals_; ++iXtal) {
      xtalEnergies_[iCalo][iXtal] = thisCaloDir.make<TH1D>(
          Form("xtal%iEnergy", iXtal),
          Form("calo %i xtal %i energy", iCalo + 1, iXtal), 250, 0, 4000);
    }
  }
}

void gm2calo::CaloNearlineHistograms::analyze(art::Event const &e) {
  runNumber_ = e.run();
  subrunNumber_ = e.subRun();

  // cluster based plots
  const auto &clusterCol = *e.getValidHandle<CaloClusterArtRecordCollection>(
      {clusterModuleLabel_, clusterInstanceLabel_});

  calo_for_each(clusterCol, [&](const auto &cluster) {
    int caloIndex = cluster.caloNum - 1;
    if (caloIndex > nCalos_) {
      throw cet::exception("CaloNearlineHistograms")
          << "Found cluster with calo num " << cluster.caloNum
          << ", but n calos set to " << nCalos_ << "!\n";
    } else if (caloIndex < 0) {
      throw cet::exception("CaloNearlineHistograms")
          << "Found cluster with calo num " << cluster.caloNum << "!\n";
    }

    allTimes_->Fill(cluster.time);
    caloTimes_[caloIndex]->Fill(cluster.time);

    allEnergies_->Fill(cluster.energy);
    caloEnergies_[caloIndex]->Fill(cluster.energy);
    if (cluster.energy > wiggleThreshold_) {
      allWiggle_->Fill(cluster.time);
      caloWiggles_[caloIndex]->Fill(cluster.time);
    }
    if (cluster.energy > positionThreshold_) {
      hitPositions_[caloIndex]->Fill(cluster.x, cluster.y);
    }
    if (cluster.time > ctagTimeCut_ && cluster.energy > ctagECut_) {
      nearlineCTag_->Fill(caloIndex + 1.5);
    }
  });

  // xtal hit based plots
  const auto &xtalHitCol = *e.getValidHandle<CaloCrystalHitArtRecordCollection>(
      {xtalhitModuleLabel_, xtalhitInstanceLabel_});
  calo_for_each(xtalHitCol, [&](const auto &xtalhit) {
    int caloIndex = xtalhit.caloNum - 1;
    if (caloIndex > nCalos_) {
      throw cet::exception("CaloNearlineHistograms")
          << "Found xtal hit with calo num " << xtalhit.caloNum
          << ", but n calos set to " << nCalos_ << "!\n";
    }

    if (xtalhit.energy > hitThreshold_) {
      nXtalHits_[caloIndex]->Fill(8.5 - xtalhit.xtalNum % 9,
                                  0.5 + xtalhit.xtalNum / 9);
    }

    if (xtalhit.xtalNum > nXtals_) {
      throw cet::exception("CaloNearlineHistograms")
          << "Found xtal hit with xtal num " << xtalhit.xtalNum
          << ", but n xtals set to " << nXtals_ << "!\n";
    }
    xtalEnergies_[caloIndex][xtalhit.xtalNum]->Fill(xtalhit.energy);
  });

  // grab the gpu ctag and put it into a histogram
  const auto &gpuCTagCol = *e.getValidHandle<GpuCTagArtRecordCollection>(
      {unpackerModuleLabel_, unpackerInstanceLabel_});

  for (const auto &tag : gpuCTagCol) {
    gpuCTag_->SetBinContent(tag.caloNum, tag.ctag);
  }
}

void gm2calo::CaloNearlineHistograms::endJob() {
  if (useDatabase_) {
    art::ServiceHandle<gm2util::Database> databaseHandle;

    databaseHandle->checkDate();

    int nctag = nearlineCTag_->GetEntries();
    int gctag = gpuCTag_->GetEntries();

    std::string query = "UPDATE nearline_processing";
    query += " SET nearline_ctag = " + std::to_string(nctag);
    query += ", gpu_ctag = " + std::to_string(gctag);
    query += " WHERE run_number = " + std::to_string(runNumber_);
    query += " AND subrun_number = " + std::to_string(subrunNumber_) + ";";

    //  Insert into database table
    databaseHandle->customQuery(query);
  }
}

using gm2calo::CaloNearlineHistograms;
DEFINE_ART_MODULE(CaloNearlineHistograms)
