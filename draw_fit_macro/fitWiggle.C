void fitWiggle(){

  gStyle->SetOptFit(1111);
  gStyle->SetOptStat(10);
  TCanvas *c1 = new TCanvas("c1","c1",1200,800);

  double binWidth = 0.148936170213;
  int nRebin = 2;

  TH1D *hittime = new TH1D("hittime","hittime",3000,0,binWidth*3000);
  TFile *file= new TFile("the_root_file_which_will_be_process");
  TH1D *allhits = (TH1D*)file->Get("nearline/allCaloWiggle");

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
  hittime->GetXaxis()->SetRangeUser(0,150);
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

  c1->SetLogy();

  // Fit the wiggle plot!
  TF1 *fit = new TF1("fit", "[0]*exp(-x/[1])*(1+[2]*cos([3]+2*TMath::Pi()/[4]*x))", 20,150);
  fit->SetNpx(50000);
  fit->SetParNames("N","#gamma#tau_{#mu}","A","#phi","T_{a}(#mus)");
  fit->SetParameters(100,64.4,0.5,0,4.3);
  hittime->Fit("fit","REML");//L means likelihood method; no L means chi2 mini method

  TPaveText *txtbox = new TPaveText(20,100,50,400);
  txtbox->SetFillColor(kWhite);
  txtbox->SetLineColor(kWhite);
  txtbox->SetShadowColor(kWhite);
  txtbox->AddText("some_text_you_want_add");
  txtbox->Draw();
}

