void fitWiggle(){



  gStyle->SetOptFit(1111);
  gStyle->SetOptStat(10);
  TCanvas *c = new TCanvas("c","c",1200,800);

  double binWidth = 0.148936170213;
  int nRebin = 2;

  TH1D *hittime = new TH1D("hittime","hittime",3000,0,binWidth*3000);
//  TFile *file= new TFile("../run/gm2_wiggle_fit_related_ana.1874.root");
//  TFile *file= new TFile("../run/gm2_wiggle_fit_related_ana.1912.root");
  TFile *file= new TFile("../run/gm2_wiggle_fit_related_ana.1462.root");
//  TFile *file= new TFile("../run/1462.1912.root");
//  TFile *file= new TFile("../run/gm2_wiggle_fit_related_ana.total.root");
  TH1D *allhits = (TH1D*)file->Get("WiggleFitAna/allCaloWiggle");
  TFile *f=new TFile("allCaloWiggle.root","create");
  
  // offset to bin 255 (right after the first splash)
  // convert from clock tick to ns histogram
  for(unsigned int i=0;i<3000;i++){
    hittime->SetBinContent(i+1,allhits->GetBinContent(225+i));
  }
  hittime->ResetStats();
  hittime->SetTitle("T-method_wiggle_plot_Likelihood_fit");
  hittime->SetName("T-method Wiggle plot");
  hittime->Rebin(nRebin);
  hittime->SetMarkerStyle(4);
  hittime->SetMarkerColor(4);
  hittime->SetLineColor(4);
  hittime->SetMarkerSize(0.5);
  //hittime->GetXaxis()->SetRangeUser(0,150);
  hittime->GetYaxis()->SetRangeUser(1,10000);
  hittime->GetXaxis()->SetTitle("time [#mus]");
  hittime->GetYaxis()->SetTitle(Form("count / %d*149 ns", nRebin));
  hittime->Draw("E");
  hittime->Write(); 

  gPad->Update();
  TPaveStats *st = (TPaveStats*)hittime->FindObject("stats");
  st->SetX1NDC(0.55); //new x start position
  st->SetX2NDC(0.89); //new x end position
  st->SetY1NDC(0.55); //new x start position
  st->SetY2NDC(0.89); //new x end position

  c->SetLogy();

  double noerror[161]={0};

  double gamma_tau_L[161];
  double gamma_tau_L_error[161];
  double T_a_L[161];
  double T_a_L_error[161];
  double A_L[161];
  double A_L_error[161];
  double phi_L[161];
  double phi_L_error[161];
  double N_L[161];
  double N_L_error[161];
  double gamma_tau_C[161];
  double gamma_tau_C_error[161];
  double T_a_C[161];
  double T_a_C_error[161];
  double A_C[161];
  double A_C_error[161];
  double phi_C[161];
  double phi_C_error[161];
  double N_C[161];
  double N_C_error[161];
  double range[161];

  for(int i=0;i<161;i++){
    
    range[i]=i+40;
    TF1 *fit = new TF1("fit", "[0]*exp(-x/[1])*(1+[2]*cos([3]+2*TMath::Pi()/[4]*x))", 20,i+40);
    fit->SetNpx(50000);
    fit->SetParNames("N","#gamma#tau_{#mu}","A","#phi","T_{a}(#mus)");
    fit->SetParameters(100,64.4,0.5,0,4.3);
     
    //likelihood
    cout<<"likelihood"<<endl;
    //get likelihood gamma_tau
    gamma_tau_L[i] = hittime->Fit("fit","SQREML")->Parameter(1);
    gamma_tau_L_error[i] = fit->GetParError(1);
    cout<<i<<"    "<<gamma_tau_L[i]<<"    "<< gamma_tau_L_error[i]<<endl;
    //get likelihood Ta
    T_a_L[i] = hittime->Fit("fit","SQREML")->Parameter(4);
    T_a_L_error[i] = fit->GetParError(4);
    cout<<i<<"    "<<T_a_L[i]<<"    "<<T_a_L_error[i]<<endl;
    //get likelihood A
    A_L[i] = hittime->Fit("fit","SQREML")->Parameter(2);
    A_L_error[i] = fit->GetParError(2);
    cout<<i<<"    "<<A_L[i]<<"    "<<A_L_error[i]<<endl;
    //get likelihood phi
    phi_L[i] = hittime->Fit("fit","SQREML")->Parameter(3);
    phi_L_error[i] = fit->GetParError(3);
    cout<<i<<"    "<<phi_L[i]<<"    "<<phi_L_error[i]<<endl;
    //get likelihood N
    N_L[i] = hittime->Fit("fit","SQREML")->Parameter(0);
    N_L_error[i] = fit->GetParError(0);
    cout<<i<<"    "<<N_L[i]<<"    "<<N_L_error[i]<<endl;
    //chi2
    cout<<"chi2"<<endl;
    //get chi2 gamma_tau
    gamma_tau_C[i] = hittime->Fit("fit","SQREM")->Parameter(1);
    gamma_tau_C_error[i] = fit->GetParError(1);
    cout<<i<<"    "<<gamma_tau_C[i]<<"    "<< gamma_tau_C_error[i]<<endl;
    //get chi2 Ta
    T_a_C[i] = hittime->Fit("fit","SQREM")->Parameter(4);
    T_a_C_error[i] = fit->GetParError(4);
    cout<<i<<"    "<<T_a_C[i]<<"    "<<T_a_C_error[i]<<endl;
    //get chi2 A
    A_C[i] = hittime->Fit("fit","SQREM")->Parameter(2);
    A_C_error[i] = fit->GetParError(2);
    cout<<i<<"    "<<A_C[i]<<"    "<<A_C_error[i]<<endl;
    //get chi2 phi
    phi_C[i] = hittime->Fit("fit","SQREM")->Parameter(3);
    phi_C_error[i] = fit->GetParError(3);
    cout<<i<<"    "<<phi_C[i]<<"    "<<phi_C_error[i]<<endl;
    //get chi2 N
    N_C[i] = hittime->Fit("fit","SQREM")->Parameter(0);
    N_C_error[i] = fit->GetParError(0);
    cout<<i<<"    "<<N_C[i]<<"    "<<N_C_error[i]<<endl;

    cout<<endl;
   
  }

  //gamma tau vs range likelihood
  TGraph *g1=new TGraphErrors(161,range,gamma_tau_L,noerror,gamma_tau_L_error);
  g1->SetName("gamma_tau_vs_fit_range_likelihood");
  TCanvas *cc1=new TCanvas("cc1","cc1",1200,800);
  g1->SetTitle("stability of #gamma#tau_{#mu} vs fit range (likelihood: start point 20)");
  g1->GetXaxis()->SetTitle("end point");
  g1->GetYaxis()->SetTitle("#gamma#tau_{#mu}");
  g1->SetMarkerStyle(20);
  g1->SetMarkerColor(4);
  g1->Draw("AP"); 
  g1->Write();

  //T vs range likelihood
  TGraph *g2=new TGraphErrors(161,range,T_a_L,noerror,T_a_L_error);
  g2->SetName("Ta_vs_fit_range_likelihood");
  TCanvas *cc2=new TCanvas("cc2","cc2",1200,800);
  g2->SetTitle("stability of T_{a} vs fit range (likelihood: start point 20)");
  g2->GetXaxis()->SetTitle("end point");
  g2->GetYaxis()->SetTitle("T_{a}");
  g2->SetMarkerStyle(20);
  g2->SetMarkerColor(4);
  g2->Draw("AP"); 
  g2->Write();

  //gamma tau vs range Chi2
  TGraph *g3=new TGraphErrors(161,range,gamma_tau_C,noerror,gamma_tau_C_error);
  g3->SetName("gamma_tau_vs_fit_range_chi2");
  TCanvas *cc3=new TCanvas("cc3","cc3",1200,800);
  g3->SetTitle("stability of #gamma#tau_{#mu} vs fit range (Chi2: start point 20)");
  g3->GetXaxis()->SetTitle("end point");
  g3->GetYaxis()->SetTitle("#gamma#tau_{#mu}");
  g3->SetMarkerStyle(20);
  g3->SetMarkerColor(4);
  g3->Draw("AP"); 
  g3->Write();
 
  //T vs range Chi2
  TGraph *g4=new TGraphErrors(161,range,T_a_C,noerror,T_a_C_error);
  g4->SetName("Ta_vs_fit_range_chi2");
  TCanvas *cc4=new TCanvas("cc4","cc4",1200,800);
  g4->SetTitle("stability of T_{a} vs fit range (Chi2: start point 20)");
  g4->GetXaxis()->SetTitle("end point");
  g4->GetYaxis()->SetTitle("T_{a}");
  g4->SetMarkerStyle(20);
  g4->SetMarkerColor(4);
  g4->Draw("AP"); 
  g4->Write();  

  //A vs range likelihood
  TGraph *g5=new TGraphErrors(161,range,A_L,noerror,A_L_error);
  g5->SetName("A_vs_fit_range_likelihood");
  TCanvas *cc5=new TCanvas("cc5","cc5",1200,800);
  g5->SetTitle("stability of A vs fit range (likelihood: start point 20)");
  g5->GetXaxis()->SetTitle("end point");
  g5->GetYaxis()->SetTitle("A");
  g5->SetMarkerStyle(20);
  g5->SetMarkerColor(4);
  g5->Draw("AP");   
  g5->Write();

  //A vs range Chi2
  TGraph *g6=new TGraphErrors(161,range,A_C,noerror,A_C_error);
  g6->SetName("A_vs_fit_range_chi2");
  TCanvas *cc6=new TCanvas("cc6","cc6",1200,800);
  g6->SetTitle("stability of A vs fit range (Chi2: start point 20)");
  g6->GetXaxis()->SetTitle("end point");
  g6->GetYaxis()->SetTitle("A");
  g6->SetMarkerStyle(20);
  g6->SetMarkerColor(4);
  g6->Draw("AP"); 
  g6->Write();

  //phi vs range likelihood
  TGraph *g7=new TGraphErrors(161,range,phi_L,noerror,phi_L_error);
  g7->SetName("phi_vs_fit_range_likelihood");
  TCanvas *cc7=new TCanvas("cc7","cc7",1200,800);
  g7->SetTitle("stability of #phi vs fit range (likelihood: start point 20)");
  g7->GetXaxis()->SetTitle("end point");
  g7->GetYaxis()->SetTitle("#phi");
  g7->SetMarkerStyle(20);
  g7->SetMarkerColor(4);
  g7->Draw("AP");         
  g7->Write();

  //phi vs range Chi2
  TGraph *g8=new TGraphErrors(161,range,phi_C,noerror,phi_C_error);
  g8->SetName("phi_vs_fit_range_chi2");
  TCanvas *cc8=new TCanvas("cc8","cc8",1200,800);
  g8->SetTitle("stability of #phi vs fit range (Chi2: start point 20)");
  g8->GetXaxis()->SetTitle("end point");
  g8->GetYaxis()->SetTitle("#phi");
  g8->SetMarkerStyle(20);
  g8->SetMarkerColor(4);
  g8->Draw("AP"); 
  g8->Write();

  //N vs range likelihood 
  TGraph *g9=new TGraphErrors(161,range,N_L,noerror,N_L_error);
  g9->SetName("N_vs_fit_range_likelihood");
  TCanvas *cc9=new TCanvas("cc9","cc9",1200,800);
  g9->SetTitle("stability of N vs fit range (likelihood: start point 20)");
  g9->GetXaxis()->SetTitle("end point");
  g9->GetYaxis()->SetTitle("N");
  g9->SetMarkerStyle(20);
  g9->SetMarkerColor(4);
  g9->Draw("AP");            
  g9->Write();

  //N vs range Chi2
  TGraph *g10=new TGraphErrors(161,range,N_C,noerror,N_C_error);
  g10->SetName("N_vs_fit_range_chi2");
  TCanvas *cc10=new TCanvas("cc10","cc10",1200,800);
  g10->SetTitle("stability of N vs fit range (Chi2: start point 20)");
  g10->GetXaxis()->SetTitle("end point");
  g10->GetYaxis()->SetTitle("N");
  g10->SetMarkerStyle(20);
  g10->SetMarkerColor(4);
  g10->Draw("AP");       
  g10->Write();

  TH1D *h1 = new TH1D("h1","#gamma#tau_{#mu} likelihood",30,60,90);
  TH1D *h2 = new TH1D("h2","T_{a} likelihood",100,4.3,4.4);
  TH1D *h3 = new TH1D("h3","#gamma#tau_{#mu} Chi2",30,60,90);
  TH1D *h4 = new TH1D("h4","T_{a} Chi2",100,4.3,4.4);
  for(int j=0;j<161;j++){
    h1->Fill(gamma_tau_L[j]);
    h2->Fill(T_a_L[j]);
    h3->Fill(gamma_tau_C[j]);
    h4->Fill(T_a_C[j]);
  }

  TCanvas *c1[4];
  gStyle->SetOptStat("RM");
  for(int k=0;k<4;k++){
    c1[k]=new TCanvas (Form("c%i",k),Form("%i",k),1200,800);
    if(k==0) h1->Draw();       
    if(k==1) h2->Draw();
    if(k==2) h3->Draw();
    if(k==3) h4->Draw();
  }

/*  //draw the plots
  cc1->Print("gammaTau_vs_fitRange_likelihood.png");
  cc2->Print("Ta_vs_fitRange_likelihood.png");
  cc3->Print("gammaTau_vs_fitRange_Chi2.png");
  cc4->Print("Ta_vs _fitRange_chi2.png");

  c1[0]->Print("gammaTau_value_likelihood_hist.png");
  c1[1]->Print("Ta_value_likelihood_hist.png");
  c1[2]->Print("gammaTau_value_chi2_hist.png");
  c1[3]->Print("Ta_value_chi2_hist.png");*/
  
  f->Write();
  
}

