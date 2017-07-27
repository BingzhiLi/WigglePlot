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

  TH1D *allWiggle_; // all wiggle plot with wiggle threshold 1.86GeV
  std::vector<TH1D *> caloWiggles_; // wiggle plots for 24 calos with wiggle threshold 1.86GeV

  //////////////diff energy threshold 1.6 1.7 1.8 1.9 2.0 2.1 2.2 GeV * 0.75pe/MeV
  double th16;
  double th17;
  double th18;
  double th19;
  double th20;
  double th21;
  double th22;
  //////////////diff energy threshold histogram
  TH1D *threshold16;
  TH1D *threshold17;
  TH1D *threshold18;
  TH1D *threshold19;
  TH1D *threshold20;
  TH1D *threshold21;
  TH1D *threshold22;
  //////////////energy slices histogram
  TH1D *slice1617;
  TH1D *slice1718;
  TH1D *slice1819;
  TH1D *slice1920;
  TH1D *slice2021;
  TH1D *slice2122;
  TH1D *slice1618;
  TH1D *slice1820;
  TH1D *slice2022;
  
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
  clusterInstanceLabel_(p.get<std::string>("clusterInstanceLabel", "cluster")),
  th16(p.get<double>("th16", 1200)),
  th17(p.get<double>("th17", 1275)),
  th18(p.get<double>("th18", 1350)),
  th19(p.get<double>("th19", 1425)),
  th20(p.get<double>("th20", 1500)),
  th21(p.get<double>("th21", 1575)),
  th22(p.get<double>("th22", 1650))
{

  art::ServiceHandle<art::TFileService> tfs;
  art::TFileDirectory allCaloDir = *tfs;

  allWiggle_ = allCaloDir.make<TH1D>("allCaloWiggle", "T Method with threshold 1.86GeV, all calos; time [clock ticks]; N;", 4700, 0,560000);

  caloWiggles_.resize(nCalos_);
  for (int iCalo = 0; iCalo < nCalos_; ++iCalo) {
    caloWiggles_[iCalo] = allCaloDir.make<TH1D>(Form("wiggle_%i",iCalo + 1), Form("calo %i T Method with threshold 1.86GeV; time [clock ticks]; N", iCalo + 1), 4700, 0,560000);
  }

  threshold16 = allCaloDir.make<TH1D>("wigglethreshold1600MeV","T Method with threshold 1.6GeV, all calos; time [clock ticks]; N;", 4700, 0, 560000);
  threshold17 = allCaloDir.make<TH1D>("wigglethreshold1700MeV","T Method with threshold 1.7GeV, all calos; time [clock ticks]; N;", 4700, 0, 560000);
  threshold18 = allCaloDir.make<TH1D>("wigglethreshold1800MeV","T Method with threshold 1.8GeV, all calos; time [clock ticks]; N;", 4700, 0, 560000);
  threshold19 = allCaloDir.make<TH1D>("wigglethreshold1900MeV","T Method with threshold 1.9GeV, all calos; time [clock ticks]; N;", 4700, 0, 560000);
  threshold20 = allCaloDir.make<TH1D>("wigglethreshold2000MeV","T Method with threshold 2.0GeV, all calos; time [clock ticks]; N;", 4700, 0, 560000);
  threshold21 = allCaloDir.make<TH1D>("wigglethreshold2100MeV","T Method with threshold 2.1GeV, all calos; time [clock ticks]; N;", 4700, 0, 560000);
  threshold22 = allCaloDir.make<TH1D>("wigglethreshold2200MeV","T Method with threshold 2.2GeV, all calos; time [clock ticks]; N;", 4700, 0, 560000);

  slice1617 = allCaloDir.make<TH1D>("energy_slice_1600_1700MeV","T Method with energy slice 1.6 to 1.7 GeV, all calos; time [clock ticks]; N;", 4700, 0, 560000);
  slice1718 = allCaloDir.make<TH1D>("energy_slice_1700_1800MeV","T Method with energy slice 1.7 to 1.8 GeV, all calos; time [clock ticks]; N;", 4700, 0, 560000);
  slice1819 = allCaloDir.make<TH1D>("energy_slice_1800_1900MeV","T Method with energy slice 1.8 to 1.9 GeV, all calos; time [clock ticks]; N;", 4700, 0, 560000);
  slice1920 = allCaloDir.make<TH1D>("energy_slice_1900_2000MeV","T Method with energy slice 1.9 to 2.0 GeV, all calos; time [clock ticks]; N;", 4700, 0, 560000);
  slice2021 = allCaloDir.make<TH1D>("energy_slice_2000_2100MeV","T Method with energy slice 2.0 to 2.1 GeV, all calos; time [clock ticks]; N;", 4700, 0, 560000);
  slice2122 = allCaloDir.make<TH1D>("energy_slice_2100_2200MeV","T Method with energy slice 2.1 to 2.2 GeV, all calos; time [clock ticks]; N;", 4700, 0, 560000);

  slice1618 = allCaloDir.make<TH1D>("energy_slice_1600_1800MeV","T Method with energy slice 1.6 to 1.8 GeV, all calos; time [clock ticks]; N;", 4700, 0, 560000);
  slice1820 = allCaloDir.make<TH1D>("energy_slice_1800_2000MeV","T Method with energy slice 1.8 to 2.0 GeV, all calos; time [clock ticks]; N;", 4700, 0, 560000);
  slice2022 = allCaloDir.make<TH1D>("energy_slice_2000_2200MeV","T Method with energy slice 2.0 to 2.2 GeV, all calos; time [clock ticks]; N;", 4700, 0, 560000);
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

    //energy threshold above 1.6 1.7 1.8 1.9 2.0 2.1 2.2 GeV
    if (cluster.energy > th16) { threshold16->Fill(cluster.time); }
    if (cluster.energy > th17) { threshold17->Fill(cluster.time); }
    if (cluster.energy > th18) { threshold18->Fill(cluster.time); }
    if (cluster.energy > th19) { threshold19->Fill(cluster.time); }
    if (cluster.energy > th20) { threshold20->Fill(cluster.time); } 
    if (cluster.energy > th21) { threshold21->Fill(cluster.time); }
    if (cluster.energy > th22) { threshold22->Fill(cluster.time); }
    
    //energy slices 1.6-1.7 1.7-1.8 1.8-1.9 1.9-2.0 2.0-2.1 2.1-2.2 
    if (cluster.energy > th16 && cluster.energy < th17) { slice1617->Fill(cluster.time); }
    if (cluster.energy > th17 && cluster.energy < th18) { slice1718->Fill(cluster.time); }
    if (cluster.energy > th18 && cluster.energy < th19) { slice1819->Fill(cluster.time); }
    if (cluster.energy > th19 && cluster.energy < th20) { slice1920->Fill(cluster.time); }
    if (cluster.energy > th20 && cluster.energy < th21) { slice2021->Fill(cluster.time); }
    if (cluster.energy > th21 && cluster.energy < th22) { slice2122->Fill(cluster.time); }

    //energy slices 1.6-1.8 1.8-2.0 2.0-2.2
    if (cluster.energy > th16 && cluster.energy < th18) { slice1618->Fill(cluster.time); }
    if (cluster.energy > th18 && cluster.energy < th20) { slice1820->Fill(cluster.time); }
    if (cluster.energy > th20 && cluster.energy < th22) { slice2022->Fill(cluster.time); }    

  });

}

DEFINE_ART_MODULE(gm2calo::FitAna)
