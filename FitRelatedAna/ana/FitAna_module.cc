////////////////////////////////////////////////////////////////////////
// Class:       FitAna
// Plugin Type: analyzer (art v2_03_00)
// File:        FitAna_module.cc
//
// Generated at Sun Jul 23 03:51:22 2017 by Bingzhi Li using cetskelgen
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

#include "gm2dataproducts/calo/ClusterArtRecord.hh"
#include "gm2dataproducts/calo/GpuCTagArtRecord.hh"

#include "gm2calo/util/CaloForEach.hh"

#include "TH1.h"
#include "TH2.h"

namespace gm2calo {
  class FitAna;
}


class gm2calo::FitAna : public art::EDAnalyzer {
public:
  explicit FitAna(fhicl::ParameterSet const & p);
  // The compiler-generated destructor is fine for non-base
  // classes without bare pointers or other resource use.

  // Plugins should not be copied or assigned.
  FitAna(FitAna const &) = delete;
  FitAna(FitAna &&) = delete;
  FitAna & operator = (FitAna const &) = delete;
  FitAna & operator = (FitAna &&) = delete;

  // Required functions.
  void analyze(art::Event const & e) override;

private:

  // Declare member data here.
  int runNumber_;
  int subrunNumber_;

  int nCalos_; // calo number
  int nXtals_; // crystal number
  double wiggleThreshold_; // official Energy threshold = 1860MeV * 0.75pe/MeV = 1395

  std::string clusterModuleLabel_;
  std::string clusterInstanceLabel_;

  TH1D *allWiggle_; // all wiggle plot
  std::vector<TH1D *> caloWiggles_; // wiggle plots for 24 calos
};


gm2calo::FitAna::FitAna(fhicl::ParameterSet const & p)
  :
  EDAnalyzer(p),
  runNumber_(-1),
  subrunNumber_(-1),
  nCalos_(p.get<int>("nCalos", 24)),
  nXtals_(p.get<int>("nXtals", 54)),
  wiggleThreshold_(p.get<double>("wiggleThreshold", 1400)),
  clusterModuleLabel_(p.get<std::string>("clusterModuleLabel", "hitCluster")),
  clusterInstanceLabel_(p.get<std::string>("clusterInstanceLabel", "cluster"))
 // More initializers here.
{
  art::ServiceHandle<art::TFileService> tfs;
  art::TFileDirectory allCaloDir = *tfs;

  allWiggle_ = allCaloDir.make<TH1D>("allCaloWiggle", "T Method, all calos; time [clock ticks]; N;", 4700, 0,560000);

  caloWiggles_.resize(nCalos_);
  for (int iCalo = 0; iCalo < nCalos_; ++iCalo) {
    caloWiggles_[iCalo] = allCaloDir.make<TH1D>(Form("wiggle_%i",iCalo + 1), Form("calo %i T Method; time; N", iCalo + 1), 4700, 0,560000);
  }
}

void gm2calo::FitAna::analyze(art::Event const & e)
{
  // Implementation of required member function here.
  runNumber_ = e.run();
  subrunNumber_ = e.subRun();

  const auto &clusterCol = *e.getValidHandle<CaloClusterArtRecordCollection>({clusterModuleLabel_, clusterInstanceLabel_});  
 
  calo_for_each(clusterCol, [&](const auto &cluster){
    int caloIndex = cluster.caloNum - 1;
    if (caloIndex > nCalos_) {
      throw cet::exception("FitAna")
          << "Found cluster with calo num " << cluster.caloNum
          << ", but n calos set to " << nCalos_ << "!\n";
    } else if (caloIndex < 0) {
      throw cet::exception("FitAna")
          << "Found cluster with calo num " << cluster.caloNum << "!\n";
    }

    if (cluster.energy > wiggleThreshold_) {
      allWiggle_->Fill(cluster.time);
      caloWiggles_[caloIndex]->Fill(cluster.time);
    }    
  });
}

DEFINE_ART_MODULE(gm2calo::FitAna)
