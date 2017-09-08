void FitRelatedAna(){

  TFile *f=new TFile("parameter20.root");
  TTree *fit_parameter = (TTree*)f->Get("fit_parameter");

  double Ta_L[8],Ta_C[8],tau_L[8],tau_C[8],N_L[8],N_C[8],phi_L[8],phi_C[8],A_L[8],A_C[8];
  double Ta_L_err[8],Ta_C_err[8],tau_L_err[8],tau_C_err[8],N_L_err[8],N_C_err[8],phi_L_err[8],phi_C_err[8],A_L_err[8],A_C_err[8]; 
  double chi2ndf[8]; 

  double range[161],range_err[161];
  for(int i=0;i<161;i++){
    range[i]=i+40;
    range_err[i]=0;
  }
   
  double Ta_L_1860[161],Ta_L_1600[161],Ta_L_1700[161],Ta_L_1800[161],Ta_L_1900[161],Ta_L_2000[161],Ta_L_2100[161],Ta_L_2200[161];
  double Ta_C_1860[161],Ta_C_1600[161],Ta_C_1700[161],Ta_C_1800[161],Ta_C_1900[161],Ta_C_2000[161],Ta_C_2100[161],Ta_C_2200[161];
  double tau_L_1860[161],tau_L_1600[161],tau_L_1700[161],tau_L_1800[161],tau_L_1900[161],tau_L_2000[161],tau_L_2100[161],tau_L_2200[161];
  double tau_C_1860[161],tau_C_1600[161],tau_C_1700[161],tau_C_1800[161],tau_C_1900[161],tau_C_2000[161],tau_C_2100[161],tau_C_2200[161];
  double N_L_1860[161],N_L_1600[161],N_L_1700[161],N_L_1800[161],N_L_1900[161],N_L_2000[161],N_L_2100[161],N_L_2200[161];
  double N_C_1860[161],N_C_1600[161],N_C_1700[161],N_C_1800[161],N_C_1900[161],N_C_2000[161],N_C_2100[161],N_C_2200[161];
  double phi_L_1860[161],phi_L_1600[161],phi_L_1700[161],phi_L_1800[161],phi_L_1900[161],phi_L_2000[161],phi_L_2100[161],phi_L_2200[161];
  double phi_C_1860[161],phi_C_1600[161],phi_C_1700[161],phi_C_1800[161],phi_C_1900[161],phi_C_2000[161],phi_C_2100[161],phi_C_2200[161];
  double A_L_1860[161],A_L_1600[161],A_L_1700[161],A_L_1800[161],A_L_1900[161],A_L_2000[161],A_L_2100[161],A_L_2200[161];
  double A_C_1860[161],A_C_1600[161],A_C_1700[161],A_C_1800[161],A_C_1900[161],A_C_2000[161],A_C_2100[161],A_C_2200[161];

  double Ta_L_1860_err[161],Ta_L_1600_err[161],Ta_L_1700_err[161],Ta_L_1800_err[161],Ta_L_1900_err[161],Ta_L_2000_err[161],Ta_L_2100_err[161],Ta_L_2200_err[161];
  double Ta_C_1860_err[161],Ta_C_1600_err[161],Ta_C_1700_err[161],Ta_C_1800_err[161],Ta_C_1900_err[161],Ta_C_2000_err[161],Ta_C_2100_err[161],Ta_C_2200_err[161];
  double tau_L_1860_err[161],tau_L_1600_err[161],tau_L_1700_err[161],tau_L_1800_err[161],tau_L_1900_err[161],tau_L_2000_err[161],tau_L_2100_err[161],tau_L_2200_err[161];
  double tau_C_1860_err[161],tau_C_1600_err[161],tau_C_1700_err[161],tau_C_1800_err[161],tau_C_1900_err[161],tau_C_2000_err[161],tau_C_2100_err[161],tau_C_2200_err[161];
  double N_L_1860_err[161],N_L_1600_err[161],N_L_1700_err[161],N_L_1800_err[161],N_L_1900_err[161],N_L_2000_err[161],N_L_2100_err[161],N_L_2200_err[161];
  double N_C_1860_err[161],N_C_1600_err[161],N_C_1700_err[161],N_C_1800_err[161],N_C_1900_err[161],N_C_2000_err[161],N_C_2100_err[161],N_C_2200_err[161];
  double phi_L_1860_err[161],phi_L_1600_err[161],phi_L_1700_err[161],phi_L_1800_err[161],phi_L_1900_err[161],phi_L_2000_err[161],phi_L_2100_err[161],phi_L_2200_err[161];
  double phi_C_1860_err[161],phi_C_1600_err[161],phi_C_1700_err[161],phi_C_1800_err[161],phi_C_1900_err[161],phi_C_2000_err[161],phi_C_2100_err[161],phi_C_2200_err[161];
  double A_L_1860_err[161],A_L_1600_err[161],A_L_1700_err[161],A_L_1800_err[161],A_L_1900_err[161],A_L_2000_err[161],A_L_2100_err[161],A_L_2200_err[161];
  double A_C_1860_err[161],A_C_1600_err[161],A_C_1700_err[161],A_C_1800_err[161],A_C_1900_err[161],A_C_2000_err[161],A_C_2100_err[161],A_C_2200_err[161];

  double chi2ndf1860[161],chi2ndf1600[161],chi2ndf1700[161],chi2ndf1800[161],chi2ndf1900[161],chi2ndf2000[161],chi2ndf2100[161],chi2ndf2200[161];

  fit_parameter->SetBranchAddress("Ta_L",&Ta_L[0]);
  fit_parameter->SetBranchAddress("Ta_C",&Ta_C[0]);
  fit_parameter->SetBranchAddress("tau_L",&tau_L[0]);
  fit_parameter->SetBranchAddress("tau_C",&tau_C[0]);
  fit_parameter->SetBranchAddress("N_L",&N_L[0]);
  fit_parameter->SetBranchAddress("N_C",&N_C[0]);
  fit_parameter->SetBranchAddress("phi_L",&phi_L[0]);
  fit_parameter->SetBranchAddress("phi_C",&phi_C[0]);
  fit_parameter->SetBranchAddress("A_L",&A_L[0]);
  fit_parameter->SetBranchAddress("A_C",&A_C[0]);

  fit_parameter->SetBranchAddress("Ta_L_err",&Ta_L_err[0]);
  fit_parameter->SetBranchAddress("Ta_C_err",&Ta_C_err[0]);
  fit_parameter->SetBranchAddress("tau_L_err",&tau_L_err[0]);
  fit_parameter->SetBranchAddress("tau_C_err",&tau_C_err[0]);
  fit_parameter->SetBranchAddress("N_L_err",&N_L_err[0]);
  fit_parameter->SetBranchAddress("N_C_err",&N_C_err[0]);
  fit_parameter->SetBranchAddress("phi_L_err",&phi_L_err[0]);
  fit_parameter->SetBranchAddress("phi_C_err",&phi_C_err[0]);
  fit_parameter->SetBranchAddress("A_L_err",&A_L_err[0]);
  fit_parameter->SetBranchAddress("A_C_err",&A_C_err[0]);

  fit_parameter->SetBranchAddress("chi2ndf",&chi2ndf[0]);
  
  Int_t nentries = (Int_t)fit_parameter->GetEntries();

  for (int i=0; i<nentries; i++) {
    fit_parameter->GetEntry(i);
    for (int j=0;j<8;j++){
      if(j==0){
        Ta_L_1860[i]=Ta_L[j];
        Ta_C_1860[i]=Ta_C[j];
        tau_L_1860[i]=tau_L[j];
        tau_C_1860[i]=tau_C[j];
        N_L_1860[i]=N_L[j];
        N_C_1860[i]=N_C[j];
        phi_L_1860[i]=phi_L[j];
        phi_C_1860[i]=phi_C[j];
        A_L_1860[i]=A_L[j];
        A_C_1860[i]=A_C[j];

        Ta_L_1860_err[i]=Ta_L_err[j];
        Ta_C_1860_err[i]=Ta_C_err[j];
        tau_L_1860_err[i]=tau_L_err[j];
        tau_C_1860_err[i]=tau_C_err[j];
        N_L_1860_err[i]=N_L_err[j];
        N_C_1860_err[i]=N_C_err[j];
        phi_L_1860_err[i]=phi_L_err[j];
        phi_C_1860_err[i]=phi_C_err[j];
        A_L_1860_err[i]=A_L_err[j];
        A_C_1860_err[i]=A_C_err[j];
     
        chi2ndf1860[i]=chi2ndf[j];
      }

      if(j==1){
        Ta_L_1600[i]=Ta_L[j];
        Ta_C_1600[i]=Ta_C[j];
        tau_L_1600[i]=tau_L[j];
        tau_C_1600[i]=tau_C[j];
        N_L_1600[i]=N_L[j];
        N_C_1600[i]=N_C[j];
        phi_L_1600[i]=phi_L[j];
        phi_C_1600[i]=phi_C[j];
        A_L_1600[i]=A_L[j];
        A_C_1600[i]=A_C[j];

        Ta_L_1600_err[i]=Ta_L_err[j];
        Ta_C_1600_err[i]=Ta_C_err[j];
        tau_L_1600_err[i]=tau_L_err[j];
        tau_C_1600_err[i]=tau_C_err[j];
        N_L_1600_err[i]=N_L_err[j];
        N_C_1600_err[i]=N_C_err[j];
        phi_L_1600_err[i]=phi_L_err[j];
        phi_C_1600_err[i]=phi_C_err[j];
        A_L_1600_err[i]=A_L_err[j];
        A_C_1600_err[i]=A_C_err[j]; 

        chi2ndf1600[i]=chi2ndf[j];       
      }

      if(j==2){
        Ta_L_1700[i]=Ta_L[j];
        Ta_C_1700[i]=Ta_C[j];
        tau_L_1700[i]=tau_L[j];
        tau_C_1700[i]=tau_C[j];
        N_L_1700[i]=N_L[j];
        N_C_1700[i]=N_C[j];
        phi_L_1700[i]=phi_L[j];
        phi_C_1700[i]=phi_C[j];
        A_L_1700[i]=A_L[j];
        A_C_1700[i]=A_C[j];

        Ta_L_1700_err[i]=Ta_L_err[j];
        Ta_C_1700_err[i]=Ta_C_err[j];
        tau_L_1700_err[i]=tau_L_err[j];
        tau_C_1700_err[i]=tau_C_err[j];
        N_L_1700_err[i]=N_L_err[j];
        N_C_1700_err[i]=N_C_err[j];
        phi_L_1700_err[i]=phi_L_err[j];
        phi_C_1700_err[i]=phi_C_err[j];
        A_L_1700_err[i]=A_L_err[j];
        A_C_1700_err[i]=A_C_err[j];

        chi2ndf1700[i]=chi2ndf[j];
      }

      if(j==3){
        Ta_L_1800[i]=Ta_L[j];
        Ta_C_1800[i]=Ta_C[j];
        tau_L_1800[i]=tau_L[j];
        tau_C_1800[i]=tau_C[j];
        N_L_1800[i]=N_L[j];
        N_C_1800[i]=N_C[j];
        phi_L_1800[i]=phi_L[j];
        phi_C_1800[i]=phi_C[j];
        A_L_1800[i]=A_L[j];
        A_C_1800[i]=A_C[j];

        Ta_L_1800_err[i]=Ta_L_err[j];
        Ta_C_1800_err[i]=Ta_C_err[j];
        tau_L_1800_err[i]=tau_L_err[j];
        tau_C_1800_err[i]=tau_C_err[j];
        N_L_1800_err[i]=N_L_err[j];
        N_C_1800_err[i]=N_C_err[j];
        phi_L_1800_err[i]=phi_L_err[j];
        phi_C_1800_err[i]=phi_C_err[j];
        A_L_1800_err[i]=A_L_err[j];
        A_C_1800_err[i]=A_C_err[j];

        chi2ndf1800[i]=chi2ndf[j];
      }

      if(j==4){
        Ta_L_1900[i]=Ta_L[j];
        Ta_C_1900[i]=Ta_C[j];
        tau_L_1900[i]=tau_L[j];
        tau_C_1900[i]=tau_C[j];
        N_L_1900[i]=N_L[j];
        N_C_1900[i]=N_C[j];
        phi_L_1900[i]=phi_L[j];
        phi_C_1900[i]=phi_C[j];
        A_L_1900[i]=A_L[j];
        A_C_1900[i]=A_C[j];

        Ta_L_1900_err[i]=Ta_L_err[j];
        Ta_C_1900_err[i]=Ta_C_err[j];
        tau_L_1900_err[i]=tau_L_err[j];
        tau_C_1900_err[i]=tau_C_err[j];
        N_L_1900_err[i]=N_L_err[j];
        N_C_1900_err[i]=N_C_err[j];
        phi_L_1900_err[i]=phi_L_err[j];
        phi_C_1900_err[i]=phi_C_err[j];
        A_L_1900_err[i]=A_L_err[j];
        A_C_1900_err[i]=A_C_err[j];

        chi2ndf1900[i]=chi2ndf[j];
      }

      if(j==5){
        Ta_L_2000[i]=Ta_L[j];
        Ta_C_2000[i]=Ta_C[j];
        tau_L_2000[i]=tau_L[j];
        tau_C_2000[i]=tau_C[j];
        N_L_2000[i]=N_L[j];
        N_C_2000[i]=N_C[j];
        phi_L_2000[i]=phi_L[j];
        phi_C_2000[i]=phi_C[j];
        A_L_2000[i]=A_L[j];
        A_C_2000[i]=A_C[j];

        Ta_L_2000_err[i]=Ta_L_err[j];
        Ta_C_2000_err[i]=Ta_C_err[j];
        tau_L_2000_err[i]=tau_L_err[j];
        tau_C_2000_err[i]=tau_C_err[j];
        N_L_2000_err[i]=N_L_err[j];
        N_C_2000_err[i]=N_C_err[j];
        phi_L_2000_err[i]=phi_L_err[j];
        phi_C_2000_err[i]=phi_C_err[j];
        A_L_2000_err[i]=A_L_err[j];
        A_C_2000_err[i]=A_C_err[j];

        chi2ndf2000[i]=chi2ndf[j];
      }

      if(j==6){
        Ta_L_2100[i]=Ta_L[j];
        Ta_C_2100[i]=Ta_C[j];
        tau_L_2100[i]=tau_L[j];
        tau_C_2100[i]=tau_C[j];
        N_L_2100[i]=N_L[j];
        N_C_2100[i]=N_C[j];
        phi_L_2100[i]=phi_L[j];
        phi_C_2100[i]=phi_C[j];
        A_L_2100[i]=A_L[j];
        A_C_2100[i]=A_C[j];

        Ta_L_2100_err[i]=Ta_L_err[j];
        Ta_C_2100_err[i]=Ta_C_err[j];
        tau_L_2100_err[i]=tau_L_err[j];
        tau_C_2100_err[i]=tau_C_err[j];
        N_L_2100_err[i]=N_L_err[j];
        N_C_2100_err[i]=N_C_err[j];
        phi_L_2100_err[i]=phi_L_err[j];
        phi_C_2100_err[i]=phi_C_err[j];
        A_L_2100_err[i]=A_L_err[j];
        A_C_2100_err[i]=A_C_err[j];

        chi2ndf2100[i]=chi2ndf[j];
      }
 
      if(j==7){
        Ta_L_2200[i]=Ta_L[j];
        Ta_C_2200[i]=Ta_C[j];
        tau_L_2200[i]=tau_L[j];
        tau_C_2200[i]=tau_C[j];
        N_L_2200[i]=N_L[j];
        N_C_2200[i]=N_C[j];
        phi_L_2200[i]=phi_L[j];
        phi_C_2200[i]=phi_C[j];
        A_L_2200[i]=A_L[j];
        A_C_2200[i]=A_C[j];

        Ta_L_2200_err[i]=Ta_L_err[j];
        Ta_C_2200_err[i]=Ta_C_err[j];
        tau_L_2200_err[i]=tau_L_err[j];
        tau_C_2200_err[i]=tau_C_err[j];
        N_L_2200_err[i]=N_L_err[j];
        N_C_2200_err[i]=N_C_err[j];
        phi_L_2200_err[i]=phi_L_err[j];
        phi_C_2200_err[i]=phi_C_err[j];
        A_L_2200_err[i]=A_L_err[j];
        A_C_2200_err[i]=A_C_err[j];

        chi2ndf2200[i]=chi2ndf[j];
      }

    }
  
  }

  //likelihood: Ta vs fit range
  TCanvas *c1=new TCanvas("c1","c1",1200,800);

  TGraph *TaL1860=new TGraphErrors(161,range,Ta_L_1860,range_err,Ta_L_1860_err);
  TaL1860->SetMarkerStyle(20);
  TaL1860->SetMarkerColor(1);
  TaL1860->SetLineColor(1);

  TGraph *TaL1600=new TGraphErrors(161,range,Ta_L_1600,range_err,Ta_L_1600_err);
  TaL1600->SetMarkerStyle(20);
  TaL1600->SetMarkerColor(2);
  TaL1600->SetLineColor(2);

  TGraph *TaL1700=new TGraphErrors(161,range,Ta_L_1700,range_err,Ta_L_1700_err);
  TaL1700->SetMarkerStyle(20);
  TaL1700->SetMarkerColor(3);
  TaL1700->SetLineColor(3);

  TGraph *TaL1800=new TGraphErrors(161,range,Ta_L_1800,range_err,Ta_L_1800_err);
  TaL1800->SetMarkerStyle(20);
  TaL1800->SetMarkerColor(4);
  TaL1800->SetLineColor(4);

  TGraph *TaL1900=new TGraphErrors(161,range,Ta_L_1900,range_err,Ta_L_1900_err);
  TaL1900->SetMarkerStyle(20);
  TaL1900->SetMarkerColor(5);
  TaL1900->SetLineColor(5);

  TGraph *TaL2000=new TGraphErrors(161,range,Ta_L_2000,range_err,Ta_L_2000_err);
  TaL2000->SetMarkerStyle(20);
  TaL2000->SetMarkerColor(6);
  TaL2000->SetLineColor(6);

  TGraph *TaL2100=new TGraphErrors(161,range,Ta_L_2100,range_err,Ta_L_2100_err);
  TaL2100->SetMarkerStyle(20);
  TaL2100->SetMarkerColor(7);
  TaL2100->SetLineColor(7);

  TGraph *TaL2200=new TGraphErrors(161,range,Ta_L_2200,range_err,Ta_L_2200_err);
  TaL2200->SetMarkerStyle(20);
  TaL2200->SetMarkerColor(8);
  TaL2200->SetLineColor(8);

  TMultiGraph *mg_Ta_L=new TMultiGraph();
  mg_Ta_L->Add(TaL1860,"AP");
  mg_Ta_L->Add(TaL1600,"AP");
//  mg_Ta_L->Add(TaL1700,"AP");
//  mg_Ta_L->Add(TaL1800,"AP");
//  mg_Ta_L->Add(TaL1900,"AP");
//  mg_Ta_L->Add(TaL2000,"AP");
//  mg_Ta_L->Add(TaL2100,"AP");
  mg_Ta_L->Add(TaL2200,"AP");  
  mg_Ta_L->SetTitle("T_{a} vs fit range (likelihood: start point 20);end point;T_{a}");
  mg_Ta_L->Draw("a");

  gStyle->SetLegendBorderSize(0);
  TLegend* mg_Ta_L_leg=new TLegend(0.7,0.2,0.85,0.4);
  mg_Ta_L_leg->AddEntry(TaL1860,"1.86GeV","P");
  mg_Ta_L_leg->AddEntry(TaL1600,"1.6 GeV","P");
//  mg_Ta_L_leg->AddEntry(TaL1700,"1.7 GeV","P");
//  mg_Ta_L_leg->AddEntry(TaL1800,"1.8 GeV","P");
//  mg_Ta_L_leg->AddEntry(TaL1900,"1.9 GeV","P");
//  mg_Ta_L_leg->AddEntry(TaL2000,"2.0 GeV","P");
//  mg_Ta_L_leg->AddEntry(TaL2100,"2.1 GeV","P");
  mg_Ta_L_leg->AddEntry(TaL2200,"2.2 GeV","P");
  mg_Ta_L_leg->Draw("");  

  gPad->Modified();
  mg_Ta_L->SetMinimum(4.3);
  mg_Ta_L->SetMaximum(4.4);  

  //likelihood: gamma_tau vs fit range
  TCanvas *c2=new TCanvas("c2","c2",1200,800);

  TGraph *tau1860=new TGraphErrors(161,range,tau_L_1860,range_err,tau_L_1860_err);
  tau1860->SetMarkerStyle(20);
  tau1860->SetMarkerColor(1);
  tau1860->SetLineColor(1);

  TGraph *tau1600=new TGraphErrors(161,range,tau_L_1600,range_err,tau_L_1600_err);
  tau1600->SetMarkerStyle(20);
  tau1600->SetMarkerColor(2);
  tau1600->SetLineColor(2);

  TGraph *tau1700=new TGraphErrors(161,range,tau_L_1700,range_err,tau_L_1700_err);
  tau1700->SetMarkerStyle(20);
  tau1700->SetMarkerColor(3);
  tau1700->SetLineColor(3);

  TGraph *tau1800=new TGraphErrors(161,range,tau_L_1800,range_err,tau_L_1800_err);
  tau1800->SetMarkerStyle(20);
  tau1800->SetMarkerColor(4);
  tau1800->SetLineColor(4);

  TGraph *tau1900=new TGraphErrors(161,range,tau_L_1900,range_err,tau_L_1900_err);
  tau1900->SetMarkerStyle(20);
  tau1900->SetMarkerColor(5);
  tau1900->SetLineColor(5);

  TGraph *tau2000=new TGraphErrors(161,range,tau_L_2000,range_err,tau_L_2000_err);
  tau2000->SetMarkerStyle(20);
  tau2000->SetMarkerColor(6);
  tau2000->SetLineColor(6);

  TGraph *tau2100=new TGraphErrors(161,range,tau_L_2100,range_err,tau_L_2100_err);
  tau2100->SetMarkerStyle(20);
  tau2100->SetMarkerColor(7);
  tau2100->SetLineColor(7);

  TGraph *tau2200=new TGraphErrors(161,range,tau_L_2200,range_err,tau_L_2200_err);
  tau2200->SetMarkerStyle(20);
  tau2200->SetMarkerColor(8);
  tau2200->SetLineColor(8);

  TMultiGraph *mg_tau_L=new TMultiGraph();
  mg_tau_L->Add(tau1860,"AP");
  mg_tau_L->Add(tau1600,"AP");
//  mg_tau_L->Add(tau1700,"AP");
//  mg_tau_L->Add(tau1800,"AP");
//  mg_tau_L->Add(tau1900,"AP");
//  mg_tau_L->Add(tau2000,"AP");
//  mg_tau_L->Add(tau2100,"AP");
  mg_tau_L->Add(tau2200,"AP");  
  mg_tau_L->SetTitle("#gamma#tau_{#mu} vs fit range (likelihood: start point 20);end point;#gamma#tau_{#mu}");
  mg_tau_L->Draw("a");

  gStyle->SetLegendBorderSize(0);
  TLegend* mg_tau_L_leg=new TLegend(0.7,0.6,0.85,0.8);
  mg_tau_L_leg->AddEntry(tau1860,"1.86GeV","P");
  mg_tau_L_leg->AddEntry(tau1600,"1.6 GeV","P");
//  mg_tau_L_leg->AddEntry(tau1700,"1.7 GeV","P");
//  mg_tau_L_leg->AddEntry(tau1800,"1.8 GeV","P");
//  mg_tau_L_leg->AddEntry(tau1900,"1.9 GeV","P");
//  mg_tau_L_leg->AddEntry(tau2000,"2.0 GeV","P");
//  mg_tau_L_leg->AddEntry(tau2100,"2.1 GeV","P");
  mg_tau_L_leg->AddEntry(tau2200,"2.2 GeV","P");
  mg_tau_L_leg->Draw(""); 

  gPad->Modified();
  mg_tau_L->SetMinimum(50);
  mg_tau_L->SetMaximum(130);

  //likelihood: A vs fit range
  TCanvas *c3=new TCanvas("c3","c3",1200,800);

  TGraph *A1860=new TGraphErrors(161,range,A_L_1860,range_err,A_L_1860_err);
  A1860->SetMarkerStyle(20);
  A1860->SetMarkerColor(1);
  A1860->SetLineColor(1);

  TGraph *A1600=new TGraphErrors(161,range,A_L_1600,range_err,A_L_1600_err);
  A1600->SetMarkerStyle(20);
  A1600->SetMarkerColor(2);
  A1600->SetLineColor(2);

  TGraph *A1700=new TGraphErrors(161,range,A_L_1700,range_err,A_L_1700_err);
  A1700->SetMarkerStyle(20);
  A1700->SetMarkerColor(3);
  A1700->SetLineColor(3);

  TGraph *A1800=new TGraphErrors(161,range,A_L_1800,range_err,A_L_1800_err);
  A1800->SetMarkerStyle(20);
  A1800->SetMarkerColor(4);
  A1800->SetLineColor(4);

  TGraph *A1900=new TGraphErrors(161,range,A_L_1900,range_err,A_L_1900_err);
  A1900->SetMarkerStyle(20);
  A1900->SetMarkerColor(5);
  A1900->SetLineColor(5);

  TGraph *A2000=new TGraphErrors(161,range,A_L_2000,range_err,A_L_2000_err);
  A2000->SetMarkerStyle(20);
  A2000->SetMarkerColor(6);
  A2000->SetLineColor(6);

  TGraph *A2100=new TGraphErrors(161,range,A_L_2100,range_err,A_L_2100_err);
  A2100->SetMarkerStyle(20);
  A2100->SetMarkerColor(7);
  A2100->SetLineColor(7);

  TGraph *A2200=new TGraphErrors(161,range,A_L_2200,range_err,A_L_2200_err);
  A2200->SetMarkerStyle(20);
  A2200->SetMarkerColor(8);
  A2200->SetLineColor(8);

  TMultiGraph *mg_A_L=new TMultiGraph();
  mg_A_L->Add(A1860,"AP");
  mg_A_L->Add(A1600,"AP");
//  mg_A_L->Add(A1700,"AP");
// mg_A_L->Add(A1800,"AP");
//  mg_A_L->Add(A1900,"AP");
//  mg_A_L->Add(A2000,"AP");
//  mg_A_L->Add(A2100,"AP");
  mg_A_L->Add(A2200,"AP");  
  mg_A_L->SetTitle("A vs fit range (likelihood: start point 20);end point;A");
  mg_A_L->Draw("a");

  gStyle->SetLegendBorderSize(0);
  TLegend* mg_A_L_leg=new TLegend(0.7,0.2,0.85,0.4);
  mg_A_L_leg->AddEntry(A1860,"1.86GeV","P");
  mg_A_L_leg->AddEntry(A1600,"1.6 GeV","P");
//  mg_A_L_leg->AddEntry(A1700,"1.7 GeV","P");
//  mg_A_L_leg->AddEntry(A1800,"1.8 GeV","P");
//  mg_A_L_leg->AddEntry(A1900,"1.9 GeV","P");
// mg_A_L_leg->AddEntry(A2000,"2.0 GeV","P");
//  mg_A_L_leg->AddEntry(A2100,"2.1 GeV","P");
  mg_A_L_leg->AddEntry(A2200,"2.2 GeV","P");
  mg_A_L_leg->Draw("");  

  //likelihood: phi vs fit range
  TCanvas *c4=new TCanvas("c4","c4",1200,800);

  TGraph *phi1860=new TGraphErrors(161,range,phi_L_1860,range_err,phi_L_1860_err);
  phi1860->SetMarkerStyle(20);
  phi1860->SetMarkerColor(1);
  phi1860->SetLineColor(1);

  TGraph *phi1600=new TGraphErrors(161,range,phi_L_1600,range_err,phi_L_1600_err);
  phi1600->SetMarkerStyle(20);
  phi1600->SetMarkerColor(2);
  phi1600->SetLineColor(2);

  TGraph *phi1700=new TGraphErrors(161,range,phi_L_1700,range_err,phi_L_1700_err);
  phi1700->SetMarkerStyle(20);
  phi1700->SetMarkerColor(3);
  phi1700->SetLineColor(3);

  TGraph *phi1800=new TGraphErrors(161,range,phi_L_1800,range_err,phi_L_1800_err);
  phi1800->SetMarkerStyle(20);
  phi1800->SetMarkerColor(4);
  phi1800->SetLineColor(4);

  TGraph *phi1900=new TGraphErrors(161,range,phi_L_1900,range_err,phi_L_1900_err);
  phi1900->SetMarkerStyle(20);
  phi1900->SetMarkerColor(5);
  phi1900->SetLineColor(5);

  TGraph *phi2000=new TGraphErrors(161,range,phi_L_2000,range_err,phi_L_2000_err);
  phi2000->SetMarkerStyle(20);
  phi2000->SetMarkerColor(6);
  phi2000->SetLineColor(6);

  TGraph *phi2100=new TGraphErrors(161,range,phi_L_2100,range_err,phi_L_2100_err);
  phi2100->SetMarkerStyle(20);
  phi2100->SetMarkerColor(7);
  phi2100->SetLineColor(7);

  TGraph *phi2200=new TGraphErrors(161,range,phi_L_2200,range_err,phi_L_2200_err);
  phi2200->SetMarkerStyle(20);
  phi2200->SetMarkerColor(8);
  phi2200->SetLineColor(8);

  TMultiGraph *mg_phi_L=new TMultiGraph();
  mg_phi_L->Add(phi1860,"AP");
  mg_phi_L->Add(phi1600,"AP");
//  mg_phi_L->Add(phi1700,"AP");
//  mg_phi_L->Add(phi1800,"AP");
//  mg_phi_L->Add(phi1900,"AP");
//  mg_phi_L->Add(phi2000,"AP");
//  mg_phi_L->Add(phi2100,"AP");
  mg_phi_L->Add(phi2200,"AP");  
  mg_phi_L->SetTitle("phi vs fit range (likelihood: start point 20);end point;phi");
  mg_phi_L->Draw("a");

  gStyle->SetLegendBorderSize(0);
  TLegend* mg_phi_L_leg=new TLegend(0.7,0.2,0.85,0.4);
  mg_phi_L_leg->AddEntry(phi1860,"1.86GeV","P");
  mg_phi_L_leg->AddEntry(phi1600,"1.6 GeV","P");
//  mg_phi_L_leg->AddEntry(phi1700,"1.7 GeV","P");
//  mg_phi_L_leg->AddEntry(phi1800,"1.8 GeV","P");
//  mg_phi_L_leg->AddEntry(phi1900,"1.9 GeV","P");
//  mg_phi_L_leg->AddEntry(phi2000,"2.0 GeV","P");
// mg_phi_L_leg->AddEntry(phi2100,"2.1 GeV","P");
  mg_phi_L_leg->AddEntry(phi2200,"2.2 GeV","P");
  mg_phi_L_leg->Draw("");  

  gPad->Modified();
  mg_phi_L->SetMinimum(-10);
  mg_phi_L->SetMaximum(0);

  //likelihood: N vs fit range
  TCanvas *c5=new TCanvas("c5","c5",1200,800);

  TGraph *N1860=new TGraphErrors(161,range,N_L_1860,range_err,N_L_1860_err);
  N1860->SetMarkerStyle(20);
  N1860->SetMarkerColor(1);
  N1860->SetLineColor(1);

  TGraph *N1600=new TGraphErrors(161,range,N_L_1600,range_err,N_L_1600_err);
  N1600->SetMarkerStyle(20);
  N1600->SetMarkerColor(2);
  N1600->SetLineColor(2);

  TGraph *N1700=new TGraphErrors(161,range,N_L_1700,range_err,N_L_1700_err);
  N1700->SetMarkerStyle(20);
  N1700->SetMarkerColor(3);
  N1700->SetLineColor(3);

  TGraph *N1800=new TGraphErrors(161,range,N_L_1800,range_err,N_L_1800_err);
  N1800->SetMarkerStyle(20);
  N1800->SetMarkerColor(4);
  N1800->SetLineColor(4);

  TGraph *N1900=new TGraphErrors(161,range,N_L_1900,range_err,N_L_1900_err);
  N1900->SetMarkerStyle(20);
  N1900->SetMarkerColor(5);
  N1900->SetLineColor(5);

  TGraph *N2000=new TGraphErrors(161,range,N_L_2000,range_err,N_L_2000_err);
  N2000->SetMarkerStyle(20);
  N2000->SetMarkerColor(6);
  N2000->SetLineColor(6);

  TGraph *N2100=new TGraphErrors(161,range,N_L_2100,range_err,N_L_2100_err);
  N2100->SetMarkerStyle(20);
  N2100->SetMarkerColor(7);
  N2100->SetLineColor(7);

  TGraph *N2200=new TGraphErrors(161,range,N_L_2200,range_err,N_L_2200_err);
  N2200->SetMarkerStyle(20);
  N2200->SetMarkerColor(8);
  N2200->SetLineColor(8);

  TMultiGraph *mg_N_L=new TMultiGraph();
  mg_N_L->Add(N1860,"AP");
  mg_N_L->Add(N1600,"AP");
//  mg_N_L->Add(N1700,"AP");
//  mg_N_L->Add(N1800,"AP");
//  mg_N_L->Add(N1900,"AP");
//  mg_N_L->Add(N2000,"AP");
//  mg_N_L->Add(N2100,"AP");
  mg_N_L->Add(N2200,"AP");  
  mg_N_L->SetTitle("N vs fit range (likelihood: start point 20);end point;N");
  mg_N_L->Draw("a");

  gStyle->SetLegendBorderSize(0);
  TLegend* mg_N_L_leg=new TLegend(0.7,0.2,0.85,0.4);
  mg_N_L_leg->AddEntry(N1860,"1.86GeV","P");
  mg_N_L_leg->AddEntry(N1600,"1.6 GeV","P");
//  mg_N_L_leg->AddEntry(N1700,"1.7 GeV","P");
//  mg_N_L_leg->AddEntry(N1800,"1.8 GeV","P");
//  mg_N_L_leg->AddEntry(N1900,"1.9 GeV","P");
//  mg_N_L_leg->AddEntry(N2000,"2.0 GeV","P");
//  mg_N_L_leg->AddEntry(N2100,"2.1 GeV","P");
  mg_N_L_leg->AddEntry(N2200,"2.2 GeV","P");
  mg_N_L_leg->Draw("");  

  // chi2/ndf
  TCanvas *c6=new TCanvas("c6","c6",1200,800);

  TGraph *ndf1860=new TGraphErrors(161,range,chi2ndf1860,range_err,range_err);
  ndf1860->SetMarkerStyle(20);
  ndf1860->SetMarkerColor(1);
  ndf1860->SetLineColor(1);

  TGraph *ndf1600=new TGraphErrors(161,range,chi2ndf1600,range_err,range_err);
  ndf1600->SetMarkerStyle(20);
  ndf1600->SetMarkerColor(2);
  ndf1600->SetLineColor(2);

  TGraph *ndf1700=new TGraphErrors(161,range,chi2ndf1700,range_err,range_err);
  ndf1700->SetMarkerStyle(20);
  ndf1700->SetMarkerColor(3);
  ndf1700->SetLineColor(3);

  TGraph *ndf1800=new TGraphErrors(161,range,chi2ndf1800,range_err,range_err);
  ndf1800->SetMarkerStyle(20);
  ndf1800->SetMarkerColor(4);
  ndf1800->SetLineColor(4);

  TGraph *ndf1900=new TGraphErrors(161,range,chi2ndf1900,range_err,range_err);
  ndf1900->SetMarkerStyle(20);
  ndf1900->SetMarkerColor(5);
  ndf1900->SetLineColor(5);

  TGraph *ndf2000=new TGraphErrors(161,range,chi2ndf2000,range_err,range_err);
  ndf2000->SetMarkerStyle(20);
  ndf2000->SetMarkerColor(6);
  ndf2000->SetLineColor(6);

  TGraph *ndf2100=new TGraphErrors(161,range,chi2ndf2100,range_err,range_err);
  ndf2100->SetMarkerStyle(20);
  ndf2100->SetMarkerColor(7);
  ndf2100->SetLineColor(7);

  TGraph *ndf2200=new TGraphErrors(161,range,chi2ndf2200,range_err,range_err);
  ndf2200->SetMarkerStyle(20);
  ndf2200->SetMarkerColor(8);
  ndf2200->SetLineColor(8);

  TMultiGraph *mg_ndf=new TMultiGraph();
  mg_ndf->Add(ndf1860,"AP");
  mg_ndf->Add(ndf1600,"AP");
//  mg_ndf->Add(ndf1700,"AP");
//  mg_ndf->Add(ndf1800,"AP");
//  mg_ndf->Add(ndf1900,"AP");
//  mg_ndf->Add(ndf2000,"AP");
//  mg_ndf->Add(ndf2100,"AP");
  mg_ndf->Add(ndf2200,"AP");  
  mg_ndf->SetTitle("chi2/ndf vs fit range (start point 20);end point;N");
  mg_ndf->Draw("a");

  gStyle->SetLegendBorderSize(0);
  TLegend* mg_ndf_leg=new TLegend(0.7,0.2,0.85,0.4);
  mg_ndf_leg->AddEntry(ndf1860,"1.86GeV","P");
  mg_ndf_leg->AddEntry(ndf1600,"1.6 GeV","P");
//  mg_ndf_leg->AddEntry(ndf1700,"1.7 GeV","P");
//  mg_ndf_leg->AddEntry(ndf1800,"1.8 GeV","P");
//  mg_ndf_leg->AddEntry(ndf1900,"1.9 GeV","P");
//  mg_ndf_leg->AddEntry(ndf2000,"2.0 GeV","P");
//  mg_ndf_leg->AddEntry(ndf2100,"2.1 GeV","P");
  mg_ndf_leg->AddEntry(ndf2200,"2.2 GeV","P");
  mg_ndf_leg->Draw("");  


}
