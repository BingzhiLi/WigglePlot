void energy_slice_Fit(){

  TFile *f=new TFile("energy_slice_parameter.root");
  TTree *fit_parameter = (TTree*)f->Get("fit_parameter");

  double Ta_L[3],Ta_C[3],tau_L[3],tau_C[3],N_L[3],N_C[3],phi_L[3],phi_C[3],A_L[3],A_C[3];
  double Ta_L_err[3],Ta_C_err[3],tau_L_err[3],tau_C_err[3],N_L_err[3],N_C_err[3],phi_L_err[3],phi_C_err[3],A_L_err[3],A_C_err[3]; 
  double chi2ndf[3]; 

  double range[161],range_err[161];
  for(int i=0;i<161;i++){
    range[i]=i+40;
    range_err[i]=0;
  }
   
  double Ta_L_1619[161],Ta_L_1922[161],Ta_L_2231[161];
  double Ta_C_1619[161],Ta_C_1922[161],Ta_C_2231[161];
  double tau_L_1619[161],tau_L_1922[161],tau_L_2231[161];
  double tau_C_1619[161],tau_C_1922[161],tau_C_2231[161];
  double N_L_1619[161],N_L_1922[161],N_L_2231[161];
  double N_C_1619[161],N_C_1922[161],N_C_2231[161];
  double phi_L_1619[161],phi_L_1922[161],phi_L_2231[161];
  double phi_C_1619[161],phi_C_1922[161],phi_C_2231[161];
  double A_L_1619[161],A_L_1922[161],A_L_2231[161];
  double A_C_1619[161],A_C_1922[161],A_C_2231[161];

  double Ta_L_1619_err[161],Ta_L_1922_err[161],Ta_L_2231_err[161];
  double Ta_C_1619_err[161],Ta_C_1922_err[161],Ta_C_2231_err[161];
  double tau_L_1619_err[161],tau_L_1922_err[161],tau_L_2231_err[161];
  double tau_C_1619_err[161],tau_C_1922_err[161],tau_C_2231_err[161];
  double N_L_1619_err[161],N_L_1922_err[161],N_L_2231_err[161];
  double N_C_1619_err[161],N_C_1922_err[161],N_C_2231_err[161];
  double phi_L_1619_err[161],phi_L_1922_err[161],phi_L_2231_err[161];
  double phi_C_1619_err[161],phi_C_1922_err[161],phi_C_2231_err[161];
  double A_L_1619_err[161],A_L_1922_err[161],A_L_2231_err[161];
  double A_C_1619_err[161],A_C_1922_err[161],A_C_2231_err[161];

  double chi2ndf1619[161],chi2ndf1922[161],chi2ndf2231[161];

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
    for (int j=0;j<3;j++){
      if(j==0){
        Ta_L_1619[i]=Ta_L[j];
        Ta_C_1619[i]=Ta_C[j];
        tau_L_1619[i]=tau_L[j];
        tau_C_1619[i]=tau_C[j];
        N_L_1619[i]=N_L[j];
        N_C_1619[i]=N_C[j];
        phi_L_1619[i]=phi_L[j];
        phi_C_1619[i]=phi_C[j];
        A_L_1619[i]=A_L[j];
        A_C_1619[i]=A_C[j];

        Ta_L_1619_err[i]=Ta_L_err[j];
        Ta_C_1619_err[i]=Ta_C_err[j];
        tau_L_1619_err[i]=tau_L_err[j];
        tau_C_1619_err[i]=tau_C_err[j];
        N_L_1619_err[i]=N_L_err[j];
        N_C_1619_err[i]=N_C_err[j];
        phi_L_1619_err[i]=phi_L_err[j];
        phi_C_1619_err[i]=phi_C_err[j];
        A_L_1619_err[i]=A_L_err[j];
        A_C_1619_err[i]=A_C_err[j];
     
        chi2ndf1619[i]=chi2ndf[j];
      }

      if(j==1){
        Ta_L_1922[i]=Ta_L[j];
        Ta_C_1922[i]=Ta_C[j];
        tau_L_1922[i]=tau_L[j];
        tau_C_1922[i]=tau_C[j];
        N_L_1922[i]=N_L[j];
        N_C_1922[i]=N_C[j];
        phi_L_1922[i]=phi_L[j];
        phi_C_1922[i]=phi_C[j];
        A_L_1922[i]=A_L[j];
        A_C_1922[i]=A_C[j];

        Ta_L_1922_err[i]=Ta_L_err[j];
        Ta_C_1922_err[i]=Ta_C_err[j];
        tau_L_1922_err[i]=tau_L_err[j];
        tau_C_1922_err[i]=tau_C_err[j];
        N_L_1922_err[i]=N_L_err[j];
        N_C_1922_err[i]=N_C_err[j];
        phi_L_1922_err[i]=phi_L_err[j];
        phi_C_1922_err[i]=phi_C_err[j];
        A_L_1922_err[i]=A_L_err[j];
        A_C_1922_err[i]=A_C_err[j]; 

        chi2ndf1922[i]=chi2ndf[j];       
      }

      if(j==2){
        Ta_L_2231[i]=Ta_L[j];
        Ta_C_2231[i]=Ta_C[j];
        tau_L_2231[i]=tau_L[j];
        tau_C_2231[i]=tau_C[j];
        N_L_2231[i]=N_L[j];
        N_C_2231[i]=N_C[j];
        phi_L_2231[i]=phi_L[j];
        phi_C_2231[i]=phi_C[j];
        A_L_2231[i]=A_L[j];
        A_C_2231[i]=A_C[j];

        Ta_L_2231_err[i]=Ta_L_err[j];
        Ta_C_2231_err[i]=Ta_C_err[j];
        tau_L_2231_err[i]=tau_L_err[j];
        tau_C_2231_err[i]=tau_C_err[j];
        N_L_2231_err[i]=N_L_err[j];
        N_C_2231_err[i]=N_C_err[j];
        phi_L_2231_err[i]=phi_L_err[j];
        phi_C_2231_err[i]=phi_C_err[j];
        A_L_2231_err[i]=A_L_err[j];
        A_C_2231_err[i]=A_C_err[j];

        chi2ndf2231[i]=chi2ndf[j];
      }

    }
  
  }

  //likelihood: Ta vs fit range
  TCanvas *c1=new TCanvas("c1","c1",1200,800);

  TGraph *TaL1619=new TGraphErrors(161,range,Ta_L_1619,range_err,Ta_L_1619_err);
  TaL1619->SetMarkerStyle(20);
  TaL1619->SetMarkerColor(1);
  TaL1619->SetLineColor(1);

  TGraph *TaL1922=new TGraphErrors(161,range,Ta_L_1922,range_err,Ta_L_1922_err);
  TaL1922->SetMarkerStyle(20);
  TaL1922->SetMarkerColor(2);
  TaL1922->SetLineColor(2);

  TGraph *TaL2231=new TGraphErrors(161,range,Ta_L_2231,range_err,Ta_L_2231_err);
  TaL2231->SetMarkerStyle(20);
  TaL2231->SetMarkerColor(3);
  TaL2231->SetLineColor(3);

  TMultiGraph *mg_Ta_L=new TMultiGraph();
  mg_Ta_L->Add(TaL1619,"AP");
  mg_Ta_L->Add(TaL1922,"AP");
  mg_Ta_L->Add(TaL2231,"AP");
  mg_Ta_L->SetTitle("T_{a} vs fit range (likelihood: start point 20);end point;T_{a}");
  mg_Ta_L->Draw("a");

  gStyle->SetLegendBorderSize(0);
  TLegend* mg_Ta_L_leg=new TLegend(0.7,0.2,0.85,0.4);
  mg_Ta_L_leg->AddEntry(TaL1619,"1.6-1.9 GeV","P");
  mg_Ta_L_leg->AddEntry(TaL1922,"1.9-2.2 GeV","P");
  mg_Ta_L_leg->AddEntry(TaL2231,">2.2 GeV","P");
  mg_Ta_L_leg->Draw("");  

  gPad->Modified();
  mg_Ta_L->SetMinimum(4.3);
  mg_Ta_L->SetMaximum(4.4);  

  //likelihood: gamma_tau vs fit range
  TCanvas *c2=new TCanvas("c2","c2",1200,800);

  TGraph *tau1619=new TGraphErrors(161,range,tau_L_1619,range_err,tau_L_1619_err);
  tau1619->SetMarkerStyle(20);
  tau1619->SetMarkerColor(1);
  tau1619->SetLineColor(1);

  TGraph *tau1922=new TGraphErrors(161,range,tau_L_1922,range_err,tau_L_1922_err);
  tau1922->SetMarkerStyle(20);
  tau1922->SetMarkerColor(2);
  tau1922->SetLineColor(2);

  TGraph *tau2231=new TGraphErrors(161,range,tau_L_2231,range_err,tau_L_2231_err);
  tau2231->SetMarkerStyle(20);
  tau2231->SetMarkerColor(3);
  tau2231->SetLineColor(3);

  TMultiGraph *mg_tau_L=new TMultiGraph();
  mg_tau_L->Add(tau1619,"AP");
  mg_tau_L->Add(tau1922,"AP");
  mg_tau_L->Add(tau2231,"AP");
  mg_tau_L->SetTitle("#gamma#tau_{#mu} vs fit range (likelihood: start point 20);end point;#gamma#tau_{#mu}");
  mg_tau_L->Draw("a");

  gStyle->SetLegendBorderSize(0);
  TLegend* mg_tau_L_leg=new TLegend(0.7,0.6,0.85,0.8);
  mg_tau_L_leg->AddEntry(tau1619,"1.6-1.9 GeV","P");
  mg_tau_L_leg->AddEntry(tau1922,"1.9-2.2 GeV","P");
  mg_tau_L_leg->AddEntry(tau2231,">2.2 GeV","P");
  mg_tau_L_leg->Draw(""); 

  gPad->Modified();
  mg_tau_L->SetMinimum(50);
  mg_tau_L->SetMaximum(130);

  //likelihood: A vs fit range
  TCanvas *c3=new TCanvas("c3","c3",1200,800);

  TGraph *A1619=new TGraphErrors(161,range,A_L_1619,range_err,A_L_1619_err);
  A1619->SetMarkerStyle(20);
  A1619->SetMarkerColor(1);
  A1619->SetLineColor(1);

  TGraph *A1922=new TGraphErrors(161,range,A_L_1922,range_err,A_L_1922_err);
  A1922->SetMarkerStyle(20);
  A1922->SetMarkerColor(2);
  A1922->SetLineColor(2);

  TGraph *A2231=new TGraphErrors(161,range,A_L_2231,range_err,A_L_2231_err);
  A2231->SetMarkerStyle(20);
  A2231->SetMarkerColor(3);
  A2231->SetLineColor(3);

  TMultiGraph *mg_A_L=new TMultiGraph();
  mg_A_L->Add(A1619,"AP");
  mg_A_L->Add(A1922,"AP");
  mg_A_L->Add(A2231,"AP"); 
  mg_A_L->SetTitle("A vs fit range (likelihood: start point 20);end point;A");
  mg_A_L->Draw("a");

  gStyle->SetLegendBorderSize(0);
  TLegend* mg_A_L_leg=new TLegend(0.7,0.2,0.85,0.4);
  mg_A_L_leg->AddEntry(A1619,"1.6-1.9GeV","P");
  mg_A_L_leg->AddEntry(A1922,"1.9-2.2 GeV","P");
  mg_A_L_leg->AddEntry(A2231,">2.2 GeV","P");
  mg_A_L_leg->Draw("");  

  gPad->Modified();
  mg_A_L->SetMinimum(0);
  mg_A_L->SetMaximum(1);

  //likelihood: phi vs fit range
  TCanvas *c4=new TCanvas("c4","c4",1200,800);

  TGraph *phi1619=new TGraphErrors(161,range,phi_L_1619,range_err,phi_L_1619_err);
  phi1619->SetMarkerStyle(20);
  phi1619->SetMarkerColor(1);
  phi1619->SetLineColor(1);

  TGraph *phi1922=new TGraphErrors(161,range,phi_L_1922,range_err,phi_L_1922_err);
  phi1922->SetMarkerStyle(20);
  phi1922->SetMarkerColor(2);
  phi1922->SetLineColor(2);

  TGraph *phi2231=new TGraphErrors(161,range,phi_L_2231,range_err,phi_L_2231_err);
  phi2231->SetMarkerStyle(20);
  phi2231->SetMarkerColor(3);
  phi2231->SetLineColor(3);

  TMultiGraph *mg_phi_L=new TMultiGraph();
  mg_phi_L->Add(phi1619,"AP");
  mg_phi_L->Add(phi1922,"AP");
  mg_phi_L->Add(phi2231,"AP");
  mg_phi_L->SetTitle("phi vs fit range (likelihood: start point 20);end point;phi");
  mg_phi_L->Draw("a");

  gStyle->SetLegendBorderSize(0);
  TLegend* mg_phi_L_leg=new TLegend(0.7,0.2,0.85,0.4);
  mg_phi_L_leg->AddEntry(phi1619,"1.6-1.9 GeV","P");
  mg_phi_L_leg->AddEntry(phi1922,"1.9-2.2 GeV","P");
  mg_phi_L_leg->AddEntry(phi2231,">2.2 GeV","P");
  mg_phi_L_leg->Draw("");  

  gPad->Modified();
  mg_phi_L->SetMinimum(-10);
  mg_phi_L->SetMaximum(10);

  //likelihood: N vs fit range
  TCanvas *c5=new TCanvas("c5","c5",1200,800);

  TGraph *N1619=new TGraphErrors(161,range,N_L_1619,range_err,N_L_1619_err);
  N1619->SetMarkerStyle(20);
  N1619->SetMarkerColor(1);
  N1619->SetLineColor(1);

  TGraph *N1922=new TGraphErrors(161,range,N_L_1922,range_err,N_L_1922_err);
  N1922->SetMarkerStyle(20);
  N1922->SetMarkerColor(2);
  N1922->SetLineColor(2);

  TGraph *N2231=new TGraphErrors(161,range,N_L_2231,range_err,N_L_2231_err);
  N2231->SetMarkerStyle(20);
  N2231->SetMarkerColor(3);
  N2231->SetLineColor(3);

  TMultiGraph *mg_N_L=new TMultiGraph();
  mg_N_L->Add(N1619,"AP");
  mg_N_L->Add(N1922,"AP");
  mg_N_L->Add(N2231,"AP");
  mg_N_L->SetTitle("N vs fit range (likelihood: start point 20);end point;N");
  mg_N_L->Draw("a");

  gStyle->SetLegendBorderSize(0);
  TLegend* mg_N_L_leg=new TLegend(0.7,0.2,0.85,0.4);
  mg_N_L_leg->AddEntry(N1619,"1.6-1.9 GeV","P");
  mg_N_L_leg->AddEntry(N1922,"1.9-2.2 GeV","P");
  mg_N_L_leg->AddEntry(N2231,">2.2 GeV","P");
  mg_N_L_leg->Draw("");  

  // chi2/ndf
  TCanvas *c6=new TCanvas("c6","c6",1200,800);

  TGraph *ndf1619=new TGraphErrors(161,range,chi2ndf1619,range_err,range_err);
  ndf1619->SetMarkerStyle(20);
  ndf1619->SetMarkerColor(1);
  ndf1619->SetLineColor(1);

  TGraph *ndf1922=new TGraphErrors(161,range,chi2ndf1922,range_err,range_err);
  ndf1922->SetMarkerStyle(20);
  ndf1922->SetMarkerColor(2);
  ndf1922->SetLineColor(2);

  TGraph *ndf2231=new TGraphErrors(161,range,chi2ndf2231,range_err,range_err);
  ndf2231->SetMarkerStyle(20);
  ndf2231->SetMarkerColor(3);
  ndf2231->SetLineColor(3);

  TMultiGraph *mg_ndf=new TMultiGraph();
  mg_ndf->Add(ndf1619,"AP");
  mg_ndf->Add(ndf1922,"AP");
  mg_ndf->Add(ndf2231,"AP"); 
  mg_ndf->SetTitle("chi2/ndf vs fit range (start point 20);end point;N");
  mg_ndf->Draw("a");

  gStyle->SetLegendBorderSize(0);
  TLegend* mg_ndf_leg=new TLegend(0.7,0.2,0.85,0.4);
  mg_ndf_leg->AddEntry(ndf1619,"1.6-1.9 GeV","P");
  mg_ndf_leg->AddEntry(ndf1922,"1.9-2.2 GeV","P");
  mg_ndf_leg->AddEntry(ndf2231,">2.2 GeV","P");
  mg_ndf_leg->Draw("");  


}
