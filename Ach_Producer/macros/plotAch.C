#include "RiceStyle.h"

using namespace std;

void plotAch(){

	TH1D::SetDefaultSumw2();

	TFile* file1[3];
	TFile* file2[3];

	TH2D* Npos_uncorr1[3];
	TH2D* Nneg_uncorr1[3];
	TH2D* Npos_corr1[3];
	TH2D* Nneg_corr1[3];
	TH2D* Ach_uncorr1[3];
	TH2D* Ach_corr1[3];

	TH2D* Npos_uncorr2[3];
	TH2D* Nneg_uncorr2[3];
	TH2D* Npos_corr2[3];
	TH2D* Nneg_corr2[3];
	TH2D* Ach_uncorr2[3];
	TH2D* Ach_corr2[3];

	for(int i = 0; i < 3; i++){

		file1[i] = new TFile(Form("../rootfiles/Ach_Producer_EPOS_v3_%d.root", i+1));
		file2[i] = new TFile(Form("../rootfiles/Ach_Producer_Hydjet_v2_%d.root", i+1));

		Npos_uncorr1[i] = (TH2D*) file1[i]->Get("ana/Npos_uncorr");
		Nneg_uncorr1[i] = (TH2D*) file1[i]->Get("ana/Nneg_uncorr");
		Npos_corr1[i] = (TH2D*) file1[i]->Get("ana/Npos_corr");
		Nneg_corr1[i] = (TH2D*) file1[i]->Get("ana/Nneg_corr");
		Ach_uncorr1[i] = (TH2D*) file1[i]->Get("ana/Ach_uncorr");
		Ach_corr1[i] = (TH2D*) file1[i]->Get("ana/Ach_corr");

		Npos_uncorr2[i] = (TH2D*) file2[i]->Get("ana/Npos_uncorr");
		Nneg_uncorr2[i] = (TH2D*) file2[i]->Get("ana/Nneg_uncorr");
		Npos_corr2[i] = (TH2D*) file2[i]->Get("ana/Npos_corr");
		Nneg_corr2[i] = (TH2D*) file2[i]->Get("ana/Nneg_corr");
		Ach_uncorr2[i] = (TH2D*) file2[i]->Get("ana/Ach_uncorr");
		Ach_corr2[i] = (TH2D*) file2[i]->Get("ana/Ach_corr");

	}



	for(int i = 0; i < 3; i++){

		Npos_uncorr1[i]->ProfileY(Form("Npos_uncorr1_%d",i+1), 1, 2000, "");
		Nneg_uncorr1[i]->ProfileY(Form("Nneg_uncorr1_%d",i+1), 1, 2000, "");
		Npos_corr1[i]->ProfileY(Form("Npos_corr1_%d",i+1), 1, 2000, "");
		Nneg_corr1[i]->ProfileY(Form("Nneg_corr1_%d",i+1), 1, 2000, "");
		Ach_uncorr1[i]->ProfileY(Form("Ach_uncorr1_%d",i+1), 1, 3000, "");
		Ach_corr1[i]->ProfileY(Form("Ach_corr1_%d",i+1), 1, 3000, "");

		Npos_uncorr2[i]->ProfileY(Form("Npos_uncorr2_%d",i+1), 1, 2000, "");
		Nneg_uncorr2[i]->ProfileY(Form("Nneg_uncorr2_%d",i+1), 1, 2000, "");
		Npos_corr2[i]->ProfileY(Form("Npos_corr2_%d",i+1), 1, 2000, "");
		Nneg_corr2[i]->ProfileY(Form("Nneg_corr2_%d",i+1), 1, 2000, "");
		Ach_uncorr2[i]->ProfileY(Form("Ach_uncorr2_%d",i+1), 1, 3000, "");
		Ach_corr2[i]->ProfileY(Form("Ach_corr2_%d",i+1), 1, 3000, "");

	}

	cout << "corrected EPOS: " << Ach_corr1[0]->GetCorrelationFactor() << endl;
	cout << "corrected Hydjet: " << Ach_corr2[0]->GetCorrelationFactor() << endl;

	cout << "uncorrected EPOS: " << Ach_uncorr1[0]->GetCorrelationFactor() << endl;
	cout << "uncorrected Hydjet: " << Ach_uncorr2[0]->GetCorrelationFactor() << endl;


	// TFile f1("./Ach_uncorr_weight.root", "RECREATE");

	TH1D* test1 = Ach_corr1[1]->ProjectionY("test1", 1,3000);
	TH1D* test2 = Ach_corr2[1]->ProjectionY("ApplyEPOS_0", 1,3000);

	test1->SetMarkerStyle(20);
	test2->SetMarkerStyle(20);

	test1->SetMarkerColor(1);
	test2->SetMarkerColor(2);

	test1->SetLineColor(1);
	test2->SetLineColor(2);

	test1->Scale(1.0/Ach_corr1[1]->GetEntries());
	test2->Scale(1.0/Ach_corr2[1]->GetEntries());

	test1->Rebin(100);
	test2->Rebin(100);

	test1->Draw("P");
	//test2->Divide( test1 );
	test2->Draw("Psame");

    return;

	// TH1D* test11 = Ach_uncorr1[1]->ProjectionX("test11", 1,3000);
	// TH1D* test22 = Ach_uncorr2[1]->ProjectionX("ApplyEPOS_1", 1,3000);

	// test11->SetMarkerStyle(20);
	// test22->SetMarkerStyle(20);

	// test11->SetMarkerColor(1);
	// test22->SetMarkerColor(2);

	// test11->Scale(1.0/Ach_uncorr1[1]->GetEntries());
	// test22->Scale(1.0/Ach_uncorr2[1]->GetEntries());

	// test11->Rebin(100);
	// test22->Rebin(100);

	// test22->Divide( test11 );
	// test22->Write();

	// TH1D* test111 = Ach_uncorr1[2]->ProjectionX("test111", 1,3000);
	// TH1D* test222 = Ach_uncorr2[2]->ProjectionX("ApplyEPOS_2", 1,3000);

	// test111->SetMarkerStyle(20);
	// test222->SetMarkerStyle(20);

	// test111->SetMarkerColor(1);
	// test222->SetMarkerColor(2);

	// test111->Scale(1.0/Ach_uncorr1[2]->GetEntries());
	// test222->Scale(1.0/Ach_uncorr2[2]->GetEntries());

	// test111->Rebin(100);
	// test222->Rebin(100);

	// test222->Divide( test111 );
	// test222->Write();
	

	
	// return;
	
	// TCanvas* c3 = new TCanvas();

	// test1->Draw("P");
	// test2->Draw("Psame");

	// return;


	TGaxis::SetMaxDigits(3);

	TH1D* base1 = makeHist("base1", "", "N_{+}", "", 1500,0,1500,kBlack);

	base1->GetYaxis()->SetRangeUser(0,1500);
	base1->GetXaxis()->SetRangeUser(0,1500);
	base1->GetXaxis()->SetTitleColor(kBlack);

	
	fixedFontHist1D(base1,1.1,1.25);

	base1->GetYaxis()->SetTitleOffset(1.3);
	base1->GetXaxis()->SetTitleOffset(1.0);
	base1->GetYaxis()->SetTitleSize(base1->GetYaxis()->GetTitleSize()*1.3);
	base1->GetXaxis()->SetTitleSize(base1->GetXaxis()->GetTitleSize()*1.4);
	base1->GetYaxis()->SetLabelSize(base1->GetYaxis()->GetLabelSize()*1.4);
	base1->GetXaxis()->SetLabelSize(base1->GetXaxis()->GetLabelSize()*1.4);
	
	base1->GetXaxis()->SetNdivisions(5,8,0);

	TH1D* base11 = makeHist("base11", "", "N_{-}", "", 1500,0,1500,kBlack);

	base11->GetYaxis()->SetRangeUser(0,1500);
	base11->GetXaxis()->SetRangeUser(0,1500);
	base11->GetXaxis()->SetTitleColor(kBlack);

	
	fixedFontHist1D(base11,1.1,1.25);

	base11->GetYaxis()->SetTitleOffset(1.3);
	base11->GetXaxis()->SetTitleOffset(1.0);
	base11->GetYaxis()->SetTitleSize(base11->GetYaxis()->GetTitleSize()*1.3);
	base11->GetXaxis()->SetTitleSize(base11->GetXaxis()->GetTitleSize()*1.4);
	base11->GetYaxis()->SetLabelSize(base11->GetYaxis()->GetLabelSize()*1.4);
	base11->GetXaxis()->SetLabelSize(base11->GetXaxis()->GetLabelSize()*1.4);
	
	base11->GetXaxis()->SetNdivisions(5,8,0);


	TH1D* base2 = makeHist("base2", "", "GEN A_{ch}", "", 300,-0.20,0.20,kBlack);

	base2->GetYaxis()->SetRangeUser(-0.2,0.3);
	base2->GetXaxis()->SetRangeUser(-0.20,0.20);
	base2->GetXaxis()->SetTitleColor(kBlack);

	
	fixedFontHist1D(base2,1.1,1.25);

	base2->GetYaxis()->SetTitleOffset(1.3);
	base2->GetXaxis()->SetTitleOffset(0.9);
	base2->GetYaxis()->SetTitleSize(base2->GetYaxis()->GetTitleSize()*1.3);
	base2->GetXaxis()->SetTitleSize(base2->GetXaxis()->GetTitleSize()*1.4);
	base2->GetYaxis()->SetLabelSize(base2->GetYaxis()->GetLabelSize()*1.4);
	base2->GetXaxis()->SetLabelSize(base2->GetXaxis()->GetLabelSize()*1.4);
	
	base2->GetXaxis()->SetNdivisions(5,8,0);

	TLatex* latex5 = new TLatex(0.24, 0.21, "EPOS");
    latex5->SetNDC();
    latex5->SetTextSize(20);
    latex5->SetTextFont(43);
    latex5->SetTextColor(kBlack);
    
    TLatex* latex6 = new TLatex(0.24, 0.21, "Hydjet");
    latex6->SetNDC();
    latex6->SetTextSize(20);
    latex6->SetTextFont(43);
    latex6->SetTextColor(kBlack);

    TLatex* latex7 = new TLatex(0.24, 0.85, "200 #leq N^{offline}_{trk} < 400");
    latex7->SetNDC();
    latex7->SetTextSize(20);
    latex7->SetTextFont(43);
    latex7->SetTextColor(kBlack);

	TCanvas* c1 = new TCanvas("c1","",1,1,1200,400);
	c1->Divide(3,1,0.01,0.01);
	c1->cd(1);
	gPad->SetLeftMargin(0.20);
	gPad->SetBottomMargin(0.20);
	gPad->SetTopMargin(0.06);
	gPad->SetTicks();

	base1->Draw();
	
	Npos_uncorr1_1->Rebin(10);
	Npos_uncorr1_1->SetMarkerStyle(20);
	Npos_uncorr1_1->SetMarkerColor(kBlack);
	Npos_uncorr1_1->SetLineColor(kBlack);
	Npos_uncorr1_1->Draw("Psame");

	Npos_corr1_1->Rebin(10);
	Npos_corr1_1->SetMarkerStyle(20);
	Npos_corr1_1->SetMarkerColor(kRed);
	Npos_corr1_1->SetLineColor(kRed);
	Npos_corr1_1->Draw("Psame");

	Npos_uncorr2_1->Rebin(10);
	Npos_uncorr2_1->SetMarkerStyle(24);
	Npos_uncorr2_1->SetMarkerColor(kBlack);
	Npos_uncorr2_1->SetLineColor(kBlack);
	Npos_uncorr2_1->Draw("Psame");

	Npos_corr2_1->Rebin(10);
	Npos_corr2_1->SetMarkerStyle(24);
	Npos_corr2_1->SetMarkerColor(kRed);
	Npos_corr2_1->SetLineColor(kRed);
	Npos_corr2_1->Draw("Psame");

	latex5->Draw("same");

	latex7->Draw("same");

	c1->cd(2);
	gPad->SetLeftMargin(0.20);
	gPad->SetBottomMargin(0.20);
	gPad->SetTopMargin(0.06);
	gPad->SetTicks();

	base11->Draw();
	Nneg_uncorr1_1->Rebin(10);
	Nneg_uncorr1_1->SetMarkerStyle(20);
	Nneg_uncorr1_1->SetMarkerColor(kBlack);
	Nneg_uncorr1_1->SetLineColor(kBlack);
	Nneg_uncorr1_1->Draw("Psame");

	Nneg_corr1_1->Rebin(10);
	Nneg_corr1_1->SetMarkerStyle(20);
	Nneg_corr1_1->SetMarkerColor(kRed);
	Nneg_corr1_1->SetLineColor(kRed);
	Nneg_corr1_1->Draw("Psame");

	Nneg_uncorr2_1->Rebin(10);
	Nneg_uncorr2_1->SetMarkerStyle(24);
	Nneg_uncorr2_1->SetMarkerColor(kBlack);
	Nneg_uncorr2_1->SetLineColor(kBlack);
	Nneg_uncorr2_1->Draw("Psame");

	Nneg_corr2_1->Rebin(10);
	Nneg_corr2_1->SetMarkerStyle(24);
	Nneg_corr2_1->SetMarkerColor(kRed);
	Nneg_corr2_1->SetLineColor(kRed);
	Nneg_corr2_1->Draw("Psame");

	latex5->Draw("same");

	c1->cd(3);
	gPad->SetLeftMargin(0.20);
	gPad->SetBottomMargin(0.20);
	gPad->SetTopMargin(0.06);
	gPad->SetTicks();

	base2->Draw();
	Ach_uncorr1_1->Rebin(10);
	Ach_uncorr1_1->SetMarkerStyle(20);
	Ach_uncorr1_1->SetMarkerColor(kBlack);
	Ach_uncorr1_1->SetLineColor(kBlack);
	Ach_uncorr1_1->Draw("Psame");

	Ach_corr1_1->Rebin(10);
	Ach_corr1_1->SetMarkerStyle(20);
	Ach_corr1_1->SetMarkerColor(kRed);
	Ach_corr1_1->SetLineColor(kRed);
	Ach_corr1_1->Draw("Psame");

	Ach_uncorr2_1->Rebin(10);
	Ach_uncorr2_1->SetMarkerStyle(24);
	Ach_uncorr2_1->SetMarkerColor(kBlack);
	Ach_uncorr2_1->SetLineColor(kBlack);
	Ach_uncorr2_1->Draw("Psame");

	Ach_corr2_1->Rebin(10);
	Ach_corr2_1->SetMarkerStyle(24);
	Ach_corr2_1->SetMarkerColor(kRed);
	Ach_corr2_1->SetLineColor(kRed);
	Ach_corr2_1->Draw("Psame");

	Ach_corr1_1->Fit("pol1");
    TF1 * myFunc1 = Ach_corr1_1->GetFunction("pol1");
    myFunc1->SetLineStyle(2);
    myFunc1->SetLineColor(kBlue);
    double intersect_1 = myFunc1->GetParameter(0);
    double intersect_1_error = myFunc1->GetParError(0);
    double slope_1 = myFunc1->GetParameter(1);
    double slope_1_error = myFunc1->GetParError(1);

    TLatex* latex1 = new TLatex(0.21, 0.85, Form("EPOS slope: %.6f +/- %.6f",slope_1, slope_1_error ));
    latex1->SetNDC();
    latex1->SetTextSize(16);
    latex1->SetTextFont(43);
    latex1->SetTextColor(kBlue);
    latex1->Draw("same");

    TLatex* latex2 = new TLatex(0.21, 0.8, Form("EPOS intersect: %.6f +/- %.6f",intersect_1, intersect_1_error ));
    latex2->SetNDC();
    latex2->SetTextSize(16);
    latex2->SetTextFont(43);
    latex2->SetTextColor(kBlue);
    latex2->Draw("same");

	Ach_corr2_1->Fit("pol1");
    TF1 * myFunc2 = Ach_corr2_1->GetFunction("pol1");
    myFunc2->SetLineStyle(2);
    myFunc2->SetLineColor(kBlue);
    double intersect_1 = myFunc2->GetParameter(0);
    double intersect_1_error = myFunc2->GetParError(0);
    double slope_1 = myFunc2->GetParameter(1);
    double slope_1_error = myFunc2->GetParError(1);

    TLatex* latex3 = new TLatex(0.21, 0.75, Form("Hydjet slope: %.6f +/- %.6f",slope_1, slope_1_error ));
    latex3->SetNDC();
    latex3->SetTextSize(16);
    latex3->SetTextFont(43);
    latex3->SetTextColor(kBlue);
    latex3->Draw("same");

    TLatex* latex4 = new TLatex(0.21, 0.7, Form("Hydjet intersect: %.6f +/- %.6f",intersect_1, intersect_1_error ));
    latex4->SetNDC();
    latex4->SetTextSize(16);
    latex4->SetTextFont(43);
    latex4->SetTextColor(kBlue);
    latex4->Draw("same");

    

	// c1->cd(4);
	// gPad->SetLeftMargin(0.20);
	// gPad->SetBottomMargin(0.13);
	// gPad->SetTopMargin(0.06);
	// gPad->SetTicks();

	// base1->Draw();
	// Npos_uncorr2_1->Rebin(10);
	// Npos_uncorr2_1->SetMarkerStyle(20);
	// Npos_uncorr2_1->SetMarkerColor(kBlack);
	// Npos_uncorr2_1->SetLineColor(kBlack);
	// Npos_uncorr2_1->Draw("Psame");

	// Npos_corr2_1->Rebin(10);
	// Npos_corr2_1->SetMarkerStyle(20);
	// Npos_corr2_1->SetMarkerColor(kRed);
	// Npos_corr2_1->SetLineColor(kRed);
	// Npos_corr2_1->Draw("Psame");

	// latex6->Draw("same");

	// c1->cd(5);
	// gPad->SetLeftMargin(0.20);
	// gPad->SetBottomMargin(0.13);
	// gPad->SetTopMargin(0.06);
	// gPad->SetTicks();

	// base11->Draw();
	// Nneg_uncorr2_1->Rebin(10);
	// Nneg_uncorr2_1->SetMarkerStyle(20);
	// Nneg_uncorr2_1->SetMarkerColor(kBlack);
	// Nneg_uncorr2_1->SetLineColor(kBlack);
	// Nneg_uncorr2_1->Draw("Psame");

	// Nneg_corr2_1->Rebin(10);
	// Nneg_corr2_1->SetMarkerStyle(20);
	// Nneg_corr2_1->SetMarkerColor(kRed);
	// Nneg_corr2_1->SetLineColor(kRed);
	// Nneg_corr2_1->Draw("Psame");

	// latex6->Draw("same");

	// c1->cd(6);
	// gPad->SetLeftMargin(0.20);
	// gPad->SetBottomMargin(0.13);
	// gPad->SetTopMargin(0.06);
	// gPad->SetTicks();

	// base2->Draw();
	// Ach_uncorr2_1->Rebin(100);
	// Ach_uncorr2_1->SetMarkerStyle(20);
	// Ach_uncorr2_1->SetMarkerColor(kBlack);
	// Ach_uncorr2_1->SetLineColor(kBlack);
	// Ach_uncorr2_1->Draw("Psame");

	// Ach_corr2_1->Rebin(100);
	// Ach_corr2_1->SetMarkerStyle(20);
	// Ach_corr2_1->SetMarkerColor(kRed);
	// Ach_corr2_1->SetLineColor(kRed);
	// Ach_corr2_1->Draw("Psame");
	
	// Ach_corr2_1->Fit("pol1");
 //    TF1 * myFunc2 = Ach_corr2_1->GetFunction("pol1");
 //    myFunc2->SetLineStyle(2);
 //    myFunc2->SetLineColor(kBlue);
 //    double intersect_1 = myFunc2->GetParameter(0);
 //    double intersect_1_error = myFunc2->GetParError(0);
 //    double slope_1 = myFunc2->GetParameter(1);
 //    double slope_1_error = myFunc2->GetParError(1);

 //    TLatex* latex3 = new TLatex(0.21, 0.85, Form("slope: %.6f +/- %.6f",slope_1, slope_1_error ));
 //    latex3->SetNDC();
 //    latex3->SetTextSize(16);
 //    latex3->SetTextFont(43);
 //    latex3->SetTextColor(kBlue);
 //    latex3->Draw("same");

 //    TLatex* latex4 = new TLatex(0.21, 0.8, Form("intersect: %.6f +/- %.6f",intersect_1, intersect_1_error ));
 //    latex4->SetNDC();
 //    latex4->SetTextSize(16);
 //    latex4->SetTextFont(43);
 //    latex4->SetTextColor(kBlue);
 //    latex4->Draw("same");

	TLegend *w10 = new TLegend(0.5,0.14,0.7.5,0.30);
    w10->SetLineColor(kWhite);
    w10->SetFillColor(0);
    w10->SetTextSize(18);
    w10->SetTextFont(43);
    w10->AddEntry(Ach_uncorr1_1, "EPOS uncorrected", "P");
    w10->AddEntry(Ach_corr1_1, "EPOS corrected", "P");
    w10->AddEntry(Ach_uncorr2_1, "Hydjet uncorrected", "P");
    w10->AddEntry(Ach_corr2_1, "Hydjet corrected", "P");
    w10->Draw("same");

    latex6->Draw("same");

    //c1->Print("../figures/Ach_RECO_vs_GEN_1.pdf");
    //c1->Print("../figures/Ach_RECO_vs_GEN_1.gif");




}