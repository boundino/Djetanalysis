#include "compxsec.h"

void compxsec_usehist_ratio(TString inputnumname, TString inputdenname, 
                            TString legnum, TString legden,
                            TString outputname, 
                            Float_t jetptmin, Float_t jetptmax, Float_t jetetamin, Float_t jetetamax,
                            TString texname="")
{
  xjjroot::setgstyle();

  if(createhists("usehist")) return;

  std::vector<TFile*> infhist(nCorr, 0);
  infhist[0] = new TFile(Form("%s.root",inputnumname.Data()));
  if(!infhist[0]->IsOpen()) return;
  infhist[1] = new TFile(Form("%s.root",inputdenname.Data()));
  if(!infhist[1]->IsOpen()) return;

  if(gethists(infhist, "usehist_ratio")) return;

  for(int i=0;i<nPtBins;i++)
    ahCorrFactor[i]->Divide(ahSignalRnorm[0][i], ahSignalRnorm[1][i]);

  // preparation
  std::vector<TString> vectex =
    {
      "|y^{D}| < 2",
      Form("%s < |#eta^{jet}| < %s",xjjc::number_remove_zero(jetetamin).c_str(),xjjc::number_remove_zero(jetetamax).c_str()),
    };
  TString texjetpt = jetptmax<999? Form("%s < p_{T}^{jet} < %s GeV/c",xjjc::number_remove_zero(jetptmin).c_str(),xjjc::number_remove_zero(jetptmax).c_str()): Form("p_{T}^{jet} > %s GeV/c",xjjc::number_remove_zero(jetptmin).c_str());
  vectex.push_back(texjetpt);

  Float_t ypaddiv = 2./3, yPullpaddiv = 1-ypaddiv;

  for(int i=0;i<nPtBins;i++)
    {
      Float_t yaxismax = 3;
      Float_t yaxismin = 0;
      TCanvas* c = new TCanvas("c", "", 600, 800);
      TPad* pXsec = new TPad("pXsec", "", 0, 1-ypaddiv, 1, 1);
      pXsec->SetMargin(xjjroot::margin_pad_left, xjjroot::margin_pad_right, 0, xjjroot::margin_pad_top);
      pXsec->Draw();
      pXsec->cd();
      // pXsec->SetLogy();
      TH2F* hempty = new TH2F("hempty", ";r;P+H / PYTHIA", 5, drBins[0], drBins[nDrBins], 10, yaxismin, yaxismax);
      hempty->GetXaxis()->SetNdivisions(505);
      xjjroot::sethempty(hempty, 0, 0.3);
      hempty->Draw();
      TLegend* leg = new TLegend(0.58, 0.88-2*0.06, 0.90, 0.88);
      xjjroot::setleg(leg);
      xjjroot::setthgrstyle(ahSignalRnorm[0][i], kBlack, 20, 1.2, kBlack, 1, 1, -1, -1, -1);
      ahSignalRnorm[0][i]->Draw("pe same");
      leg->AddEntry(ahSignalRnorm[0][i], legnum.Data(), "p");
      xjjroot::setthgrstyle(ahSignalRnorm[1][i], kRed, 25, 1.2, kRed, 1, 1, -1, -1, -1);
      ahSignalRnorm[1][i]->Draw("pe same");
      leg->AddEntry(ahSignalRnorm[1][i], legden.Data(), "p");
      xjjroot::drawCMS("");
      Float_t texxpos = 0.22, texypos = 0.85, texdypos = 0.06;
      texypos += texdypos;
      for(std::vector<TString>::const_iterator it=vectex.begin(); it!=vectex.end(); it++)
        xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), *it);
      TString tpt = ptBins[i+1]>=999?Form("p_{T}^{D} > %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str()):Form("%s < p_{T}^{D} < %s GeV/c",xjjc::number_remove_zero(ptBins[i]).c_str(),xjjc::number_remove_zero(ptBins[i+1]).c_str());
      xjjroot::drawtex(texxpos, texypos=(texypos-texdypos), tpt.Data());
      leg->Draw();

      c->cd();
      TPad* pPull = new TPad("pPull", "", 0, 0, 1, yPullpaddiv);
      pPull->SetMargin(xjjroot::margin_pad_left, xjjroot::margin_pad_right, 0.07*1/yPullpaddiv, 0);
      pPull->Draw();
      pPull->cd();
      TH2F* hemptyPull = new TH2F("hemptyPull", ";r;Ratio", 5, drBins[0], drBins[nDrBins], 10, 0, 2.2);
      hemptyPull->GetXaxis()->SetNdivisions(505);
      hemptyPull->GetYaxis()->SetNdivisions(504);
      xjjroot::sethempty(hemptyPull, -0.5, -0);
      hemptyPull->GetYaxis()->SetTitleSize(hemptyPull->GetYaxis()->GetTitleSize() * (ypaddiv / yPullpaddiv));
      hemptyPull->GetXaxis()->SetTitleSize(hemptyPull->GetXaxis()->GetTitleSize() * (ypaddiv / yPullpaddiv));
      hemptyPull->GetYaxis()->SetLabelSize(hemptyPull->GetYaxis()->GetLabelSize() * (ypaddiv / yPullpaddiv));
      hemptyPull->GetXaxis()->SetLabelSize(hemptyPull->GetXaxis()->GetLabelSize() * (ypaddiv / yPullpaddiv));
      hemptyPull->GetYaxis()->SetTitleOffset(hemptyPull->GetYaxis()->GetTitleOffset() / (ypaddiv / yPullpaddiv));
      hemptyPull->GetXaxis()->SetTitleOffset(hemptyPull->GetXaxis()->GetTitleOffset() / (ypaddiv / yPullpaddiv) *(1+1.8));
      hemptyPull->GetYaxis()->SetLabelOffset(hemptyPull->GetYaxis()->GetLabelOffset() / (ypaddiv / yPullpaddiv) *(1+12));
      hemptyPull->GetXaxis()->SetLabelOffset(hemptyPull->GetXaxis()->GetLabelOffset() / (ypaddiv / yPullpaddiv));
      hemptyPull->Draw();
      // xjjroot::drawbox(drBins[0], 0.90, drBins[nDrBins], 1.10, kGray, 0.4);
      xjjroot::drawline(drBins[0], 1.00, drBins[nDrBins], 1.00, kGray+2, 2, 4);
      xjjroot::setthgrstyle(ahCorrFactor[i], kBlack, 20, 1.2, kBlack, 1, 1, -1, -1, -1);
      ahCorrFactor[i]->Draw("pe same");
      c->SaveAs(Form("plotcomp/ccomp_ratio_xsec_%s_dr_pt_%d.pdf",outputname.Data(),i));

      delete hemptyPull;
      delete pPull;
      delete leg;
      delete hempty;
      delete pXsec;
      delete c;
    }

  if(texname == "corrFactor" && jetetamin<=0 && jetetamax>=1.6)
    {
      std::cout<<"\033[1;35mstd::vector<std::vector<Float_t>> syst"<<Form("%.0f",jetptmin)<<Form("%.0f",jetptmax)<<"_NONCLOSURE_ratio = {";
      for(int i=0;i<nPtBins;i++)
        {
          for(int j=0;j<nDrBins;j++)
            {
              if(!j) std::cout<<"{";
              std::cout<<Form("%.1f",TMath::Abs(ahCorrFactor[i]->GetBinContent(j+1)-1)*100.)<<(j<nDrBins-1?", ":"}");
            }
          if(i<nPtBins-1) std::cout<<","<<std::endl;
        }
      std::cout<<"};\033[0m"<<std::endl;      
    }
}

int main(int argc, char* argv[])
{
  if(argc==11)
    {
      compxsec_usehist_ratio(argv[1], argv[2], argv[3], argv[4], argv[5], atof(argv[6]), atof(argv[7]), atof(argv[8]), atof(argv[9]), argv[10]);
      return 0;
    }
  std::cout<<"  Error: invalid arguments number - compxsec_usehist_ratio()"<<std::endl;
  return 1;
}
