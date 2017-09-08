void diff_start_point(){

  gStyle->SetOptFit(1111);
  gStyle->SetOptStat(10);

  double binWidth = 0.148936170213;
  int nRebin = 2;

  double threshold=1.86;

  double Ta_L1[161],Ta_C1[161],tau_L1[161],tau_C1[161],N_L1[161],N_C1[161],phi_L1[161],phi_C1[161],A_L1[161],A_C1[161];
  double Ta_L_err1[161],Ta_C_err1[161],tau_L_err1[161],tau_C_err1[161],N_L_err1[161],N_C_err1[161],phi_L_err1[161],phi_C_err1[161],A_L_err1[161],A_C_err1[161];
  double chi2ndf1[161];

  double Ta_L2[161],Ta_C2[161],tau_L2[161],tau_C2[161],N_L2[161],N_C2[161],phi_L2[161],phi_C2[161],A_L2[161],A_C2[161];
  double Ta_L_err2[161],Ta_C_err2[161],tau_L_err2[161],tau_C_err2[161],N_L_err2[161],N_C_err2[161],phi_L_err2[161],phi_C_err2[161],A_L_err2[161],A_C_err2[161];
  double chi2ndf2[161];

  double Ta_L3[161],Ta_C3[161],tau_L3[161],tau_C3[161],N_L3[161],N_C3[161],phi_L3[161],phi_C3[161],A_L3[161],A_C3[161];
  double Ta_L_err3[161],Ta_C_err3[161],tau_L_err3[161],tau_C_err3[161],N_L_err3[161],N_C_err3[161],phi_L_err3[161],phi_C_err3[161],A_L_err3[161],A_C_err3[161];
  double chi2ndf3[161];

  double range[161],range_err[161];
  for(int i=0;i<161;i++){
    range[i]=i+40;
    range_err[i]=0;
  }

  TH1D *hittime;
  hittime= new TH1D("Wiggle_plot_1.86GeV","T-Method wiggle plot with cut 1.86GeV",3000,0,binWidth*3000);    
  TFile *file= new TFile("../run/gm2_wiggle_fit_related_ana.1462.root");

  TH1D *allhits;
  allhits = (TH1D*)file->Get("WiggleFitAna/allCaloWiggle");

  for(unsigned int i=0;i<3000;i++){
    hittime->SetBinContent(i+1,allhits->GetBinContent(225+i));
  }  
  hittime->ResetStats();
  hittime->Rebin(nRebin);
  hittime->SetMarkerStyle(4);
  hittime->SetMarkerColor(4);
  hittime->SetLineColor(4);
  hittime->SetMarkerSize(0.5);
  //hittime->GetXaxis()->SetRangeUser(0,150);
  hittime->GetYaxis()->SetRangeUser(1,10000);
  hittime->GetXaxis()->SetTitle("time [#mus]");
  hittime->GetYaxis()->SetTitle(Form("count / %d*149 ns", nRebin));

  for(int l=0;l<161;l++){
    TF1 *fit = new TF1("fit", "[0]*exp(-x/[1])*(1+[2]*cos([3]+2*TMath::Pi()/[4]*x))", 10,l+40);
    fit->SetNpx(50000);
    fit->SetParNames("N","#gamma#tau_{#mu}","A","#phi","T_{a}(#mus)");
    fit->SetParameters(100,64.4,0.5,0,4.3);

      Ta_L1[l] = hittime->Fit("fit","SQREML")->Parameter(4);
      Ta_L_err1[l] = fit->GetParError(4);
      Ta_C1[l] = hittime->Fit("fit","SQREM")->Parameter(4);
      Ta_C_err1[l] = fit->GetParError(4);

      tau_L1[l] = hittime->Fit("fit","SQREML")->Parameter(1);
      tau_L_err1[l] = fit->GetParError(1);
      tau_C1[l] = hittime->Fit("fit","SQREM")->Parameter(1);
      tau_C_err1[l] = fit->GetParError(1);

      N_L1[l] = hittime->Fit("fit","SQREML")->Parameter(0);
      N_L_err1[l] = fit->GetParError(0);
      N_C1[l] = hittime->Fit("fit","SQREM")->Parameter(0);
      N_C_err1[l] = fit->GetParError(0);

      phi_L1[l] = hittime->Fit("fit","SQREML")->Parameter(3);
      phi_L_err1[l] = fit->GetParError(3);
      phi_C1[l] = hittime->Fit("fit","SQREM")->Parameter(3);
      phi_C_err1[l] = fit->GetParError(3);  
   
      A_L1[l] = hittime->Fit("fit","SQREML")->Parameter(2);
      A_L_err1[l] = fit->GetParError(2);
      A_C1[l] = hittime->Fit("fit","SQREM")->Parameter(2);
      A_C_err1[l] = fit->GetParError(2); 

      chi2ndf1[l] = ( hittime->Fit("fit","SQREM")->Chi2() ) / ( hittime->Fit("fit","SQREM")->Ndf() );
  }   

  for(int l=0;l<161;l++){
    TF1 *fit = new TF1("fit", "[0]*exp(-x/[1])*(1+[2]*cos([3]+2*TMath::Pi()/[4]*x))", 20,l+40);
    fit->SetNpx(50000);
    fit->SetParNames("N","#gamma#tau_{#mu}","A","#phi","T_{a}(#mus)");
    fit->SetParameters(100,64.4,0.5,0,4.3);

      Ta_L2[l] = hittime->Fit("fit","SQREML")->Parameter(4);
      Ta_L_err2[l] = fit->GetParError(4);
      Ta_C2[l] = hittime->Fit("fit","SQREM")->Parameter(4);
      Ta_C_err2[l] = fit->GetParError(4);

      tau_L2[l] = hittime->Fit("fit","SQREML")->Parameter(1);
      tau_L_err2[l] = fit->GetParError(1);
      tau_C2[l] = hittime->Fit("fit","SQREM")->Parameter(1);
      tau_C_err2[l] = fit->GetParError(1);

      N_L2[l] = hittime->Fit("fit","SQREML")->Parameter(0);
      N_L_err2[l] = fit->GetParError(0);
      N_C2[l] = hittime->Fit("fit","SQREM")->Parameter(0);
      N_C_err2[l] = fit->GetParError(0);

      phi_L2[l] = hittime->Fit("fit","SQREML")->Parameter(3);
      phi_L_err2[l] = fit->GetParError(3);
      phi_C2[l] = hittime->Fit("fit","SQREM")->Parameter(3);
      phi_C_err2[l] = fit->GetParError(3);  
   
      A_L2[l] = hittime->Fit("fit","SQREML")->Parameter(2);
      A_L_err2[l] = fit->GetParError(2);
      A_C2[l] = hittime->Fit("fit","SQREM")->Parameter(2);
      A_C_err2[l] = fit->GetParError(2); 

      chi2ndf2[l] = ( hittime->Fit("fit","SQREM")->Chi2() ) / ( hittime->Fit("fit","SQREM")->Ndf() );
  }  

  for(int l=0;l<161;l++){
    TF1 *fit = new TF1("fit", "[0]*exp(-x/[1])*(1+[2]*cos([3]+2*TMath::Pi()/[4]*x))", 25,l+40);
    fit->SetNpx(50000);
    fit->SetParNames("N","#gamma#tau_{#mu}","A","#phi","T_{a}(#mus)");
    fit->SetParameters(100,64.4,0.5,0,4.3);

      Ta_L3[l] = hittime->Fit("fit","SQREML")->Parameter(4);
      Ta_L_err3[l] = fit->GetParError(4);
      Ta_C3[l] = hittime->Fit("fit","SQREM")->Parameter(4);
      Ta_C_err3[l] = fit->GetParError(4);

      tau_L3[l] = hittime->Fit("fit","SQREML")->Parameter(1);
      tau_L_err3[l] = fit->GetParError(1);
      tau_C3[l] = hittime->Fit("fit","SQREM")->Parameter(1);
      tau_C_err3[l] = fit->GetParError(1);

      N_L3[l] = hittime->Fit("fit","SQREML")->Parameter(0);
      N_L_err3[l] = fit->GetParError(0);
      N_C3[l] = hittime->Fit("fit","SQREM")->Parameter(0);
      N_C_err3[l] = fit->GetParError(0);

      phi_L3[l] = hittime->Fit("fit","SQREML")->Parameter(3);
      phi_L_err3[l] = fit->GetParError(3);
      phi_C3[l] = hittime->Fit("fit","SQREM")->Parameter(3);
      phi_C_err3[l] = fit->GetParError(3);  
   
      A_L3[l] = hittime->Fit("fit","SQREML")->Parameter(2);
      A_L_err3[l] = fit->GetParError(2);
      A_C3[l] = hittime->Fit("fit","SQREM")->Parameter(2);
      A_C_err3[l] = fit->GetParError(2); 

      chi2ndf3[l] = ( hittime->Fit("fit","SQREM")->Chi2() ) / ( hittime->Fit("fit","SQREM")->Ndf() );
  } 
///////////////////////////////////////////////////////
  TCanvas *c1=new TCanvas("c1","c1",1200,800);

  TGraph *TaL1=new TGraphErrors(161,range,Ta_L1,range_err,Ta_L_err1);
  TaL1->SetMarkerStyle(20);
  TaL1->SetMarkerColor(1);
  TaL1->SetLineColor(1);

  TGraph *TaL2=new TGraphErrors(161,range,Ta_L2,range_err,Ta_L_err2);
  TaL2->SetMarkerStyle(20);
  TaL2->SetMarkerColor(2);
  TaL2->SetLineColor(2);

  TGraph *TaL3=new TGraphErrors(161,range,Ta_L3,range_err,Ta_L_err3);
  TaL3->SetMarkerStyle(20);
  TaL3->SetMarkerColor(3);
  TaL3->SetLineColor(3);

  TMultiGraph *mg_Ta_L=new TMultiGraph();
  mg_Ta_L->Add(TaL1,"AP");
  mg_Ta_L->Add(TaL2,"AP");
  mg_Ta_L->Add(TaL3,"AP");
  mg_Ta_L->SetTitle("T_{a} vs fit range;end point;T_{a}");
  mg_Ta_L->Draw("a");

  gStyle->SetLegendBorderSize(0);
  TLegend* mg_Ta_L_leg=new TLegend(0.7,0.2,0.85,0.4);
  mg_Ta_L_leg->AddEntry(TaL1,"start point 10","P");
  mg_Ta_L_leg->AddEntry(TaL2,"start point 20","P");
  mg_Ta_L_leg->AddEntry(TaL3,"start point 25","P");
  mg_Ta_L_leg->Draw(""); 

  gPad->Modified();
  mg_Ta_L->SetMinimum(4.3);
  mg_Ta_L->SetMaximum(4.4);
///////////////////////////////////////////////////////
  TCanvas *c2=new TCanvas("c2","c2",1200,800);

  TGraph *tau1=new TGraphErrors(161,range,tau_L1,range_err,tau_L_err1);
  tau1->SetMarkerStyle(20);
  tau1->SetMarkerColor(1);
  tau1->SetLineColor(1);

  TGraph *tau2=new TGraphErrors(161,range,tau_L2,range_err,tau_L_err2);
  tau2->SetMarkerStyle(20);
  tau2->SetMarkerColor(2);
  tau2->SetLineColor(2);
    
  TGraph *tau3=new TGraphErrors(161,range,tau_L3,range_err,tau_L_err3);
  tau3->SetMarkerStyle(20);
  tau3->SetMarkerColor(3);
  tau3->SetLineColor(3);

  TMultiGraph *mg_tau_L=new TMultiGraph();
  mg_tau_L->Add(tau1,"AP");
  mg_tau_L->Add(tau2,"AP");
  mg_tau_L->Add(tau3,"AP");
  mg_tau_L->SetTitle("#gamma#tau_{#mu} vs fit range;end point;#gamma#tau_{#mu}");
  mg_tau_L->Draw("a");

  gStyle->SetLegendBorderSize(0);
  TLegend* mg_tau_L_leg=new TLegend(0.7,0.6,0.85,0.8);
  mg_tau_L_leg->AddEntry(tau1,"start point 10","P");
  mg_tau_L_leg->AddEntry(tau2,"start point 20","P");
  mg_tau_L_leg->AddEntry(tau3,"start point 25","P");
  mg_tau_L_leg->Draw(""); 
///////////////////////////////////////////////////////////
  TCanvas *c3=new TCanvas("c3","c3",1200,800);

  TGraph *A1=new TGraphErrors(161,range,A_L1,range_err,A_L_err1);
  A1->SetMarkerStyle(20);
  A1->SetMarkerColor(1);
  A1->SetLineColor(1);

  TGraph *A2=new TGraphErrors(161,range,A_L2,range_err,A_L_err2);
  A2->SetMarkerStyle(20);
  A2->SetMarkerColor(2);
  A2->SetLineColor(2);
    
  TGraph *A3=new TGraphErrors(161,range,A_L3,range_err,A_L_err3);
  A3->SetMarkerStyle(20);
  A3->SetMarkerColor(3);
  A3->SetLineColor(3);

  TMultiGraph *mg_A_L=new TMultiGraph();
  mg_A_L->Add(A1,"AP");
  mg_A_L->Add(A2,"AP");
  mg_A_L->Add(A3,"AP");
  mg_A_L->SetTitle("A vs fit range;end point;A");
  mg_A_L->Draw("a");

  gStyle->SetLegendBorderSize(0);
  TLegend* mg_A_L_leg=new TLegend(0.7,0.6,0.85,0.8);
  mg_A_L_leg->AddEntry(A1,"start point 10","P");
  mg_A_L_leg->AddEntry(A2,"start point 20","P");
  mg_A_L_leg->AddEntry(A3,"start point 25","P");
  mg_A_L_leg->Draw(""); 
///////////////////////////////////////////////////////////////
  TCanvas *c4=new TCanvas("c4","c4",1200,800);

  TGraph *phi1=new TGraphErrors(161,range,phi_L1,range_err,phi_L_err1);
  phi1->SetMarkerStyle(20);
  phi1->SetMarkerColor(1);
  phi1->SetLineColor(1);

  TGraph *phi2=new TGraphErrors(161,range,phi_L2,range_err,phi_L_err2);
  phi2->SetMarkerStyle(20);
  phi2->SetMarkerColor(2);
  phi2->SetLineColor(2);
    
  TGraph *phi3=new TGraphErrors(161,range,phi_L3,range_err,phi_L_err3);
  phi3->SetMarkerStyle(20);
  phi3->SetMarkerColor(3);
  phi3->SetLineColor(3);

  TMultiGraph *mg_phi_L=new TMultiGraph();
  mg_phi_L->Add(phi1,"AP");
  mg_phi_L->Add(phi2,"AP");
  mg_phi_L->Add(phi3,"AP");
  mg_phi_L->SetTitle("#phi vs fit range;end point;#phi");
  mg_phi_L->Draw("a");

  gStyle->SetLegendBorderSize(0);
  TLegend* mg_phi_L_leg=new TLegend(0.7,0.6,0.85,0.8);
  mg_phi_L_leg->AddEntry(phi1,"start point 10","P");
  mg_phi_L_leg->AddEntry(phi2,"start point 20","P");
  mg_phi_L_leg->AddEntry(phi3,"start point 25","P");
  mg_phi_L_leg->Draw(""); 
//////////////////////////////////////////////////////////
  TCanvas *c5=new TCanvas("c5","c5",1200,800);

  TGraph *N1=new TGraphErrors(161,range,N_L1,range_err,N_L_err1);
  N1->SetMarkerStyle(20);
  N1->SetMarkerColor(1);
  N1->SetLineColor(1);

  TGraph *N2=new TGraphErrors(161,range,N_L2,range_err,N_L_err2);
  N2->SetMarkerStyle(20);
  N2->SetMarkerColor(2);
  N2->SetLineColor(2);
    
  TGraph *N3=new TGraphErrors(161,range,N_L3,range_err,N_L_err3);
  N3->SetMarkerStyle(20);
  N3->SetMarkerColor(3);
  N3->SetLineColor(3);

  TMultiGraph *mg_N_L=new TMultiGraph();
  mg_N_L->Add(N1,"AP");
  mg_N_L->Add(N2,"AP");
  mg_N_L->Add(N3,"AP");
  mg_N_L->SetTitle("N vs fit range;end point;N");
  mg_N_L->Draw("a");

  gStyle->SetLegendBorderSize(0);
  TLegend* mg_N_L_leg=new TLegend(0.7,0.6,0.85,0.8);
  mg_N_L_leg->AddEntry(N1,"start point 10","P");
  mg_N_L_leg->AddEntry(N2,"start point 20","P");
  mg_N_L_leg->AddEntry(N3,"start point 25","P");
  mg_N_L_leg->Draw(""); 
///////////////////////////////////////////////////////////
  TCanvas *c6=new TCanvas("c6","c6",1200,800);

  TGraph *ndf1=new TGraphErrors(161,range,chi2ndf1,range_err,range_err);
  ndf1->SetMarkerStyle(20);
  ndf1->SetMarkerColor(1);
  ndf1->SetLineColor(1);

  TGraph *ndf2=new TGraphErrors(161,range,chi2ndf2,range_err,range_err);
  ndf2->SetMarkerStyle(20);
  ndf2->SetMarkerColor(2);
  ndf2->SetLineColor(2);
    
  TGraph *ndf3=new TGraphErrors(161,range,chi2ndf3,range_err,range_err);
  ndf3->SetMarkerStyle(20);
  ndf3->SetMarkerColor(3);
  ndf3->SetLineColor(3);

  TMultiGraph *mg_ndf_L=new TMultiGraph();
  mg_ndf_L->Add(ndf1,"AP");
  mg_ndf_L->Add(ndf2,"AP");
  mg_ndf_L->Add(ndf3,"AP");
  mg_ndf_L->SetTitle("chi2/ndf vs fit range;end point;chi2/ndf");
  mg_ndf_L->Draw("a");

  gStyle->SetLegendBorderSize(0);
  TLegend* mg_ndf_L_leg=new TLegend(0.7,0.6,0.85,0.8);
  mg_ndf_L_leg->AddEntry(ndf1,"start point 10","P");
  mg_ndf_L_leg->AddEntry(ndf2,"start point 20","P");
  mg_ndf_L_leg->AddEntry(ndf3,"start point 25","P");
  mg_ndf_L_leg->Draw(""); 

}
    
