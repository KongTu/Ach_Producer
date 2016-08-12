#include "RiceStyle.h"

using namespace std;

void makeCorrectionFactor(){

	TFile* file1[3];
	TFile* file2[3];

	TH2D* Ach_uncorr1[3];
	TH2D* Ach_corr1[3];

	TH2D* Ach_uncorr2[3];
	TH2D* Ach_corr2[3];

	for(int i = 0; i < 6; i++){

		// file1[i] = new TFile(Form("../rootfiles/Ach_Producer_EPOS_v2_%d.root", i+1));
		// file2[i] = new TFile(Form("../rootfiles/Ach_Producer_Hydjet_v2_%d.root", i+1));

		file1[i] = new TFile("../rootfiles/Ach_Producer_pPb_EPOS_v1_rebin.root");
		file2[i] = new TFile("../rootfiles/Ach_Producer_pPb_HIJING_v1_rebin.root");

		Ach_uncorr1[i] = (TH2D*) file1[i]->Get("ana/Ach_uncorr");
		Ach_corr1[i] = (TH2D*) file1[i]->Get("ana/Ach_corr");

		Ach_uncorr2[i] = (TH2D*) file2[i]->Get("ana/Ach_uncorr");
		Ach_corr2[i] = (TH2D*) file2[i]->Get("ana/Ach_corr");

	}

	TFile* file3 = new TFile("../data/achdist_pPb.root");

	TH1D* ach_data[6];
	for(int i = 0; i < 6; i++){

		ach_data[i] = (TH1D*) file3->Get(Form("h_%d",i));

	}
	
	TH1D* base1 = makeHist("base1", "", "A_{ch}", "DATA/EPOS", 1000, -0.4, 0.4, kBlack);
	base1->GetYaxis()->SetRangeUser(0,2.2);
	base1->GetYaxis()->SetNdivisions(5,6,0);
	base1->GetXaxis()->SetNdivisions(5,8,0);
	base1->GetYaxis()->SetTitleOffset(1.6);

	Ach_corr1[0]->ProjectionX("test",1,1000);
	test->SetMarkerStyle(24);
	test->SetMarkerColor(kRed);
	test->Scale( 1.0/Ach_corr1[0]->GetEntries() );
	test->Rebin(10);
	
	TGaxis::SetMaxDigits(3);

	TLatex* latex1[6];


    latex1[0] = new TLatex(0.3, 0.85, "90 #leq N^{offline}_{trk} < 120");
    latex1[1] = new TLatex(0.3, 0.85, "120 #leq N^{offline}_{trk} < 150");
    latex1[2] = new TLatex(0.3, 0.85, "150 #leq N^{offline}_{trk} < 185");
    latex1[3] = new TLatex(0.3, 0.85, "185 #leq N^{offline}_{trk} < 220");
    latex1[4] = new TLatex(0.3, 0.85, "220 #leq N^{offline}_{trk} < 260");
    latex1[5] = new TLatex(0.3, 0.85, "260 #leq N^{offline}_{trk} < 300");
  

	TCanvas* c1 = makeMultiCanvas("c1","c1",3,2);
	for(int mult = 0; mult < 6; mult++){

		c1->cd(mult+1);
		gPad->SetLeftMargin(0.15);
		gPad->SetBottomMargin(0.15);
		gPad->SetTopMargin(0.06);
		gPad->SetTicks();

		base1->Draw();

		ach_data[mult]->SetMarkerStyle(24);
		ach_data[mult]->Scale( 1.0/ach_data[mult]->GetEntries() );
		ach_data[mult]->Rebin(10);
		ach_data[mult]->Divide( test );
		ach_data[mult]->Draw("Psame");
		//test->Draw("Psame");

		latex1[mult]->SetNDC();
		latex1[mult]->SetTextSize(25);
		latex1[mult]->SetTextFont(43);
		latex1[mult]->SetTextColor(kBlack);
		latex1[mult]->Draw("same");

	}

	TLegend *w1 = new TLegend(0.3,0.65,0.7,0.8);
    w1->SetLineColor(kWhite);
    w1->SetFillColor(0);
    w1->SetTextSize(23);
    w1->SetTextFont(43);
    w1->AddEntry(ach_data[0], "pPb data", "P");
    w1->AddEntry(test, "pPb EPOS", "P");

    c1->cd(2);
    //w1->Draw("same");

 //    TFile f1("../data/Ach_reweight_pPb_data.root", "RECREATE");
    
	
	// for(int mult = 0; mult < 6; mult++){

	// 	TH1D* temp = (TH1D*) ach_data[mult]->Clone(Form("ApplyEPOS_%d", mult));
	// 	temp->Divide( test );
	// 	temp->Write();

	// }
	





	


}