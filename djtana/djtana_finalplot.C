#include "djtana.h"
#include "djtana_finalplot.h"
#include "../../theory/theory.h"

Float_t ypaddivP = 1.2/2, yPullpaddivP = 0.6*0.8/4, yShpaddivP = 0.6*0.8/4, yPypaddivP = 0.8*0.8/4;
Float_t ypaddiv = 2./3, yPullpaddiv = 1-ypaddiv;
void djtana_finalplot(TString inputnamePP, TString inputnamePbPb, TString inputnameRatio, TString outputname,
                      Float_t jetptmin, Float_t jetptmax, Float_t jetetamin, Float_t jetetamax,
                      Int_t plotPYTHIA=0, TString inputnamePYTHIA="",
                      Bool_t verbose=false)
{
  xjjroot::setgstyle(1);
  gStyle->SetLineWidth(2);

  void setup_hempty(TH2F* hempty, TH2F* hemptyPull);
  void setup_hempty_P(TH2F* hempty, TH2F* hemptyPull, TH2F* hemptyPy, TH2F* hemptySh);
  void setup_hempty_Psep(TH2F* hempty, TH2F* hemptyPull, TH2F* hemptyPy, TH2F* hemptysep, TH2F* hemptyPullsep);
  void set_yaxisrange(Float_t& yaxismin, Float_t& yaxismax, int i);
  void verbose_bincontent(TH1F* hpp, TH1F* hPbPb, TH1F* hratio, Float_t jetptmin, Float_t jetptmax, int i);
  void verbose_binerror();

  TFile* infhistPP = new TFile(Form("%s.root",inputnamePP.Data()));
  if(!infhistPP->IsOpen()) return;
  if(gethists(infhistPP, "saveratiopp")) return;
  TFile* infhistPbPb = new TFile(Form("%s.root",inputnamePbPb.Data()));
  if(!infhistPbPb->IsOpen()) return;
  if(gethists(infhistPbPb, "saveratiopbpb")) return;
  TFile* infhistRatio = new TFile(Form("%s.root",inputnameRatio.Data()));
  if(!infhistRatio->IsOpen()) return;
  if(gethists(infhistRatio, "plotratio")) return;

  // prepare sherpa
  djt::theoryCCNU* tccnu = new djt::theoryCCNU("../../theory/1906.01499_data_0619.dat");

  // prepare th1 and systematics
  if(djtsyst::initsyst(jetptmin, jetptmax)) return;
  finalplot::preparehist(plotPYTHIA, inputnamePYTHIA);

  // set up ploting style
  for(int i=0;i<nPtBins;i++)
    {
      for(int l=0;l<2;l++)
        {
          xjjroot::setthgrstyle(finalplot::hPbPbdndr(i, l), fmcolor[1], fmstyle[1], 1.2, fmcolor[1], 1, 2, -1, -1, -1);
          xjjroot::setthgrstyle(finalplot::gPbPbdndr(i, l), fmcolor[1], fmstyle[1], 1.2, 0, 1, 1, ffcolor[1], 0.7, 1001);
          xjjroot::setthgrstyle(finalplot::hppdndr(i, l), fmcolor[0], fmstyle[0], 1.2, fmcolor[0], 1, 2, -1, -1, -1);
          xjjroot::setthgrstyle(finalplot::gppdndr(i, l), fmcolor[0], fmstyle[0], 1.2, 0, 1, 1, ffcolor[0], 0.7, 1001);
          xjjroot::setthgrstyle(finalplot::hratio(i, l), kBlack, fmstyle[1], 1.2, kBlack, 1, 2, -1, -1, -1);
          xjjroot::setthgrstyle(finalplot::gratio(i, l), kBlack, fmstyle[1], 1.2, 0, 1, 1, kGray+1, 0.7, 1001);
        }
      xjjroot::setthgrstyle(finalplot::hPbPbdndr(i, 0), kViolet-7, fmstyle[1]+4, 1.2, kViolet-7, 1, 2, -1, -1, -1);
      xjjroot::setthgrstyle(finalplot::hppdndr(i, 0), kViolet-7, fmstyle[0]+4, 1.2, kViolet-7, 1, 2, -1, -1, -1);
      xjjroot::setthgrstyle(finalplot::hratio(i, 0), kViolet-7, fmstyle[1]+4, 1.2, kViolet-7, 1, 2, -1, -1, -1);
      if(plotPYTHIA)
        {
          xjjroot::setthgrstyle(finalplot::hpythiadndr(i), fmcolor[2], fmstyle[2], 1.2, fmcolor[2], 1, 2, -1, -1, -1);
          xjjroot::setthgrstyle(finalplot::gpythiadndr(i), fmcolor[2], fmstyle[2], 1.2, 0, 1, 1, ffcolor[2], 0.7, 1001);
          xjjroot::setthgrstyle(finalplot::hpythiatopp(i), fmcolor[2], fmstyle[2], 1.2, fmcolor[2], 1, 2, -1, -1, -1);
          xjjroot::setthgrstyle(finalplot::gpythiatopp(i), fmcolor[2], fmstyle[2], 1.2, 0, 1, 1, ffcolor[2], 0.7, 1001);
        }
    }

  // prepare legends
  TString texjetpt = jetptmax<999?Form("%s < |p_{T}^{jet}| < %s GeV/c",xjjc::number_remove_zero(jetptmin).c_str(),xjjc::number_remove_zero(jetptmax).c_str()):Form("|p_{T}^{jet}| > %s GeV/c",xjjc::number_remove_zero(jetptmin).c_str());
  std::vector<TString> vectex =
    {
      "|y^{D}| < 2",
      texjetpt,
      jetetamin<=0?Form("|#eta^{jet}| < %s",xjjc::number_remove_zero(jetetamax).c_str()):Form("%s < |#eta^{jet}| < %s",xjjc::number_remove_zero(jetetamin).c_str(),xjjc::number_remove_zero(jetetamax).c_str()),
    };
  Float_t yaxismin, yaxismax;

  //-------------------------------------------- Publish plots -------------------------------------------- //

  for(int i=0;i<nPtBins;i++)
    {
      set_yaxisrange(yaxismin, yaxismax, i);
      TH2F* hempty = new TH2F("hempty", ";r;#frac{1}{N_{JD}} #frac{dN_{JD}}{dr}", 5, drBins[0], drBins[nDrBins], 10, yaxismin, yaxismax);
      // TH2F* hemptyPull = new TH2F("hemptyPull", ";r;#frac{PbPb}{pp}", 5, drBins[0], drBins[nDrBins], 10, -0.4, 2.8);
      TH2F* hemptyPull = new TH2F("hemptyPull", ";r;#frac{PbPb}{pp}", 5, drBins[0], drBins[nDrBins], 10, 0.2, 2.8);
      TH2F* hemptySh = new TH2F("hemptySh", ";r;#frac{SHERPA}{pp}", 5, drBins[0], drBins[nDrBins], 10, -0.4, 2.4);
      TH2F* hemptyPy = new TH2F("hemptyPy", ";r;#frac{PYTHIA}{pp}", 5, drBins[0], drBins[nDrBins], 10, 0, 2.6);
      setup_hempty_P(hempty, hemptyPull, hemptyPy, hemptySh);
      TString texpt = ptBins[i+1]>900?Form("p_{T}^{D} > %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str()):Form("%s < p_{T}^{D} < %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str(),xjjc::number_remove_zero(ptBins[i+1]).c_str());
      vectex.insert(vectex.begin(),texpt);

      TCanvas* c = new TCanvas("c", "", 600, 800);
      TPad* pXsec = new TPad("pXsec", "", 0, 1-ypaddivP, 1, 1);
      pXsec->SetMargin(xjjroot::margin_pad_left, xjjroot::margin_pad_right, 0, xjjroot::margin_pad_top);
      pXsec->Draw();
      pXsec->cd();
      pXsec->SetLogy();
      hempty->Draw();
      TLegend* leg = new TLegend(0.24, 0.27-(2+plotPYTHIA)*0.065, 0.70, 0.27);
      xjjroot::setleg(leg, 0.050);

      finalplot::gPbPbdndr(i)->Draw("2 same");
      finalplot::hPbPbdndr(i)->Draw("pe same");
      leg->AddEntry(finalplot::gPbPbdndr(i), fleg[1], "pf");
      finalplot::gppdndr(i)->Draw("2 same");
      finalplot::hppdndr(i)->Draw("pe same");
      leg->AddEntry(finalplot::gppdndr(i), fleg[0], "pf");
      if(plotPYTHIA)
        {
          finalplot::gpythiadndr(i)->Draw("2 same");
          finalplot::hpythiadndr(i)->Draw("pe same");
          leg->AddEntry(finalplot::gpythiadndr(i), fleg[2], "p");
        }
      xjjroot::drawtex((i?0.62:0.65)+0.01, (i?0.45:0.05)+0.05+0.054, "CCNU", 0.047, 11);
      tccnu->draw(0, i, 0.047, (i?0.62:0.65), (i?0.45:0.05));
      tccnu->draw(1, i, 0.047, (i?0.62:0.65), (i?0.45:0.05)+0.047);

      xjjroot::drawtex(0.22, 0.81, "CMS", 0.075, 11, 62);
      xjjroot::drawtex(0.22, 0.86-0.07, "D^{0} + jet", 0.068, 13, 62);
      xjjroot::drawtex(0.96, 0.915, "27.4 pb^{-1} (5.02 TeV pp) + 404 #mub^{-1} (5.02 TeV PbPb)", 0.046, 31);
      Float_t texxpos = 0.62, texypos = 0.84, texdypos = 0.070;
      texypos += texdypos;
      for(std::vector<TString>::const_iterator it=vectex.begin(); it!=vectex.end(); it++)
        xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), *it, 0.050);
      leg->Draw();

      c->cd();
      TPad* pPull = new TPad("pPull", "", 0, 1-ypaddivP-yPullpaddivP, 1, 1-ypaddivP);
      pPull->SetMargin(xjjroot::margin_pad_left, xjjroot::margin_pad_right, 0, 0); 
      pPull->Draw();
      pPull->cd();
      hemptyPull->Draw();
      xjjroot::drawline(drBins[0], 1, drBins[nDrBins], 1, kBlack, 1, 2);
      finalplot::gratio(i)->Draw("2 same");
      finalplot::hratio(i)->Draw("pe same");

      tccnu->draw(2, i, 0.23, 0.23, 0.62, -0.9);

      c->cd();
      TPad* pSh = new TPad("pSh", "", 0, yPypaddivP, 1, yPypaddivP+yShpaddivP);
      pSh->SetMargin(xjjroot::margin_pad_left, xjjroot::margin_pad_right, 0, 0);
      pSh->Draw();
      pSh->cd();
      hemptySh->Draw();
      xjjroot::drawline(drBins[0], 1, drBins[nDrBins], 1, kBlack, 1, 2);
      tccnu->drawratiopp(i, ahSignalRsubMeP[0][i]);

      c->cd();
      TPad* pPy = new TPad("pPy", "", 0, 0, 1, yPypaddivP);
      pPy->SetMargin(xjjroot::margin_pad_left, xjjroot::margin_pad_right, xjjroot::margin_pad_bottom*1.8, 0);
      pPy->Draw();
      pPy->cd();
      hemptyPy->Draw();
      xjjroot::drawline(drBins[0], 1, drBins[nDrBins], 1, kBlack, 1, 2);
      finalplot::gpythiatopp(i)->Draw("2 same");
      finalplot::hpythiatopp(i)->Draw("pe same");

      if(jetetamin<0.3) c->SaveAs(Form("plotfinal/cfinal_xsec_%s_r_pt_%s_%s%s_pythia.pdf",outputname.Data(),xjjc::number_to_string(ptBins[i]).c_str(),xjjc::number_to_string(ptBins[i+1]).c_str(),tname[lme].Data()));
      pXsec->cd();
      xjjroot::drawtex(0.35, 0.81, "Preliminary", 0.054, 11, 52);
      if(jetetamin<0.3) c->SaveAs(Form("plotfinal/cfinal_xsec_%s_r_pt_%s_%s%s_pythia_pre.pdf",outputname.Data(),xjjc::number_to_string(ptBins[i]).c_str(),xjjc::number_to_string(ptBins[i+1]).c_str(),tname[lme].Data()));

      delete leg;
      delete hemptyPy;
      delete hemptySh;
      delete hemptyPull;
      delete hempty;
      delete pPy;
      delete pPull;
      delete pXsec;
      delete c;

      vectex.erase(vectex.begin());
    }

  // Separate panels

  for(int i=0;i<nPtBins;i++)
    {
      set_yaxisrange(yaxismin, yaxismax, i);
      TH2F* hempty = new TH2F("hempty", ";r;#frac{1}{N_{JD}} #frac{dN_{JD}}{dr}", 5, drBins[0], drBins[nDrBins], 10, yaxismin, yaxismax);
      TH2F* hemptysep = new TH2F("hemptysep", ";r;#frac{1}{N_{JD}} #frac{dN_{JD}}{dr}", 5, drBins[0], drBins[nDrBins], 10, yaxismin, yaxismax);
      TH2F* hemptyPull = new TH2F("hemptyPull", ";r;#frac{PbPb}{pp}", 5, drBins[0], drBins[nDrBins], 10, -0.2, 3.2);
      TH2F* hemptyPullsep = new TH2F("hemptyPullsep", ";r;#frac{1}{N_{JD}} #frac{dN_{JD}}{dr} (#frac{PbPb}{pp})", 5, drBins[0], drBins[nDrBins], 10, 0, 3.5);
      TH2F* hemptyPy = new TH2F("hemptyPy", ";r;#frac{PYTHIA}{pp}", 5, drBins[0], drBins[nDrBins], 10, -0.2, 3.2);
      setup_hempty_Psep(hempty, hemptyPull, hemptyPy, hemptysep, hemptyPullsep);
      TString texpt = ptBins[i+1]>900?Form("p_{T}^{D} > %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str()):Form("%s < p_{T}^{D} < %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str(),xjjc::number_remove_zero(ptBins[i+1]).c_str());
      vectex.insert(vectex.begin(),texpt);
      std::vector<TString> vectexD = {texpt, "|y^{D}| < 2"};
      std::vector<TString> vectexJ = {texjetpt, jetetamin<=0?Form("|#eta^{jet}| < %s",xjjc::number_remove_zero(jetetamax).c_str()):Form("%s < |#eta^{jet}| < %s",xjjc::number_remove_zero(jetetamin).c_str(),xjjc::number_remove_zero(jetetamax).c_str())};

      // dNdr only
      TCanvas* conly = new TCanvas("conly", "", 600, 600);
      conly->cd();
      TPad* ponly = new TPad("ponly", "", 0, 0, 1, 1);
      ponly->SetMargin(xjjroot::margin_pad_left, xjjroot::margin_pad_right, xjjroot::margin_pad_bottom*0.7, xjjroot::margin_pad_top);
      ponly->SetLogy();
      ponly->Draw();
      ponly->cd();
      hemptysep->Draw();
      TLegend* legonly = new TLegend(0.24, 0.30-2*0.065, 0.70, 0.30);
      xjjroot::setleg(legonly, 0.045);
      finalplot::gPbPbdndr(i)->Draw("2 same");
      finalplot::hPbPbdndr(i)->Draw("pe same");
      legonly->AddEntry(finalplot::gPbPbdndr(i), fleg[1], "pf");
      finalplot::gppdndr(i)->Draw("2 same");
      finalplot::hppdndr(i)->Draw("pe same");
      legonly->AddEntry(finalplot::gppdndr(i), fleg[0], "pf");
      xjjroot::drawtex((i?0.62:0.65)+0.01, (i?0.51:0.19)-0.05+0.044+0.055, "CCNU", 0.042, 11);
      tccnu->draw(0, i, 0.042, (i?0.62:0.65), (i?0.51:0.19)-0.05);
      tccnu->draw(1, i, 0.042, (i?0.62:0.65), (i?0.51:0.19)-0.05+0.044);
      xjjroot::drawtex(0.22, 0.827, "CMS", 0.062, 11, 62);
      // xjjroot::drawtex(0.22, 0.785, "Supplementary", 0.042, 11, 52);
      xjjroot::drawtex(0.22, 0.785, "Preliminary", 0.042, 11, 52);
      xjjroot::drawtex(0.22, 0.83-0.07-0.046, "D^{0} + jet", 0.062, 11, 62);
      xjjroot::drawtex(0.96, 0.92, "27.4 pb^{-1} (5.02 TeV pp) + 404 #mub^{-1} (5.02 TeV PbPb)", 0.037, 31);
      Float_t texxpos = 0.62, texypos = 0.84, texdypos = 0.070;
      texypos += texdypos;
      for(std::vector<TString>::const_iterator it=vectex.begin(); it!=vectex.end(); it++)
        xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), *it, 0.043);
      legonly->Draw();
      gPad->RedrawAxis();

      if(jetetamin<0.3) conly->SaveAs(Form("plotfinal/cfinal_xsec_%s_r_pt_%s_%s%s_dNdronly.pdf",outputname.Data(),xjjc::number_to_string(ptBins[i]).c_str(),xjjc::number_to_string(ptBins[i+1]).c_str(),tname[lme].Data()));

      // ratio only
      TCanvas* cratioonly = new TCanvas("cratioonly", "", 600, 600);
      cratioonly->cd();
      TPad* pratioonly = new TPad("pratioonly", "", 0, 0, 1, 1);
      pratioonly->SetMargin(xjjroot::margin_pad_left, xjjroot::margin_pad_right, xjjroot::margin_pad_bottom*0.7, xjjroot::margin_pad_top);
      pratioonly->Draw();
      pratioonly->cd();
      hemptyPullsep->Draw();
      xjjroot::drawline(drBins[0], 1, drBins[nDrBins], 1, kBlack, 1, 2);
      finalplot::gratio(i)->Draw("2 same");
      finalplot::hratio(i)->Draw("pe same");
      tccnu->draw(2, i, 0.045, 0.62, (i?0.67:0.20));
      xjjroot::drawtex(0.22, 0.827, "CMS", 0.062, 11, 62);
      // xjjroot::drawtex(0.35, 0.827, "Preliminary", 0.042, 11, 52);
      // xjjroot::drawtex(0.22, 0.785, "Supplementary", 0.042, 11, 52);
      xjjroot::drawtex(0.22, 0.785, "Preliminary", 0.042, 11, 52);
      xjjroot::drawtex(0.22, 0.83-0.07-0.046, "D^{0} + jet", 0.062, 11, 62);
      xjjroot::drawtex(0.96, 0.92, "27.4 pb^{-1} (5.02 TeV pp) + 404 #mub^{-1} (5.02 TeV PbPb)", 0.037, 31);
      texxpos = 0.62, texypos = 0.84, texdypos = 0.070;
      texypos += texdypos;
      for(std::vector<TString>::const_iterator it=vectexD.begin(); it!=vectexD.end(); it++)
        xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), *it, 0.043);
      texxpos = 0.22, texypos = 0.64, texdypos = 0.070;
      texypos += texdypos;
      for(std::vector<TString>::const_iterator it=vectexJ.begin(); it!=vectexJ.end(); it++)
        xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), *it, 0.043);
      gPad->RedrawAxis();

      if(jetetamin<0.3) cratioonly->SaveAs(Form("plotfinal/cfinal_xsec_%s_r_pt_%s_%s%s_ratioonly.pdf",outputname.Data(),xjjc::number_to_string(ptBins[i]).c_str(),xjjc::number_to_string(ptBins[i+1]).c_str(),tname[lme].Data()));

      // dNdr + PbPb/pp
      TCanvas* cdNdrratio = new TCanvas("cdNdrratio", "", 600, 700);
      cdNdrratio->cd();
      TPad* pdNdr = new TPad("pdNdr", "", 0, 0.4, 1, 1);
      pdNdr->SetMargin(xjjroot::margin_pad_left, xjjroot::margin_pad_right, 0, xjjroot::margin_pad_top);
      pdNdr->SetLogy();
      pdNdr->Draw();
      pdNdr->cd();
      hempty->Draw();
      TLegend* legdNdrratio = new TLegend(0.24, 0.29-2*0.067, 0.70, 0.29);
      xjjroot::setleg(legdNdrratio, 0.062);
      finalplot::gPbPbdndr(i)->Draw("2 same");
      finalplot::hPbPbdndr(i)->Draw("pe same");
      legdNdrratio->AddEntry(finalplot::gPbPbdndr(i), fleg[1], "pf");
      finalplot::gppdndr(i)->Draw("2 same");
      finalplot::hppdndr(i)->Draw("pe same");
      legdNdrratio->AddEntry(finalplot::gppdndr(i), fleg[0], "pf");
      xjjroot::drawtex((i?0.62:0.65)+0.01, (i?0.42:0.06)-0.02+0.05+0.06, "CCNU", 0.050, 11);
      tccnu->draw(0, i, 0.050, (i?0.62:0.65), (i?0.42:0.06)-0.02);
      tccnu->draw(1, i, 0.050, (i?0.62:0.65), (i?0.42:0.06)-0.02+0.05);
      xjjroot::drawtex(0.22, 0.81, "CMS", 0.075, 11, 62);
      // xjjroot::drawtex(0.335, 0.81, "Preliminary", 0.050, 11, 52);
      // xjjroot::drawtex(0.22, 0.76, "Supplementary", 0.050, 11, 52);
      xjjroot::drawtex(0.22, 0.76, "Preliminary", 0.050, 11, 52);
      xjjroot::drawtex(0.22, 0.76-0.075, "D^{0} + jet", 0.062, 11, 62);
      xjjroot::drawtex(0.96, 0.92, "27.4 pb^{-1} (5.02 TeV pp) + 404 #mub^{-1} (5.02 TeV PbPb)", 0.050, 31);
      texxpos = 0.62, texypos = 0.82, texdypos = 0.079;
      texypos += texdypos;
      for(std::vector<TString>::const_iterator it=vectex.begin(); it!=vectex.end(); it++)
        xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), *it, 0.057);
      legdNdrratio->Draw();
      gPad->RedrawAxis();
      cdNdrratio->cd();
      TPad* pratio = new TPad("pratio", "", 0, 0, 1, 0.4);
      pratio->SetMargin(xjjroot::margin_pad_left, xjjroot::margin_pad_right, xjjroot::margin_pad_bottom, 0);
      pratio->Draw();
      pratio->cd();
      hemptyPull->Draw();
      xjjroot::drawline(drBins[0], 1, drBins[nDrBins], 1, kBlack, 1, 2);
      finalplot::gratio(i)->Draw("2 same");
      finalplot::hratio(i)->Draw("pe same");
      tccnu->draw(2, i, 0.1, 0.20, 0.70);
      gPad->RedrawAxis();

      if(jetetamin<0.3) cdNdrratio->SaveAs(Form("plotfinal/cfinal_xsec_%s_r_pt_%s_%s%s_dNdrratio.pdf",outputname.Data(),xjjc::number_to_string(ptBins[i]).c_str(),xjjc::number_to_string(ptBins[i+1]).c_str(),tname[lme].Data()));

      // dNdr + pp/pythia
      TCanvas* cdNdrpythia = new TCanvas("cdNdrpythia", "", 600, 700);
      cdNdrpythia->cd();
      pdNdr->Draw();
      pdNdr->cd();
      hempty->Draw();
      TLegend* legdNdrpythia = new TLegend(0.24, 0.29-3*0.067, 0.70, 0.29);
      xjjroot::setleg(legdNdrpythia, 0.062);
      finalplot::gPbPbdndr(i)->Draw("2 same");
      finalplot::hPbPbdndr(i)->Draw("pe same");
      legdNdrpythia->AddEntry(finalplot::gPbPbdndr(i), fleg[1], "pf");
      finalplot::gppdndr(i)->Draw("2 same");
      finalplot::hppdndr(i)->Draw("pe same");
      legdNdrpythia->AddEntry(finalplot::gppdndr(i), fleg[0], "pf");
      finalplot::gpythiadndr(i)->Draw("2 same");
      finalplot::hpythiadndr(i)->Draw("pe same");
      legdNdrpythia->AddEntry(finalplot::gpythiadndr(i), fleg[2], "p");
      xjjroot::drawtex((i?0.62:0.65)+0.01, (i?0.42:0.06+0.05)-0.02+0.06, "CCNU", 0.050, 11);
      tccnu->draw(0, i, 0.050, (i?0.62:0.65), (i?0.42:0.06+0.05)-0.02);
      xjjroot::drawtex(0.22, 0.81, "CMS", 0.075, 11, 62);
      // xjjroot::drawtex(0.335, 0.81, "Preliminary", 0.050, 11, 52);
      // xjjroot::drawtex(0.22, 0.76, "Supplementary", 0.050, 11, 52);
      xjjroot::drawtex(0.22, 0.76, "Preliminary", 0.050, 11, 52);
      xjjroot::drawtex(0.22, 0.76-0.075, "D^{0} + jet", 0.062, 11, 62);
      xjjroot::drawtex(0.96, 0.92, "27.4 pb^{-1} (5.02 TeV pp) + 404 #mub^{-1} (5.02 TeV PbPb)", 0.050, 31);
      texxpos = 0.62, texypos = 0.82, texdypos = 0.079;
      texypos += texdypos;
      for(std::vector<TString>::const_iterator it=vectex.begin(); it!=vectex.end(); it++)
        xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), *it, 0.057);
      legdNdrpythia->Draw();
      gPad->RedrawAxis();
      cdNdrpythia->cd();
      pratio->Draw();
      pratio->cd();
      hemptyPy->Draw();
      xjjroot::drawline(drBins[0], 1, drBins[nDrBins], 1, kBlack, 1, 2);
      finalplot::gpythiatopp(i)->Draw("2 same");
      tccnu->drawratiopp(i, ahSignalRsubMeP[0][i]);
      finalplot::hpythiatopp(i)->Draw("pe same");
      gPad->RedrawAxis();

      if(jetetamin<0.3) cdNdrpythia->SaveAs(Form("plotfinal/cfinal_xsec_%s_r_pt_%s_%s%s_dNdrpythia.pdf",outputname.Data(),xjjc::number_to_string(ptBins[i]).c_str(),xjjc::number_to_string(ptBins[i+1]).c_str(),tname[lme].Data()));

      delete hemptysep;
      delete hempty;
      delete hemptyPy;
      delete hemptyPull;
      delete hemptyPullsep;
      delete pratio;
      delete pdNdr;
      delete pratioonly;
      delete ponly;
      delete cdNdrpythia;
      delete cdNdrratio;
      delete cratioonly;
      delete conly;

      vectex.erase(vectex.begin());

    }

  if(verbose && jetetamin<=0 && jetetamax>=1.6)
    {
      for(int i=0;i<nPtBins;i++)
        {
          verbose_bincontent((hSignalXsubP.at(1))[0*nPtBins+i], (hSignalXsubP.at(1))[1*nPtBins+i], (hSignalXsubRatio.at(1))[i],
                             jetptmin, jetptmax, i);
        }
    }
  if(verbose)
    {
      verbose_binerror();
      djtsyst::printsysts();
    }
}

int main(int argc, char* argv[])
{
  if(argc == 11)
    {
      djtana_finalplot(argv[1], argv[2], argv[3], argv[4], atof(argv[5]), atof(argv[6]), atof(argv[7]), atof(argv[8]), atoi(argv[9]), argv[10]);
      return 0;
    }
  if(argc == 9)
    {
      djtana_finalplot(argv[1], argv[2], argv[3], argv[4], atof(argv[5]), atof(argv[6]), atof(argv[7]), atof(argv[8]));
      return 0;
    }
  std::cout<<"error: invalid parameter number - djtana_finalplot"<<std::endl;
  return 1;
}

void setup_hempty(TH2F* hempty, TH2F* hemptyPull)
{
  hempty->GetXaxis()->SetNdivisions(505);
  xjjroot::sethempty(hempty, 0, 0.2);

  hemptyPull->GetXaxis()->SetNdivisions(505);
  hemptyPull->GetYaxis()->SetNdivisions(505);
  xjjroot::sethempty(hemptyPull, -0.5, -0);
  hemptyPull->GetYaxis()->SetTitleSize(hemptyPull->GetYaxis()->GetTitleSize() * (ypaddiv / yPullpaddiv));
  hemptyPull->GetXaxis()->SetTitleSize(hemptyPull->GetXaxis()->GetTitleSize() * (ypaddiv / yPullpaddiv));
  hemptyPull->GetYaxis()->SetLabelSize(hemptyPull->GetYaxis()->GetLabelSize() * (ypaddiv / yPullpaddiv));
  hemptyPull->GetXaxis()->SetLabelSize(hemptyPull->GetXaxis()->GetLabelSize() * (ypaddiv / yPullpaddiv));
  hemptyPull->GetYaxis()->SetTitleOffset(hemptyPull->GetYaxis()->GetTitleOffset() / (ypaddiv / yPullpaddiv));
  hemptyPull->GetXaxis()->SetTitleOffset(hemptyPull->GetXaxis()->GetTitleOffset() / (ypaddiv / yPullpaddiv) *(1+1.8));
  hemptyPull->GetYaxis()->SetLabelOffset(hemptyPull->GetYaxis()->GetLabelOffset() / (ypaddiv / yPullpaddiv) *(1+12));
  hemptyPull->GetXaxis()->SetLabelOffset(hemptyPull->GetXaxis()->GetLabelOffset() / (ypaddiv / yPullpaddiv));
}

void setup_hempty_P(TH2F* hempty, TH2F* hemptyPull, TH2F* hemptyPy, TH2F* hemptySh)
{
  hempty->GetXaxis()->SetNdivisions(505);
  xjjroot::sethempty(hempty, 0, 0.2);

  hemptyPull->GetXaxis()->SetNdivisions(505);
  hemptyPull->GetYaxis()->SetNdivisions(505);
  xjjroot::sethempty(hemptyPull, -0.5, -0);
  hemptyPull->GetYaxis()->SetTitleSize(hemptyPull->GetYaxis()->GetTitleSize() * (ypaddivP / yPullpaddivP));
  hemptyPull->GetXaxis()->SetTitleSize(hemptyPull->GetXaxis()->GetTitleSize() * (ypaddivP / yPullpaddivP));
  hemptyPull->GetYaxis()->SetLabelSize(hemptyPull->GetYaxis()->GetLabelSize() * (ypaddivP / yPullpaddivP));
  hemptyPull->GetXaxis()->SetLabelSize(hemptyPull->GetXaxis()->GetLabelSize() * (ypaddivP / yPullpaddivP));
  hemptyPull->GetYaxis()->SetTitleOffset(hemptyPull->GetYaxis()->GetTitleOffset() / (ypaddivP / yPullpaddivP));
  hemptyPull->GetXaxis()->SetTitleOffset(hemptyPull->GetXaxis()->GetTitleOffset() / (ypaddivP / yPullpaddivP) *(1+1.8));
  hemptyPull->GetYaxis()->SetLabelOffset(hemptyPull->GetYaxis()->GetLabelOffset() / (ypaddivP / yPullpaddivP) *(1+12));
  hemptyPull->GetXaxis()->SetLabelOffset(hemptyPull->GetXaxis()->GetLabelOffset() / (ypaddivP / yPullpaddivP));

  hemptySh->GetXaxis()->SetNdivisions(505);
  hemptySh->GetYaxis()->SetNdivisions(505);
  xjjroot::sethempty(hemptySh, -0.5, -0);
  hemptySh->GetYaxis()->SetTitleSize(hemptySh->GetYaxis()->GetTitleSize() * (ypaddivP / yShpaddivP));
  hemptySh->GetXaxis()->SetTitleSize(hemptySh->GetXaxis()->GetTitleSize() * (ypaddivP / yShpaddivP));
  hemptySh->GetYaxis()->SetLabelSize(hemptySh->GetYaxis()->GetLabelSize() * (ypaddivP / yShpaddivP));
  hemptySh->GetXaxis()->SetLabelSize(hemptySh->GetXaxis()->GetLabelSize() * (ypaddivP / yShpaddivP));
  hemptySh->GetYaxis()->SetTitleOffset(hemptySh->GetYaxis()->GetTitleOffset() / (ypaddivP / yShpaddivP));
  hemptySh->GetXaxis()->SetTitleOffset(hemptySh->GetXaxis()->GetTitleOffset() / (ypaddivP / yShpaddivP) *(1+1.8));
  hemptySh->GetYaxis()->SetLabelOffset(hemptySh->GetYaxis()->GetLabelOffset() / (ypaddivP / yShpaddivP) *(1+12));
  hemptySh->GetXaxis()->SetLabelOffset(hemptySh->GetXaxis()->GetLabelOffset() / (ypaddivP / yShpaddivP));

  hemptyPy->GetXaxis()->SetNdivisions(505);
  hemptyPy->GetYaxis()->SetNdivisions(505);
  xjjroot::sethempty(hemptyPy, -0.5, -0);
  hemptyPy->GetYaxis()->SetTitleSize(hemptyPy->GetYaxis()->GetTitleSize() * (ypaddivP / yPypaddivP));
  hemptyPy->GetXaxis()->SetTitleSize(hemptyPy->GetXaxis()->GetTitleSize() * (ypaddivP / yPypaddivP));
  hemptyPy->GetYaxis()->SetLabelSize(hemptyPy->GetYaxis()->GetLabelSize() * (ypaddivP / yPypaddivP));
  hemptyPy->GetXaxis()->SetLabelSize(hemptyPy->GetXaxis()->GetLabelSize() * (ypaddivP / yPypaddivP));
  hemptyPy->GetYaxis()->SetTitleOffset(hemptyPy->GetYaxis()->GetTitleOffset() / (ypaddivP / yPypaddivP));
  hemptyPy->GetXaxis()->SetTitleOffset(hemptyPy->GetXaxis()->GetTitleOffset() / (ypaddivP / yPypaddivP) *(1+1.8));
  hemptyPy->GetYaxis()->SetLabelOffset(hemptyPy->GetYaxis()->GetLabelOffset() / (ypaddivP / yPypaddivP) *(1+12));
  hemptyPy->GetXaxis()->SetLabelOffset(hemptyPy->GetXaxis()->GetLabelOffset() / (ypaddivP / yPypaddivP));
}

void setup_hempty_Psep(TH2F* hempty, TH2F* hemptyPull, TH2F* hemptyPy, TH2F* hemptysep, TH2F* hemptyPullsep)
{
  hempty->GetXaxis()->SetNdivisions(505);
  xjjroot::sethempty(hempty, 0, -0.1);
  hempty->GetYaxis()->SetTitleSize(hempty->GetYaxis()->GetTitleSize() * 1.1);
  hempty->GetXaxis()->SetTitleSize(hempty->GetXaxis()->GetTitleSize() * 1.1);
  hempty->GetYaxis()->SetLabelSize(hempty->GetYaxis()->GetLabelSize() * 1.1);
  hempty->GetXaxis()->SetLabelSize(hempty->GetXaxis()->GetLabelSize() * 1.1);

  hemptyPull->GetXaxis()->SetNdivisions(505);
  hemptyPull->GetYaxis()->SetNdivisions(505);
  xjjroot::sethempty(hemptyPull, 0, -0.1);
  hemptyPull->GetYaxis()->SetTitleSize(hemptyPull->GetYaxis()->GetTitleSize() * 1.1 * (3./2));
  hemptyPull->GetXaxis()->SetTitleSize(hemptyPull->GetXaxis()->GetTitleSize() * 1.1 * (3./2));
  hemptyPull->GetYaxis()->SetLabelSize(hemptyPull->GetYaxis()->GetLabelSize() * 1.1 * (3./2));
  hemptyPull->GetXaxis()->SetLabelSize(hemptyPull->GetXaxis()->GetLabelSize() * 1.1 * (3./2));
  hemptyPull->GetYaxis()->SetTitleOffset(hemptyPull->GetYaxis()->GetTitleOffset() / (3./2));
  hemptyPull->GetXaxis()->SetTitleOffset(hemptyPull->GetXaxis()->GetTitleOffset() / (3./2));
  hemptyPull->GetYaxis()->SetLabelOffset(hemptyPull->GetYaxis()->GetLabelOffset() / (3./2));
  hemptyPull->GetXaxis()->SetLabelOffset(hemptyPull->GetXaxis()->GetLabelOffset() / (3./2));
  hemptyPull->GetXaxis()->SetTickLength(hemptyPull->GetXaxis()->GetTickLength() * 7. / (3./2));

  hemptyPy->GetXaxis()->SetNdivisions(505);
  hemptyPy->GetYaxis()->SetNdivisions(505);
  xjjroot::sethempty(hemptyPy, 0, -0.1);
  hemptyPy->GetYaxis()->SetTitleSize(hemptyPy->GetYaxis()->GetTitleSize() * 1.1 * (3./2));
  hemptyPy->GetXaxis()->SetTitleSize(hemptyPy->GetXaxis()->GetTitleSize() * 1.1 * (3./2));
  hemptyPy->GetYaxis()->SetLabelSize(hemptyPy->GetYaxis()->GetLabelSize() * 1.1 * (3./2));
  hemptyPy->GetXaxis()->SetLabelSize(hemptyPy->GetXaxis()->GetLabelSize() * 1.1 * (3./2));
  hemptyPy->GetYaxis()->SetTitleOffset(hemptyPy->GetYaxis()->GetTitleOffset() / (3./2));
  hemptyPy->GetXaxis()->SetTitleOffset(hemptyPy->GetXaxis()->GetTitleOffset() / (3./2));
  hemptyPy->GetYaxis()->SetLabelOffset(hemptyPy->GetYaxis()->GetLabelOffset() / (3./2));
  hemptyPy->GetXaxis()->SetLabelOffset(hemptyPy->GetXaxis()->GetLabelOffset() / (3./2));

  hemptysep->GetXaxis()->SetNdivisions(505);
  xjjroot::sethempty(hemptysep, 0, 0.2);
  hemptysep->GetXaxis()->SetTitleOffset(hemptysep->GetXaxis()->GetTitleOffset()*0.7);
  hemptysep->GetYaxis()->SetTitleOffset(hemptysep->GetYaxis()->GetTitleOffset()*0.9);

  hemptyPullsep->GetXaxis()->SetNdivisions(505);
  xjjroot::sethempty(hemptyPullsep, 0, 0.2);
  hemptyPullsep->GetXaxis()->SetTitleOffset(hemptyPullsep->GetXaxis()->GetTitleOffset()*0.7);
  hemptyPullsep->GetYaxis()->SetTitleOffset(hemptyPullsep->GetYaxis()->GetTitleOffset()*0.9);
}

void set_yaxisrange(Float_t& yaxismin, Float_t& yaxismax, int i)
{
  if(nPtBins==1)
    {
      yaxismin = 2.e-2;
      yaxismax = 1.e+2;
    }
  if(nPtBins==2)
    {
      if(i==0) { yaxismin = 8.e-2; yaxismax = 1.e+2; }
      if(i==1) { yaxismin = 2.e-3; yaxismax = 5.e+2; }
    }
}

void verbose_bincontent(TH1F* hpp, TH1F* hPbPb, TH1F* hratio, Float_t jetptmin, Float_t jetptmax, int i)
{
  Float_t normpp=0, normPbPb=0, normratio=0;
  for(int j=0;j<3;j++)
    {
      normpp += hpp->GetBinContent(j+1) * hpp->GetBinWidth(j+1);
      normPbPb += hPbPb->GetBinContent(j+1) * hPbPb->GetBinWidth(j+1);
      normratio += hratio->GetBinContent(j+1) * hratio->GetBinWidth(j+1);
    }

  std::cout<<"\033[0;36mHistogram bin content >>> "<<Form("jet pt (%.0f, %.0f) - D pt (%.0f, %.0f)\033[0m", jetptmin, jetptmax, ptBins[i], ptBins[i+1]);
  std::cout<<"\033[1;36m"<<std::endl;
  std::cout<<std::setiosflags(std::ios::left)<<std::setw(20)<<"r"<<std::setw(10)<<"pp"<<std::setw(10)<<"PbPb"<<std::setw(10)<<"PbPb/pp"<<std::setw(10)<<"ratio"<<std::endl;
  for(int j=0;j<nDrBins;j++)
    {
      std::cout<<std::setiosflags(std::ios::left)<<std::setw(20)<<Form("%.2f - %.2f",drBins[j],drBins[j+1]);
      std::cout<<std::setiosflags(std::ios::left)<<std::setw(10)<<hpp->GetBinContent(j+1);
      std::cout<<std::setiosflags(std::ios::left)<<std::setw(10)<<hPbPb->GetBinContent(j+1);
      std::cout<<std::setiosflags(std::ios::left)<<std::setw(10)<<hPbPb->GetBinContent(j+1)/hpp->GetBinContent(j+1);
      std::cout<<std::setiosflags(std::ios::left)<<std::setw(10)<<hratio->GetBinContent(j+1);
      std::cout<<std::endl;
    }
  std::cout<<std::setiosflags(std::ios::left)<<std::setw(20)<<"Norm"<<std::setw(10)<<normpp<<std::setw(10)<<normPbPb<<std::setw(10)<<normPbPb/normpp<<std::setw(10)<<normratio<<std::endl;

  TH1F* hppw = (TH1F*)hpp->Clone("hppw");
  TH1F* hPbPbw = (TH1F*)hPbPb->Clone("hPbPbw");
  for(int j=0;j<nDrBins;j++)
    {
      hppw->SetBinContent(j+1, hpp->GetBinContent(j+1)*hpp->GetBinWidth(j+1));
      hppw->SetBinError(j+1, hpp->GetBinError(j+1)*hpp->GetBinWidth(j+1));
      hPbPbw->SetBinContent(j+1, hPbPb->GetBinContent(j+1)*hPbPb->GetBinWidth(j+1));
      hPbPbw->SetBinError(j+1, hPbPb->GetBinError(j+1)*hPbPb->GetBinWidth(j+1));
    }
  std::cout<<std::left<<std::setw(20)<<"<r> (pp) = "<<std::setw(10)<<hppw->GetMean()<<" +- "<<std::setw(10)<<hppw->GetMeanError()<<std::endl;
  std::cout<<std::left<<std::setw(20)<<"<r> (PbPb) = "<<std::setw(10)<<hPbPbw->GetMean()<<" +- "<<std::setw(10)<<hPbPbw->GetMeanError()<<std::endl;

  std::cout<<"\033[0m"<<std::endl<<std::endl;
}

void verbose_binerror()
{
  std::cout<<"\e[1;36m"<<std::endl;
  std::cout<<"std::vector<double> vax = {0.025, 0.075, 0.20, 0.40};"<<std::endl;
  std::cout<<"std::vector<double> vaex = {0.025, 0.025, 0.10, 0.10};"<<std::endl;
  std::cout<<"std::vector<double> vayPP = {";
  for(int i=0;i<nPtBins;i++) 
    {
      std::cout<<"{";
      for(int j=0;j<nDrBins;j++) { std::cout<<ahSignalRsubMeP[0][i]->GetBinContent(j+1)<<(j==nDrBins-1?"}":", "); }
      std::cout<<(i==nPtBins-1?"};":",")<<std::endl;
    }
  std::cout<<"std::vector<double> vaeyPPstat = {";
  for(int i=0;i<nPtBins;i++) 
    {
      std::cout<<"{";
      for(int j=0;j<nDrBins;j++) { std::cout<<ahSignalRsubMeP[0][i]->GetBinError(j+1)<<(j==nDrBins-1?"}":", "); }
      std::cout<<(i==nPtBins-1?"};":",")<<std::endl;
    }
  std::cout<<"std::vector<double> vaeyPPsyst = {";
  for(int i=0;i<nPtBins;i++) 
    {
      std::cout<<"{";
      for(int j=0;j<nDrBins;j++) { std::cout<<agSignalRsubMeP[0][i]->GetErrorY(j)<<(j==nDrBins-1?"}":", "); }
      std::cout<<(i==nPtBins-1?"};":",")<<std::endl;
    }
  std::cout<<"std::vector<double> vayPbPb = {";
  for(int i=0;i<nPtBins;i++) 
    {
      std::cout<<"{";
      for(int j=0;j<nDrBins;j++) { std::cout<<ahSignalRsubMeP[1][i]->GetBinContent(j+1)<<(j==nDrBins-1?"}":", "); }
      std::cout<<(i==nPtBins-1?"};":",")<<std::endl;
    }
  std::cout<<"std::vector<double> vaeyPbPbstat = {";
  for(int i=0;i<nPtBins;i++) 
    {
      std::cout<<"{";
      for(int j=0;j<nDrBins;j++) { std::cout<<ahSignalRsubMeP[1][i]->GetBinError(j+1)<<(j==nDrBins-1?"}":", "); }
      std::cout<<(i==nPtBins-1?"};":",")<<std::endl;
    }
  std::cout<<"std::vector<double> vaeyPbPbsyst = {";
  for(int i=0;i<nPtBins;i++) 
    {
      std::cout<<"{";
      for(int j=0;j<nDrBins;j++) { std::cout<<agSignalRsubMeP[1][i]->GetErrorY(j)<<(j==nDrBins-1?"}":", "); }
      std::cout<<(i==nPtBins-1?"};":",")<<std::endl;
    }

  std::cout<<"std::vector<double> vayRatio = {";
  for(int i=0;i<nPtBins;i++) 
    {
      std::cout<<"{";
      for(int j=0;j<nDrBins;j++) { std::cout<<ahSignalRsubRatioMe[i]->GetBinContent(j+1)<<(j==nDrBins-1?"}":", "); }
      std::cout<<(i==nPtBins-1?"};":",")<<std::endl;
    }
  std::cout<<"std::vector<double> vaeyRatiostat = {";
  for(int i=0;i<nPtBins;i++) 
    {
      std::cout<<"{";
      for(int j=0;j<nDrBins;j++) { std::cout<<ahSignalRsubRatioMe[i]->GetBinError(j+1)<<(j==nDrBins-1?"}":", "); }
      std::cout<<(i==nPtBins-1?"};":",")<<std::endl;
    }
  std::cout<<"std::vector<double> vaeyRatiosyst = {";
  for(int i=0;i<nPtBins;i++) 
    {
      std::cout<<"{";
      for(int j=0;j<nDrBins;j++) { std::cout<<agSignalRsubRatioMe[i]->GetErrorY(j)<<(j==nDrBins-1?"}":", "); }
      std::cout<<(i==nPtBins-1?"};":",")<<std::endl;
    }
  std::cout<<"\e[0m"<<std::endl;

}
