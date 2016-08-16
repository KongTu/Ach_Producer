#include "RiceStyle.h"

using namespace std;

void plotAch(){

	TH1D::SetDefaultSumw2();

	TFile* file1[6];
	TFile* file2[6];

	TH2D* Npos_uncorr1[6];
	TH2D* Nneg_uncorr1[6];
	TH2D* Npos_corr1[6];
	TH2D* Nneg_corr1[6];
	TH2D* Ach_uncorr1[6];
	TH2D* Ach_corr1[6];

	TH2D* Npos_uncorr2[6];
	TH2D* Nneg_uncorr2[6];
	TH2D* Npos_corr2[6];
	TH2D* Nneg_corr2[6];
	TH2D* Ach_uncorr2[6];
	TH2D* Ach_corr2[6];

	for(int i = 0; i < 6; i++){

		file1[i] = new TFile(Form("../rootfiles/Ach_Producer_PbPb_EPOS_v6_%d.root", i+1));
		file2[i] = new TFile(Form("../rootfiles/Ach_Producer_PbPb_Hydjet_v6_%d.root", i+1));

		//file1[i] = new TFile(Form("../rootfiles/Ach_Producer_pPb_EPOS_v5_%d.root", i+1));
		//file2[i] = new TFile(Form("../rootfiles/Ach_Producer_pPb_HIJING_v2.root", i+1));

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



	for(int i = 0; i < 6; i++){

		Npos_uncorr1[i]->ProfileX(Form("Npos_uncorr1_%d",i+1), 1, 2000, "");
		Nneg_uncorr1[i]->ProfileX(Form("Nneg_uncorr1_%d",i+1), 1, 2000, "");
		Npos_corr1[i]->ProfileX(Form("Npos_corr1_%d",i+1), 1, 2000, "");
		Nneg_corr1[i]->ProfileX(Form("Nneg_corr1_%d",i+1), 1, 2000, "");
		Ach_uncorr1[i]->ProfileX(Form("Ach_uncorr1_%d",i+1), 1, 1000, "");
		Ach_corr1[i]->ProfileX(Form("Ach_corr1_%d",i+1), 1, 1000, "");

		Npos_uncorr2[i]->ProfileX(Form("Npos_uncorr2_%d",i+1), 1, 2000, "");
		Nneg_uncorr2[i]->ProfileX(Form("Nneg_uncorr2_%d",i+1), 1, 2000, "");
		Npos_corr2[i]->ProfileX(Form("Npos_corr2_%d",i+1), 1, 2000, "");
		Nneg_corr2[i]->ProfileX(Form("Nneg_corr2_%d",i+1), 1, 2000, "");
		Ach_uncorr2[i]->ProfileX(Form("Ach_uncorr2_%d",i+1), 1, 1000, "");
		Ach_corr2[i]->ProfileX(Form("Ach_corr2_%d",i+1), 1, 1000, "");

	}

	//string multiplicity[] = {"80 #leq N^{offline}_{trk} < 120", "120 #leq N^{offline}_{trk} < 150","150 #leq N^{offline}_{trk} < 1000"}
	// string multiplicity[] = {"90 #leq N^{offline}_{trk} < 120", "120 #leq N^{offline}_{trk} < 150","150 #leq N^{offline}_{trk} < 185",
 //                             "185 #leq N^{offline}_{trk} < 220", "220 #leq N^{offline}_{trk} < 260","260 #leq N^{offline}_{trk} < 300" };
    string multiplicity[] = {"30-40%", "40-50%","50-60%","60-70%", "70-80%", "80-90%"};

	TCanvas* c2 = makeMultiCanvas("c3","",3,2);
	for(int mult = 0; mult < 6; mult++){

		c2->cd(mult+1);
		gPad->SetLeftMargin(0.11);
		gPad->SetBottomMargin(0.11);
		gPad->SetTopMargin(0.1);
		gPad->SetTicks();
		Ach_corr2[mult]->SetStats(kFALSE);
		Ach_corr2[mult]->RebinX(20);
		Ach_corr2[mult]->RebinY(20);
		Ach_corr2[mult]->GetYaxis()->SetTitle("GEN A_{ch}");
		Ach_corr2[mult]->GetYaxis()->SetTitleSize(0.05);
		Ach_corr2[mult]->GetYaxis()->CenterTitle();
		Ach_corr2[mult]->GetXaxis()->SetTitle("RECO A_{ch}");
		Ach_corr2[mult]->GetXaxis()->CenterTitle();
		Ach_corr2[mult]->GetXaxis()->SetTitleSize(0.05);
		Ach_corr2[mult]->SetTitle( multiplicity[mult].c_str() );
		Ach_corr2[mult]->Draw("colz");

		cout << "corrected EPOS: " << Ach_corr2[mult]->GetCorrelationFactor() << endl;

		TLatex* latex3 = new TLatex(0.20, 0.16, Form("Hydjet Correlation Factor: %.3f",Ach_corr2[mult]->GetCorrelationFactor() ));
	    latex3->SetNDC();
	    latex3->SetTextSize(20);
	    latex3->SetTextFont(43);
	    latex3->SetTextColor(kBlack);
	    latex3->Draw("same");

	}

	return;

	


	// return;

  //   TFile f1("./Ach_gen_weight.root", "RECREATE");
  	
 //  	TCanvas* c2 = makeCanvas("c2","",kFALSE, kFALSE);
 //  	gPad->SetLeftMargin(0.10);
	// gPad->SetBottomMargin(0.10);
	// gPad->SetTopMargin(0.06);
	// gPad->SetTicks();

	// Ach_corr2[0]->SetStats(kFALSE);
	// Ach_corr2[0]->Draw("colz");

 //    TLatex* latex1 = new TLatex(0.15, 0.85, "pPb HIJING");
 //    latex1->SetNDC();
 //    latex1->SetTextSize(25);
 //    latex1->SetTextFont(43);
 //    latex1->SetTextColor(kBlack);
 //    latex1->Draw("same");
	// return;

 //    for(int i = 0; i < 4; i++){
		
	// 	TH1D* test1 = Ach_corr2[i]->ProjectionX(Form("test%d",i), 1,5000);
	// 	TH1D* test2 = Ach_corr2[i]->ProjectionY(Form("ApplyEPOS_%d",i), 1,5000);

	// 	test1->SetMarkerStyle(20);
	// 	test2->SetMarkerStyle(20);

	// 	test1->SetMarkerColor(kBlack);
	// 	test2->SetMarkerColor(kRed);

	// 	test1->SetLineColor(1);
	// 	test2->SetLineColor(2);

	// 	test1->Scale(1.0/Ach_corr2[i]->GetEntries());
	// 	test2->Scale(1.0/Ach_corr2[i]->GetEntries());

	// 	test1->Rebin(100);
	// 	test2->Rebin(100);

	// 	test2->GetXaxis()->SetTitle("A_{ch}");
	// 	test2->SetStats(kFALSE);
	// 	test2->Draw("P");
	// 	//test2->Divide( test1 );
	// 	//test2->Write();
 //    	test1->Draw("Psame");
 //    }

	// TLegend *w1 = new TLegend(0.5,0.14,0.7.5,0.30);
 //    w1->SetLineColor(kWhite);
 //    w1->SetFillColor(0);
 //    w1->SetTextSize(23);
 //    w1->SetTextFont(43);
 //    w1->AddEntry(test1, "RECO", "P");
 //    w1->AddEntry(test2, "GEN", "P");

 //    w1->Draw("same");

 //    TLatex* latex1 = new TLatex(0.15, 0.85, "pPb HIJING");
 //    latex1->SetNDC();
 //    latex1->SetTextSize(25);
 //    latex1->SetTextFont(43);
 //    latex1->SetTextColor(kBlack);
 //    latex1->Draw("same");

 //    return;


	TGaxis::SetMaxDigits(3);

	TH1D* base1 = makeHist("base1", "", "N_{+}", "", 1500,0,1500,kBlack);

	base1->GetYaxis()->SetRangeUser(0,300);
	base1->GetXaxis()->SetRangeUser(0,300);
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

	base11->GetYaxis()->SetRangeUser(0,300);
	base11->GetXaxis()->SetRangeUser(0,300);
	base11->GetXaxis()->SetTitleColor(kBlack);

	
	fixedFontHist1D(base11,1.1,1.25);

	base11->GetYaxis()->SetTitleOffset(1.3);
	base11->GetXaxis()->SetTitleOffset(1.0);
	base11->GetYaxis()->SetTitleSize(base11->GetYaxis()->GetTitleSize()*1.3);
	base11->GetXaxis()->SetTitleSize(base11->GetXaxis()->GetTitleSize()*1.4);
	base11->GetYaxis()->SetLabelSize(base11->GetYaxis()->GetLabelSize()*1.4);
	base11->GetXaxis()->SetLabelSize(base11->GetXaxis()->GetLabelSize()*1.4);
	
	base11->GetXaxis()->SetNdivisions(5,8,0);


	TH1D* base2 = makeHist("base2", "", "RECO A_{ch}", "", 300,-0.20,0.20,kBlack);

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

	TLatex* latex5 = new TLatex(0.24, 0.21, "");
    latex5->SetNDC();
    latex5->SetTextSize(20);
    latex5->SetTextFont(43);
    latex5->SetTextColor(kBlack);
    
    TLatex* latex6 = new TLatex(0.24, 0.21, "");
    latex6->SetNDC();
    latex6->SetTextSize(20);
    latex6->SetTextFont(43);
    latex6->SetTextColor(kBlack);

    TLatex* latex7 = new TLatex(0.24, 0.85, "80 #leq N^{offline}_{trk}");
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
	
	Npos_uncorr1_3->Rebin(10);
	Npos_uncorr1_3->SetMarkerStyle(20);
	Npos_uncorr1_3->SetMarkerColor(kBlack);
	Npos_uncorr1_3->SetLineColor(kBlack);
	Npos_uncorr1_3->Draw("Psame");

	Npos_corr1_3->Rebin(10);
	Npos_corr1_3->SetMarkerStyle(20);
	Npos_corr1_3->SetMarkerColor(kRed);
	Npos_corr1_3->SetLineColor(kRed);
	Npos_corr1_3->Draw("Psame");

	Npos_uncorr2_3->Rebin(10);
	Npos_uncorr2_3->SetMarkerStyle(24);
	Npos_uncorr2_3->SetMarkerColor(kBlack);
	Npos_uncorr2_3->SetLineColor(kBlack);
	Npos_uncorr2_3->Draw("Psame");

	Npos_corr2_3->Rebin(10);
	Npos_corr2_3->SetMarkerStyle(24);
	Npos_corr2_3->SetMarkerColor(kRed);
	Npos_corr2_3->SetLineColor(kRed);
	Npos_corr2_3->Draw("Psame");

	latex5->Draw("same");

	latex7->Draw("same");

	c1->cd(2);
	gPad->SetLeftMargin(0.20);
	gPad->SetBottomMargin(0.20);
	gPad->SetTopMargin(0.06);
	gPad->SetTicks();

	base11->Draw();
	Nneg_uncorr1_3->Rebin(10);
	Nneg_uncorr1_3->SetMarkerStyle(20);
	Nneg_uncorr1_3->SetMarkerColor(kBlack);
	Nneg_uncorr1_3->SetLineColor(kBlack);
	Nneg_uncorr1_3->Draw("Psame");

	Nneg_corr1_3->Rebin(10);
	Nneg_corr1_3->SetMarkerStyle(20);
	Nneg_corr1_3->SetMarkerColor(kRed);
	Nneg_corr1_3->SetLineColor(kRed);
	Nneg_corr1_3->Draw("Psame");

	Nneg_uncorr2_3->Rebin(10);
	Nneg_uncorr2_3->SetMarkerStyle(24);
	Nneg_uncorr2_3->SetMarkerColor(kBlack);
	Nneg_uncorr2_3->SetLineColor(kBlack);
	Nneg_uncorr2_3->Draw("Psame");

	Nneg_corr2_3->Rebin(10);
	Nneg_corr2_3->SetMarkerStyle(24);
	Nneg_corr2_3->SetMarkerColor(kRed);
	Nneg_corr2_3->SetLineColor(kRed);
	Nneg_corr2_3->Draw("Psame");

	latex5->Draw("same");

	c1->cd(3);
	gPad->SetLeftMargin(0.20);
	gPad->SetBottomMargin(0.20);
	gPad->SetTopMargin(0.06);
	gPad->SetTicks();

	base2->Draw();
	Ach_uncorr1_3->Rebin(100);
	Ach_uncorr1_3->SetMarkerStyle(20);
	Ach_uncorr1_3->SetMarkerColor(kBlack);
	Ach_uncorr1_3->SetLineColor(kBlack);
	Ach_uncorr1_3->Draw("Psame");

	Ach_corr1_3->Rebin(100);
	Ach_corr1_3->SetMarkerStyle(20);
	Ach_corr1_3->SetMarkerColor(kRed);
	Ach_corr1_3->SetLineColor(kRed);
	Ach_corr1_3->Draw("Psame");

	Ach_uncorr2_3->Rebin(100);
	Ach_uncorr2_3->SetMarkerStyle(24);
	Ach_uncorr2_3->SetMarkerColor(kBlack);
	Ach_uncorr2_3->SetLineColor(kBlack);
	Ach_uncorr2_3->Draw("Psame");

	Ach_corr2_3->Rebin(100);
	Ach_corr2_3->SetMarkerStyle(24);
	Ach_corr2_3->SetMarkerColor(kRed);
	Ach_corr2_3->SetLineColor(kRed);
	Ach_corr2_3->Draw("Psame");

	Ach_corr1_3->Fit("pol1");
    TF1 * myFunc1 = Ach_corr1_3->GetFunction("pol1");
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

	Ach_corr2_3->Fit("pol1");
    TF1 * myFunc2 = Ach_corr2_3->GetFunction("pol1");
    myFunc2->SetLineStyle(2);
    myFunc2->SetLineColor(kBlue);
    double intersect_1 = myFunc2->GetParameter(0);
    double intersect_1_error = myFunc2->GetParError(0);
    double slope_1 = myFunc2->GetParameter(1);
    double slope_1_error = myFunc2->GetParError(1);

    TLatex* latex3 = new TLatex(0.21, 0.75, Form("HIJING slope: %.6f +/- %.6f",slope_1, slope_1_error ));
    latex3->SetNDC();
    latex3->SetTextSize(16);
    latex3->SetTextFont(43);
    latex3->SetTextColor(kBlue);
    latex3->Draw("same");

    TLatex* latex4 = new TLatex(0.21, 0.7, Form("HIJING intersect: %.6f +/- %.6f",intersect_1, intersect_1_error ));
    latex4->SetNDC();
    latex4->SetTextSize(16);
    latex4->SetTextFont(43);
    latex4->SetTextColor(kBlue);
    latex4->Draw("same");


    TLatex* latex33 = new TLatex(0.21, 0.65, Form("EPOS Corr-F: %.3f", Ach_corr1[0]->GetCorrelationFactor() ));
    latex33->SetNDC();
    latex33->SetTextSize(16);
    latex33->SetTextFont(43);
    latex33->SetTextColor(kBlue);
    latex33->Draw("same");

    TLatex* latex44 = new TLatex(0.21, 0.6, Form("HIJING Corr-F: %.3f",Ach_corr2[0]->GetCorrelationFactor() ));
    latex44->SetNDC();
    latex44->SetTextSize(16);
    latex44->SetTextFont(43);
    latex44->SetTextColor(kBlue);
    latex44->Draw("same");
    

	// c1->cd(4);
	// gPad->SetLeftMargin(0.20);
	// gPad->SetBottomMargin(0.13);
	// gPad->SetTopMargin(0.06);
	// gPad->SetTicks();

	// base1->Draw();
	// Npos_uncorr2_3->Rebin(10);
	// Npos_uncorr2_3->SetMarkerStyle(20);
	// Npos_uncorr2_3->SetMarkerColor(kBlack);
	// Npos_uncorr2_3->SetLineColor(kBlack);
	// Npos_uncorr2_3->Draw("Psame");

	// Npos_corr2_3->Rebin(10);
	// Npos_corr2_3->SetMarkerStyle(20);
	// Npos_corr2_3->SetMarkerColor(kRed);
	// Npos_corr2_3->SetLineColor(kRed);
	// Npos_corr2_3->Draw("Psame");

	// latex6->Draw("same");

	// c1->cd(5);
	// gPad->SetLeftMargin(0.20);
	// gPad->SetBottomMargin(0.13);
	// gPad->SetTopMargin(0.06);
	// gPad->SetTicks();

	// base11->Draw();
	// Nneg_uncorr2_3->Rebin(10);
	// Nneg_uncorr2_3->SetMarkerStyle(20);
	// Nneg_uncorr2_3->SetMarkerColor(kBlack);
	// Nneg_uncorr2_3->SetLineColor(kBlack);
	// Nneg_uncorr2_3->Draw("Psame");

	// Nneg_corr2_3->Rebin(10);
	// Nneg_corr2_3->SetMarkerStyle(20);
	// Nneg_corr2_3->SetMarkerColor(kRed);
	// Nneg_corr2_3->SetLineColor(kRed);
	// Nneg_corr2_3->Draw("Psame");

	// latex6->Draw("same");

	// c1->cd(6);
	// gPad->SetLeftMargin(0.20);
	// gPad->SetBottomMargin(0.13);
	// gPad->SetTopMargin(0.06);
	// gPad->SetTicks();

	// base2->Draw();
	// Ach_uncorr2_3->Rebin(100);
	// Ach_uncorr2_3->SetMarkerStyle(20);
	// Ach_uncorr2_3->SetMarkerColor(kBlack);
	// Ach_uncorr2_3->SetLineColor(kBlack);
	// Ach_uncorr2_3->Draw("Psame");

	// Ach_corr2_3->Rebin(100);
	// Ach_corr2_3->SetMarkerStyle(20);
	// Ach_corr2_3->SetMarkerColor(kRed);
	// Ach_corr2_3->SetLineColor(kRed);
	// Ach_corr2_3->Draw("Psame");
	
	// Ach_corr2_3->Fit("pol1");
 //    TF1 * myFunc2 = Ach_corr2_3->GetFunction("pol1");
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

	TLegend *w10 = new TLegend(0.4,0.24,0.75,0.4);
    w10->SetLineColor(kWhite);
    w10->SetFillColor(0);
    w10->SetTextSize(18);
    w10->SetTextFont(43);
    w10->AddEntry(Ach_uncorr1_3, "EPOS uncorrected", "P");
    w10->AddEntry(Ach_corr1_3, "EPOS corrected", "P");
    w10->AddEntry(Ach_uncorr2_3, "HIJING uncorrected", "P");
    w10->AddEntry(Ach_corr2_3, "HIJING corrected", "P");
    w10->Draw("same");

    latex6->Draw("same");

    //c1->Print("../figures/Ach_RECO_vs_GEN_1.pdf");
    //c1->Print("../figures/Ach_RECO_vs_GEN_1.gif");




}