void obtain_parameter(){

  gStyle->SetOptFit(1111);
  gStyle->SetOptStat(10);

  double binWidth = 0.148936170213;
  int nRebin = 2;

  double threshold[8];
  double Ta_L[8],Ta_C[8],tau_L[8],tau_C[8],N_L[8],N_C[8],phi_L[8],phi_C[8],A_L[8],A_C[8];
  double Ta_L_err[8],Ta_C_err[8],tau_L_err[8],tau_C_err[8],N_L_err[8],N_C_err[8],phi_L_err[8],phi_C_err[8],A_L_err[8],A_C_err[8];

  TH1D *hittime[8];
  for(int k=0;k<8;k++){
    if(k==0) { threshold[k]=1.86; }
    else { threshold[k]=1.5+0.1*k; }

    hittime[k]= new TH1D(Form("hittime_%f",threshold[k]),Form("hittime_%f",threshold[k]),3000,0,binWidth*3000);    
  }

  TFile *file= new TFile("../run/gm2_wiggle_fit_related_ana.1462.root");

  TH1D *allhits[8];
  allhits[0] = (TH1D*)file->Get("WiggleFitAna/allCaloWiggle");
  allhits[1] = (TH1D*)file->Get("WiggleFitAna/wigglethreshold1600MeV");
  allhits[2] = (TH1D*)file->Get("WiggleFitAna/wigglethreshold1700MeV");
  allhits[3] = (TH1D*)file->Get("WiggleFitAna/wigglethreshold1800MeV");
  allhits[4] = (TH1D*)file->Get("WiggleFitAna/wigglethreshold1900MeV");
  allhits[5] = (TH1D*)file->Get("WiggleFitAna/wigglethreshold2000MeV");
  allhits[6] = (TH1D*)file->Get("WiggleFitAna/wigglethreshold2100MeV");
  allhits[7] = (TH1D*)file->Get("WiggleFitAna/wigglethreshold2200MeV");

  TFile *f=new TFile("parameter.root","create");

  // offset to bin 255 (right after the first splash)
  // convert from clock tick to ns histogram
  for(int j=0;j<8;j++){
    for(unsigned int i=0;i<3000;i++){
      hittime[j]->SetBinContent(i+1,allhits[j]->GetBinContent(225+i));
    }  
    hittime[j]->ResetStats();
    hittime[j]->SetTitle("T-method_wiggle_plot_Likelihood_fit");
    hittime[j]->SetName("T-method Wiggle plot");
    hittime[j]->Rebin(nRebin);
    hittime[j]->SetMarkerStyle(4);
    hittime[j]->SetMarkerColor(4);
    hittime[j]->SetLineColor(4);
    hittime[j]->SetMarkerSize(0.5);
    //hittime[j]->GetXaxis()->SetRangeUser(0,150);
    hittime[j]->GetYaxis()->SetRangeUser(1,10000);
    hittime[j]->GetXaxis()->SetTitle("time [#mus]");
    hittime[j]->GetYaxis()->SetTitle(Form("count / %d*149 ns", nRebin));

    hittime[j]->Write(); 
  }


  TTree *fit_parameter=new TTree("fit_parameter","");
  fit_parameter->Branch("Ta_L",&Ta_L[0],"Ta_L[8]/D");
  fit_parameter->Branch("Ta_C",&Ta_C[0],"Ta_C[8]/D");
  fit_parameter->Branch("tau_L",&tau_L[0],"tau_L[8]/D");
  fit_parameter->Branch("tau_C",&tau_C[0],"tau_C[8]/D");
  fit_parameter->Branch("N_L",&N_L[0],"N_L[8]/D");
  fit_parameter->Branch("N_C",&N_C[0],"N_C[8]/D");
  fit_parameter->Branch("phi_L",&phi_L[0],"phi_L[8]/D");
  fit_parameter->Branch("phi_C",&phi_C[0],"phi_C[8]/D");
  fit_parameter->Branch("A_L",&A_L[0],"A_L[8]/D");
  fit_parameter->Branch("A_C",&A_C[0],"A_C[8]/D");

  fit_parameter->Branch("Ta_L_err",&Ta_L_err[0],"Ta_L_err[8]/D");
  fit_parameter->Branch("Ta_C_err",&Ta_C_err[0],"Ta_C_err[8]/D");
  fit_parameter->Branch("tau_L_err",&tau_L_err[0],"tau_L_err[8]/D");
  fit_parameter->Branch("tau_C_err",&tau_C_err[0],"tau_C_err[8]/D");
  fit_parameter->Branch("N_L_err",&N_L_err[0],"N_L_err[8]/D");
  fit_parameter->Branch("N_C_err",&N_C_err[0],"N_C_err[8]/D");
  fit_parameter->Branch("phi_L_err",&phi_L_err[0],"phi_L_err[8]/D");
  fit_parameter->Branch("phi_C_err",&phi_C_err[0],"phi_C_err[8]/D");
  fit_parameter->Branch("A_L_err",&A_L_err[0],"A_L_err[8]/D");
  fit_parameter->Branch("A_C_err",&A_C_err[0],"A_C_err[8]/D");


  for(int l=0;l<161;l++){
    for(int p=0;p<8;p++){
      TF1 *fit = new TF1("fit", "[0]*exp(-x/[1])*(1+[2]*cos([3]+2*TMath::Pi()/[4]*x))", 20,l+40);
      fit->SetNpx(50000);
      fit->SetParNames("N","#gamma#tau_{#mu}","A","#phi","T_{a}(#mus)");
      fit->SetParameters(100,64.4,0.5,0,4.3);

      Ta_L[p] = hittime[p]->Fit("fit","SQREML")->Parameter(4);
      Ta_L_err[p] = fit->GetParError(4);
      Ta_C[p] = hittime[p]->Fit("fit","SQREM")->Parameter(4);
      Ta_C_err[p] = fit->GetParError(4);

      tau_L[p] = hittime[p]->Fit("fit","SQREML")->Parameter(1);
      tau_L_err[p] = fit->GetParError(1);
      tau_C[p] = hittime[p]->Fit("fit","SQREML")->Parameter(1);
      tau_C_err[p] = fit->GetParError(1);

      N_L[p] = hittime[p]->Fit("fit","SQREML")->Parameter(0);
      N_L_err[p] = fit->GetParError(0);
      N_C[p] = hittime[p]->Fit("fit","SQREM")->Parameter(0);
      N_C_err[p] = fit->GetParError(0);

      phi_L[p] = hittime[p]->Fit("fit","SQREML")->Parameter(3);
      phi_L_err[p] = fit->GetParError(3);
      phi_C[p] = hittime[p]->Fit("fit","SQREML")->Parameter(3);
      phi_C_err[p] = fit->GetParError(3);  
   
      A_L[p] = hittime[p]->Fit("fit","SQREML")->Parameter(2);
      A_L_err[p] = fit->GetParError(2);
      A_C[p] = hittime[p]->Fit("fit","SQREML")->Parameter(2);
      A_C_err[p] = fit->GetParError(2); 


    }      
    cout<<l<<endl;

    fit_parameter->Fill();
  }


  fit_parameter->Write();
  f->Write();
}


