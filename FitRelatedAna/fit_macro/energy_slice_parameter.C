void energy_slice_parameter(){

  gStyle->SetOptFit(1111);
  gStyle->SetOptStat(10);

  double binWidth = 0.148936170213;
  int nRebin = 2;

  //double threshold[3];
  double Ta_L[3],Ta_C[3],tau_L[3],tau_C[3],N_L[3],N_C[3],phi_L[3],phi_C[3],A_L[3],A_C[3];
  double Ta_L_err[3],Ta_C_err[3],tau_L_err[3],tau_C_err[3],N_L_err[3],N_C_err[3],phi_L_err[3],phi_C_err[3],A_L_err[3],A_C_err[3];
  double chi2ndf[3];

  TH1D *hittime[3];
  hittime[0]= new TH1D(Form("Wiggle_plot_energy_slice_1619"),Form("T-Method wiggle plot with energy slice 1.6-1.9GeV"),3000,0,binWidth*3000);    
  hittime[1]= new TH1D(Form("Wiggle_plot_energy_slice_1922"),Form("T-Method wiggle plot with energy slice 1.9-2.2GeV"),3000,0,binWidth*3000);    
  hittime[2]= new TH1D(Form("Wiggle_plot_energy_slice_2231"),Form("T-Method wiggle plot with energy slice 2.2-3.1GeV"),3000,0,binWidth*3000);    


  TFile *file= new TFile("../run/gm2_wiggle_fit_related_ana.1462.v1.root");

  TH1D *allhits[3];
  allhits[0] = (TH1D*)file->Get("WiggleFitAna/energy_slice_1600_1900MeV");
  allhits[1] = (TH1D*)file->Get("WiggleFitAna/energy_slice_1900_2200MeV");
  allhits[2] = (TH1D*)file->Get("WiggleFitAna/energy_slice_2200_3100MeV");


  TFile *f=new TFile("energy_slice_parameter.root","create");

  // offset to bin 255 (right after the first splash)
  // convert from clock tick to ns histogram
  for(int j=0;j<3;j++){
    for(unsigned int i=0;i<3000;i++){
      hittime[j]->SetBinContent(i+1,allhits[j]->GetBinContent(225+i));
    }  
    hittime[j]->ResetStats();
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
  fit_parameter->Branch("Ta_L",&Ta_L[0],"Ta_L[3]/D");
  fit_parameter->Branch("Ta_C",&Ta_C[0],"Ta_C[3]/D");
  fit_parameter->Branch("tau_L",&tau_L[0],"tau_L[3]/D");
  fit_parameter->Branch("tau_C",&tau_C[0],"tau_C[3]/D");
  fit_parameter->Branch("N_L",&N_L[0],"N_L[3]/D");
  fit_parameter->Branch("N_C",&N_C[0],"N_C[3]/D");
  fit_parameter->Branch("phi_L",&phi_L[0],"phi_L[3]/D");
  fit_parameter->Branch("phi_C",&phi_C[0],"phi_C[3]/D");
  fit_parameter->Branch("A_L",&A_L[0],"A_L[3]/D");
  fit_parameter->Branch("A_C",&A_C[0],"A_C[3]/D");

  fit_parameter->Branch("Ta_L_err",&Ta_L_err[0],"Ta_L_err[3]/D");
  fit_parameter->Branch("Ta_C_err",&Ta_C_err[0],"Ta_C_err[3]/D");
  fit_parameter->Branch("tau_L_err",&tau_L_err[0],"tau_L_err[3]/D");
  fit_parameter->Branch("tau_C_err",&tau_C_err[0],"tau_C_err[3]/D");
  fit_parameter->Branch("N_L_err",&N_L_err[0],"N_L_err[3]/D");
  fit_parameter->Branch("N_C_err",&N_C_err[0],"N_C_err[3]/D");
  fit_parameter->Branch("phi_L_err",&phi_L_err[0],"phi_L_err[3]/D");
  fit_parameter->Branch("phi_C_err",&phi_C_err[0],"phi_C_err[3]/D");
  fit_parameter->Branch("A_L_err",&A_L_err[0],"A_L_err[3]/D");
  fit_parameter->Branch("A_C_err",&A_C_err[0],"A_C_err[3]/D");
  fit_parameter->Branch("chi2ndf",&chi2ndf[0],"chi2ndf[3]/D");  


  for(int l=0;l<161;l++){
    for(int p=0;p<3;p++){
      TF1 *fit = new TF1("fit", "[0]*exp(-x/[1])*(1+[2]*cos([3]+2*TMath::Pi()/[4]*x))", 25,l+40);
      fit->SetNpx(50000);
      fit->SetParNames("N","#gamma#tau_{#mu}","A","#phi","T_{a}(#mus)");
      fit->SetParameters(100,64.4,0.5,0,4.3);

      Ta_L[p] = hittime[p]->Fit("fit","SQREML")->Parameter(4);
      Ta_L_err[p] = fit->GetParError(4);
      Ta_C[p] = hittime[p]->Fit("fit","SQREM")->Parameter(4);
      Ta_C_err[p] = fit->GetParError(4);

      tau_L[p] = hittime[p]->Fit("fit","SQREML")->Parameter(1);
      tau_L_err[p] = fit->GetParError(1);
      tau_C[p] = hittime[p]->Fit("fit","SQREM")->Parameter(1);
      tau_C_err[p] = fit->GetParError(1);

      N_L[p] = hittime[p]->Fit("fit","SQREML")->Parameter(0);
      N_L_err[p] = fit->GetParError(0);
      N_C[p] = hittime[p]->Fit("fit","SQREM")->Parameter(0);
      N_C_err[p] = fit->GetParError(0);

      phi_L[p] = hittime[p]->Fit("fit","SQREML")->Parameter(3);
      phi_L_err[p] = fit->GetParError(3);
      phi_C[p] = hittime[p]->Fit("fit","SQREM")->Parameter(3);
      phi_C_err[p] = fit->GetParError(3);  
   
      A_L[p] = hittime[p]->Fit("fit","SQREML")->Parameter(2);
      A_L_err[p] = fit->GetParError(2);
      A_C[p] = hittime[p]->Fit("fit","SQREM")->Parameter(2);
      A_C_err[p] = fit->GetParError(2); 

      chi2ndf[p] = ( hittime[p]->Fit("fit","SQREM")->Chi2() ) / ( hittime[p]->Fit("fit","SQREM")->Ndf() );
      
    }      
    cout<<l<<endl;

    fit_parameter->Fill();
  }


  fit_parameter->Write();
  f->Write();
}   
