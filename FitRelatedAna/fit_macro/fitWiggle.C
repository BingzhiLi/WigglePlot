void fitWiggle(){

  gStyle->SetOptFit(1111);
  gStyle->SetOptStat(10);
  TCanvas *c = new TCanvas("c","c",1200,800);

  double binWidth = 0.148936170213;
  int nRebin = 2;

  TH1D *hittime = new TH1D("hittime","hittime",3000,0,binWidth*3000);
  TFile *file= new TFile("../run/gm2_wiggle_fit_related_ana.root");
  TH1D *allhits = (TH1D*)file->Get("WiggleFitAna/allCaloWiggle");

  // offset to bin 255 (right after the first splash)
  // convert from clock tick to ns histogram
  for(unsigned int i=0;i<3000;i++){
    hittime->SetBinContent(i+1,allhits->GetBinContent(225+i));
  }
  hittime->ResetStats();
  hittime->SetTitle("T-method wiggle plot Likelihood fit");
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
  double gamma_tau_C[161];
  double gamma_tau_C_error[161];
  double T_a_C[161];
  double T_a_C_error[161];
  double range[161];

  for(int i=0;i<161;i++){
    
    range[i]=i+40;
    TF1 *fit = new TF1("fit", "[0]*exp(-x/[1])*(1+[2]*cos([3]+2*TMath::Pi()/[4]*x))", 20,i+40);
    fit->SetNpx(50000);
    fit->SetParNames("N","#gamma#tau_{#mu}","A","#phi","T_{a}(#mus)");
    fit->SetParameters(100,64.4,0.5,0,4.3);

    cout<<"likelihood"<<endl;

    gamma_tau_L[i] = hittime->Fit("fit","SQREML")->Parameter(1);
    gamma_tau_L_error[i] = fit->GetParError(1);
    cout<<i<<"    "<<gamma_tau_L[i]<<"    "<< gamma_tau_L_error[i]<<endl;

    T_a_L[i] = hittime->Fit("fit","SQREML")->Parameter(4);
    T_a_L_error[i] = fit->GetParError(4);
    cout<<i<<"    "<<T_a_L[i]<<"    "<<T_a_L_error[i]<<endl;

    cout<<"chi2"<<endl;

    gamma_tau_C[i] = hittime->Fit("fit","SQREM")->Parameter(1);
    gamma_tau_C_error[i] = fit->GetParError(1);
    cout<<i<<"    "<<gamma_tau_C[i]<<"    "<< gamma_tau_C_error[i]<<endl;
  
    T_a_C[i] = hittime->Fit("fit","SQREM")->Parameter(4);
    T_a_C_error[i] = fit->GetParError(4);
    cout<<i<<"    "<<T_a_C[i]<<"    "<<T_a_C_error[i]<<endl;

    cout<<endl;

  }
  //gamma tau vs range likelihood
  TGraph *g1=new TGraphErrors(161,range,gamma_tau_L,noerror,gamma_tau_L_error);
  TCanvas *cc1=new TCanvas("cc1","cc1",1200,800);
  g1->SetTitle("stability of #gamma#tau_{#mu} vs fit range (likelihood: start point 20)");
  g1->GetXaxis()->SetTitle("end point");
  g1->GetYaxis()->SetTitle("#gamma#tau_{#mu}");
  g1->SetMarkerStyle(20);
  g1->SetMarkerColor(4);
  g1->Draw("AP"); 

  //T vs range likelihood
  TGraph *g2=new TGraphErrors(161,range,T_a_L,noerror,T_a_L_error);
  TCanvas *cc2=new TCanvas("cc2","cc2",1200,800);
  g2->SetTitle("stability of T_{a} vs fit range (likelihood: start point 20)");
  g2->GetXaxis()->SetTitle("end point");
  g2->GetYaxis()->SetTitle("T_{a}");
  g2->SetMarkerStyle(20);
  g2->SetMarkerColor(4);
  g2->Draw("AP"); 

  //gamma tau vs range Chi2
  TGraph *g3=new TGraphErrors(161,range,gamma_tau_C,noerror,gamma_tau_C_error);
  TCanvas *cc3=new TCanvas("cc3","cc3",1200,800);
  g3->SetTitle("stability of #gamma#tau_{#mu} vs fit range (Chi2: start point 20)");
  g3->GetXaxis()->SetTitle("end point");
  g3->GetYaxis()->SetTitle("#gamma#tau_{#mu}");
  g3->SetMarkerStyle(20);
  g3->SetMarkerColor(4);
  g3->Draw("AP"); 

  //T vs range Chi2
  TGraph *g4=new TGraphErrors(161,range,T_a_C,noerror,T_a_C_error);
  TCanvas *cc4=new TCanvas("cc4","cc4",1200,800);
  g4->SetTitle("stability of T_{a} vs fit range (Chi2: start point 20)");
  g4->GetXaxis()->SetTitle("end point");
  g4->GetYaxis()->SetTitle("T_{a}");
  g4->SetMarkerStyle(20);
  g4->SetMarkerColor(4);
  g4->Draw("AP");   

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
    c1[k]=new TCanvas (Form("c%i",k),"",1200,800);
    if(k==0) h1->Draw();
    if(k==1) h2->Draw();
    if(k==2) h3->Draw();
    if(k==3) h4->Draw();
  }

/*  cc1->Print("gammaTau_vs_fitRange_likelihood.png");
  cc2->Print("Ta_vs_fitRange_likelihood.png");
  cc3->Print("gammaTau_vs_fitRange_Chi2.png");
  cc4->Print("Ta_vs _fitRange_chi2.png");*/
  

  
}

