#include "djtana.h"

void djtana_plothist(TString inputhistname, TString outputname,
                     TString collisionsyst, Int_t isMC,
                     Float_t jetptmin, Float_t jetptmax, Float_t jetetamin, Float_t jetetamax,
                     Int_t signalMC=1)
{
  if(collisionsyst.Contains("pp")) collisionsyst = "pp";
  int arguerr(TString collisionsyst, Int_t isMC);
  if(arguerr(collisionsyst, isMC)) return;
  gStyle->SetLineWidth(2);
  // gPad->SetFrameLineWidth(2);

  Int_t ispp = collisionsyst=="pp";
  xjjroot::setgstyle();

  TFile* infhist = new TFile(Form("%s.root",inputhistname.Data()));
  if(!infhist->IsOpen()) return;
  if(gethists(infhist, "plothist")) return;

  // preparation
  std::vector<TString> vectex =
    {
      "|y^{D}| < 2",
      // Form("p_{T}^{jet} > %s GeV/c",xjjc::number_remove_zero(jetptmin).c_str()),
      jetetamin<=0?Form("|#eta^{jet}| < %s",xjjc::number_remove_zero(jetetamax).c_str()):Form("%s < |#eta^{jet}| < %s",xjjc::number_remove_zero(jetetamin).c_str(),xjjc::number_remove_zero(jetetamax).c_str()),
    };
  TString texjetpt = jetptmax<999?Form("%s < p_{T}^{jet} < %s GeV/c",xjjc::number_remove_zero(jetptmin).c_str(),xjjc::number_remove_zero(jetptmax).c_str()):Form("p_{T}^{jet} > %s GeV/c",xjjc::number_remove_zero(jetptmin).c_str());
  vectex.push_back(texjetpt);

  // plot
  for(int i=0;i<nPtBins;i++)
    {
      TString texDpt = ptBins[i+1]==999?Form("p_{T}^{D} > %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str()):Form("%s < p_{T}^{D} < %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str(),xjjc::number_remove_zero(ptBins[i+1]).c_str());
      Float_t yaxismax = ahSignalRnorm[0][i]->GetBinContent(1) * 1.e+3;
      Float_t yaxismin = ahSignalRnorm[1][i]->GetBinContent(1) * 1.e-2;
      TCanvas* c = new TCanvas("c", "", 600, 600);
      c->SetLogy();
      TH2F* hempty = new TH2F("hempty", Form(";%s;%s","r","#frac{dN_{JD}}{dr}"), 5, drBins[0], drBins[nDrBins], 10, yaxismin, yaxismax);
      hempty->GetXaxis()->SetNdivisions(505);
      xjjroot::sethempty(hempty, 0, 0.3);
      hempty->Draw();
      Int_t nline = (isMC && signalMC)?1:2;
      TLegend* leg = new TLegend(0.53, 0.88-nline*0.06, 0.85, 0.88);
      xjjroot::setleg(leg, 0.038);
      for(int l=0;l<nRefBins;l++)
        {
          if(l && (isMC && signalMC)) continue;
          xjjroot::setthgrstyle(ahSignalRnorm[l][i], amcolor[i], amstyle[l], l?1.2:1.4, amcolor[i], 1, 2, -1, -1, -1);
          ahSignalRnorm[l][i]->Draw("pe same");
          TString tleg = l==1?"#eta reflection":texDpt;
          leg->AddEntry(ahSignalRnorm[l][i], tleg.Data(), "p");
        }
      xjjroot::drawCMS(collisionsyst);
      Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06;
      texypos += texdypos;
      for(std::vector<TString>::const_iterator it=vectex.begin(); it!=vectex.end(); it++)
        xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), *it);
      leg->Draw();
      if(jetetamin>=0.3) c->SaveAs(Form("plotxsecs/cxsec_%s_%s_pt_%d.pdf","dr",outputname.Data(),i));
      delete leg;
      delete hempty;
      delete c;
    }

  for(int i=0;i<nPtBins;i++)
    {
      TString texDpt = ptBins[i+1]==999?Form("p_{T}^{D} > %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str()):Form("%s < p_{T}^{D} < %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str(),xjjc::number_remove_zero(ptBins[i+1]).c_str());
      Float_t yaxismax = ahSignalRnorm[0][i]->GetBinContent(1) * 1.e+3;
      Float_t yaxismin = (ahSignalRnormMe[0][i]->GetBinContent(1)>0?ahSignalRnormMe[0][i]->GetBinContent(1):ahSignalRnorm[0][i]->GetBinContent(nDrBins)) * 1.e-2;
      TCanvas* c = new TCanvas("c", "", 600, 600);
      c->SetLogy();
      TH2F* hempty = new TH2F("hempty", Form(";%s;%s","r","#frac{dN_{JD}}{dr}"), 5, drBins[0], drBins[nDrBins], 10, yaxismin, yaxismax);
      hempty->GetXaxis()->SetNdivisions(505);
      xjjroot::sethempty(hempty, 0, 0.3);
      hempty->Draw();
      Int_t nline = (isMC && signalMC)?1:4;
      TLegend* leg = new TLegend(0.53, 0.88-nline*0.05, 0.85, 0.88);
      xjjroot::setleg(leg, 0.038);
      ahSignalRnorm[0][i]->Draw("pe same");
      leg->AddEntry(ahSignalRnorm[0][i], texDpt.Data(), "p");
      for(int l=0;l<nMeBins;l++)
        {
          if(isMC && signalMC) continue;
          xjjroot::setthgrstyle(ahSignalRnormMe[l][i], amcolor[i], amstyleMe[l], 1.2, amcolor[i], 1, 2, -1, -1, -1);
          ahSignalRnormMe[l][i]->Draw("pe same");
          leg->AddEntry(ahSignalRnormMe[l][i], tlegMe[l].Data(), "p");
        }
      xjjroot::drawCMS(collisionsyst);
      Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06;
      texypos += texdypos;
      for(std::vector<TString>::const_iterator it=vectex.begin(); it!=vectex.end(); it++)
        xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), *it);
      leg->Draw();
      c->SaveAs(Form("plotxsecs/cxsec_%s_%s_pt_%d_Me.pdf","dr",outputname.Data(),i));
      delete leg;
      delete hempty;
      delete c;
    }

  for(int i=0;i<nPtBins;i++)
    {
      TString texDpt = ptBins[i+1]==999?Form("p_{T}^{D} > %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str()):Form("%s < p_{T}^{D} < %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str(),xjjc::number_remove_zero(ptBins[i+1]).c_str());
      std::vector<TString> vectexD = {texDpt, "|y^{D}| < 2"};
      std::vector<TString> vectexJ = {
        jetetamin<=0?Form("|#eta^{jet}| < %s",xjjc::number_remove_zero(jetetamax).c_str()):Form("%s < |#eta^{jet}| < %s",xjjc::number_remove_zero(jetetamin).c_str(),xjjc::number_remove_zero(jetetamax).c_str()),
        texjetpt
      };
      Float_t yaxismax = ahSignalRnorm[0][i]->GetBinContent(1) * 1.e+4;
      Float_t yaxismin = (ahSignalRnormMe[0][i]->GetBinContent(1)>0?ahSignalRnormMe[0][i]->GetBinContent(1):ahSignalRnorm[0][i]->GetBinContent(nDrBins)) * 1.e-2;
      TCanvas* c = new TCanvas("c", "", 600, 600);
      c->SetLogy();
      c->SetFillColor(0);
      c->SetBorderMode(0);
      c->SetBorderSize(2);
      c->SetLeftMargin(0.185);
      c->SetRightMargin(0.030);
      c->SetTopMargin(0.080);
      c->SetBottomMargin(0.11);
      c->SetFrameBorderMode(0);
      c->SetFrameLineWidth(2);
      TH2F* hempty = new TH2F("hempty", Form(";%s;%s","r","#frac{dN_{JD}}{dr}"), 5, drBins[0], drBins[nDrBins], 10, yaxismin, yaxismax);
      hempty->GetXaxis()->SetNdivisions(505);
      xjjroot::sethempty(hempty, 0, 0.3);
      hempty->Draw();
      TLegend* leg = new TLegend(0.63, 0.78-4*0.05, 0.88, 0.78);
      xjjroot::setleg(leg, 0.038);
      ahSignalRnorm[0][i]->Draw("pe same");
      leg->AddEntry(ahSignalRnorm[0][i], "Raw jet, Raw D", "p");
      // leg->AddEntry(ahSignalRnorm[0][i], texDpt.Data(), "p");
      for(int l=0;l<nMeBins;l++)
        {
          if(isMC && signalMC) continue;
          xjjroot::setthgrstyle(ahSignalRnormMe[l][i], amcolorMe[l], 21, 1.2, amcolorMe[l], 1, 2, -1, -1, -1);
          ahSignalRnormMe[l][i]->Draw("pe same");
          leg->AddEntry(ahSignalRnormMe[l][i], tlegpaperMe[l].Data(), "p");
        }
      // xjjroot::drawCMS(collisionsyst);
      xjjroot::drawtex(0.96, 0.936, ispp?"27.4 pb^{-1} (5.02 TeV pp)":"404 #mub^{-1} (5.02 TeV PbPb)", 0.038, 31);
      xjjroot::drawtex(0.22, 0.84, "CMS", 0.062, 11, 62);
      // xjjroot::drawtex(0.35, 0.84, "Preliminary", 0.045, 11, 52);
      // xjjroot::drawtex(0.22, 0.82, "Supplementary", 0.045, 13, 52);
      xjjroot::drawtex(0.22, 0.82, "Preliminary", 0.045, 13, 52);
      Float_t texxposD = 0.65, texyposD = 0.86, texdyposD = 0.057;
      texyposD += texdyposD;
      for(std::vector<TString>::const_iterator it=vectexD.begin(); it!=vectexD.end(); it++)
        xjjroot::drawtex(texxposD, texyposD=(texyposD-texdyposD), *it);
      Float_t texxposJ = 0.23, texyposJ = 0.75, texdyposJ = 0.06;
      texyposJ += texdyposJ;
      for(std::vector<TString>::const_iterator it=vectexJ.begin(); it!=vectexJ.end(); it++)
        xjjroot::drawtex(texxposJ, texyposJ=(texyposJ-texdyposJ), *it);
      leg->Draw();
      c->SaveAs(Form("plotxsecspaper/cxsec_%s_%s_pt_%d_Me.pdf","dr",outputname.Data(),i));
      delete leg;
      delete hempty;
      delete c;
    }

  for(int i=0;i<nPtBins;i++)
    {
      TString texDpt = ptBins[i+1]==999?Form("p_{T}^{D} > %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str()):Form("%s < p_{T}^{D} < %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str(),xjjc::number_remove_zero(ptBins[i+1]).c_str());
      std::vector<TString> vectexD = {texDpt, "|y^{D}| < 2"};
      std::vector<TString> vectexJ = {
        jetetamin<=0?Form("|#eta^{jet}| < %s",xjjc::number_remove_zero(jetetamax).c_str()):Form("%s < |#eta^{jet}| < %s",xjjc::number_remove_zero(jetetamin).c_str(),xjjc::number_remove_zero(jetetamax).c_str()),
        texjetpt
      };
      Float_t yaxismax = ahSignalRnorm[0][i]->GetBinContent(1) * 1.e+4;
      Float_t yaxismin = (ahSignalRnormMe[0][i]->GetBinContent(1)>0?ahSignalRnormMe[0][i]->GetBinContent(1):ahSignalRnorm[0][i]->GetBinContent(nDrBins)) * 1.e-2;
      TCanvas* c = new TCanvas("c", "", 600, 600);
      c->SetLogy();
      c->SetFillColor(0);
      c->SetBorderMode(0);
      c->SetBorderSize(2);
      c->SetLeftMargin(0.185);
      c->SetRightMargin(0.030);
      c->SetTopMargin(0.080);
      c->SetBottomMargin(0.11);
      c->SetFrameBorderMode(0);
      c->SetFrameLineWidth(2);
      TH2F* hempty = new TH2F("hempty", Form(";%s;%s","r","#frac{dN_{JD}}{dr}"), 5, drBins[0], drBins[nDrBins], 10, yaxismin, yaxismax);
      hempty->GetXaxis()->SetNdivisions(505);
      xjjroot::sethempty(hempty, 0, 0.3);
      hempty->Draw();
      TLegend* leg = new TLegend(0.63, 0.78-3*0.05, 0.88, 0.78);
      xjjroot::setleg(leg, 0.038);
      ahSignalRnorm[0][i]->Draw("pe same");
      leg->AddEntry(ahSignalRnorm[0][i], "Raw", "p");
      xjjroot::setthgrstyle(ahSignalRbkgMe[i], kViolet-7, 21, 1.2, kViolet-7, 1, 2, -1, -1, -1);
      ahSignalRbkgMe[i]->Draw("pe same");
      leg->AddEntry(ahSignalRbkgMe[i], "Background", "p");
      xjjroot::setthgrstyle(ahSignalRsubRawMe[i], kOrange+6, 34, 1.2 , kOrange+6, 1, 2, -1, -1, -1);
      ahSignalRsubRawMe[i]->Draw("pe same");
      leg->AddEntry(ahSignalRsubRawMe[i], "Signal", "p");
      // xjjroot::drawCMS(collisionsyst);
      xjjroot::drawtex(0.96, 0.936, ispp?"27.4 pb^{-1} (5.02 TeV pp)":"404 #mub^{-1} (5.02 TeV PbPb)", 0.038, 31);
      xjjroot::drawtex(0.22, 0.84, "CMS", 0.062, 11, 62);
      // xjjroot::drawtex(0.35, 0.84, "Preliminary", 0.045, 11, 52);
      // xjjroot::drawtex(0.22, 0.82, "Supplementary", 0.045, 13, 52);
      xjjroot::drawtex(0.22, 0.82, "Preliminary", 0.045, 13, 52);
      Float_t texxposD = 0.65, texyposD = 0.86, texdyposD = 0.057;
      texyposD += texdyposD;
      for(std::vector<TString>::const_iterator it=vectexD.begin(); it!=vectexD.end(); it++)
        xjjroot::drawtex(texxposD, texyposD=(texyposD-texdyposD), *it);
      Float_t texxposJ = 0.23, texyposJ = 0.75, texdyposJ = 0.06;
      texyposJ += texdyposJ;
      for(std::vector<TString>::const_iterator it=vectexJ.begin(); it!=vectexJ.end(); it++)
        xjjroot::drawtex(texxposJ, texyposJ=(texyposJ-texdyposJ), *it);
      leg->Draw();
      c->SaveAs(Form("plotxsecspaper/cxsecsub_%s_%s_pt_%d_Me.pdf","dr",outputname.Data(),i));
      delete leg;
      delete hempty;
      delete c;
    }

  //
  for(int i=0;i<nPtBins;i++)
    {
      TString texDpt = ptBins[i+1]==999?Form("p_{T}^{D} > %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str()):Form("%s < p_{T}^{D} < %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str(),xjjc::number_remove_zero(ptBins[i+1]).c_str());
      Float_t yaxismin = ahSignalRsubRaw[i]->GetBinContent(nDrBins-1) * 1.e-2;
      Float_t yaxismax = ahSignalRsubRaw[i]->GetBinContent(1) * 1.e+3;
      TCanvas* c = new TCanvas("c", "", 600, 600);
      c->SetLogy();
      TH2F* hempty = new TH2F("hempty", Form(";%s;%s","r","#frac{dN_{JD}}{dr}"), 5, drBins[0], drBins[nDrBins], 10, yaxismin, yaxismax);
      hempty->GetXaxis()->SetNdivisions(505);
      xjjroot::sethempty(hempty, 0, 0.3);
      hempty->Draw();
      TLegend* leg = new TLegend(0.53, 0.88-0.06, 0.85, 0.88);
      xjjroot::setleg(leg, 0.038);
      xjjroot::setthgrstyle(ahSignalRsubRaw[i], amcolor[i], amstyle[0], 1.2, amcolor[i], 1, 2, -1, -1, -1);
      if(ahSignalRsubRaw[i]->GetBinContent(nDrBins) < 0) ahSignalRsubRaw[i]->SetBinContent(nDrBins, yaxismin * 1.e-3);
      ahSignalRsubRaw[i]->Draw("pe same");
      leg->AddEntry(ahSignalRsubRaw[i], texDpt.Data(), "p");
      xjjroot::drawCMS(collisionsyst);
      Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06;
      texypos += texdypos;
      for(std::vector<TString>::const_iterator it=vectex.begin(); it!=vectex.end(); it++)
        xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), *it);
      leg->Draw();
      if(jetetamin>=0.3) c->SaveAs(Form("plotxsecs/cxsecsub_%s_%s_pt_%d.pdf","dr",outputname.Data(),i));
      delete leg;
      delete hempty;
      delete c;
    }

  for(int i=0;i<nPtBins;i++)
    {
      TString texDpt = ptBins[i+1]==999?Form("p_{T}^{D} > %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str()):Form("%s < p_{T}^{D} < %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str(),xjjc::number_remove_zero(ptBins[i+1]).c_str());
      Float_t yaxismin = ahSignalRsubRawMe[i]->GetBinContent(nDrBins) * 1.e-2;
      Float_t yaxismax = ahSignalRsubRawMe[i]->GetBinContent(1) * 1.e+3;
      TCanvas* c = new TCanvas("c", "", 600, 600);
      c->SetLogy();
      TH2F* hempty = new TH2F("hempty", Form(";%s;%s","r","#frac{dN_{JD}}{dr}"), 5, drBins[0], drBins[nDrBins], 10, yaxismin, yaxismax);
      hempty->GetXaxis()->SetNdivisions(505);
      xjjroot::sethempty(hempty, 0, 0.3);
      hempty->Draw();
      TLegend* leg = new TLegend(0.53, 0.88-0.06, 0.85, 0.88);
      xjjroot::setleg(leg, 0.038);
      xjjroot::setthgrstyle(ahSignalRsubRawMe[i], amcolor[i], amstyle[0], 1.2, amcolor[i], 1, 2, -1, -1, -1);
      if(ahSignalRsubRawMe[i]->GetBinContent(nDrBins) < 0) ahSignalRsubRawMe[i]->SetBinContent(nDrBins, yaxismin * 1.e-3);
      ahSignalRsubRawMe[i]->Draw("pe same");
      leg->AddEntry(ahSignalRsubRawMe[i], texDpt.Data(), "p");
      xjjroot::drawCMS(collisionsyst);
      Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06;
      texypos += texdypos;
      for(std::vector<TString>::const_iterator it=vectex.begin(); it!=vectex.end(); it++)
        xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), *it);
      leg->Draw();
      c->SaveAs(Form("plotxsecs/cxsecsub_%s_%s_pt_%d_Me.pdf","dr",outputname.Data(),i));
      delete leg;
      delete hempty;
      delete c;
    }

}

int main(int argc, char* argv[])
{
  if(argc==10)
    {
      djtana_plothist(argv[1], argv[2], argv[3], atoi(argv[4]), 
                      atof(argv[5]), atof(argv[6]), atof(argv[7]), atof(argv[8]),
                      atoi(argv[9]));
      return 0;
    }
  else
    {
      std::cout<<"  Error: invalid arguments number - djtana_plothist()"<<std::endl;
      return 1;
    }
}

int arguerr(TString collisionsyst, Int_t isMC)
{
  if(collsyst_list.find(collisionsyst)==collsyst_list.end())
    {
      std::cout<<"\033[1;31merror:\033[0m invalid \"collisionsyst\""<<std::endl;
      return 1;
    } 
  if(isMC!=0 && isMC!=1)
    {
      std::cout<<"\033[1;31merror:\033[0m invalid \"isMC\""<<std::endl;
      return 1;
    }
  return 0;
}

