#include "djtana.h"

#include <TString.h>
#include <TH1F.h>

std::vector<TString>        tname                  = {"",                                      "_Me"};
std::vector<TH1F**>         hSignalXsubP           = {(TH1F**)ahSignalRsubP,                   (TH1F**)ahSignalRsubMeP};
std::vector<TH1F**>         hSignalXsubRatio       = {(TH1F**)ahSignalRsubRatio,               (TH1F**)ahSignalRsubRatioMe};
std::vector<TH1F**>         hSignalXsubRatioPYTHIA = {(TH1F**)ahSignalRsubRatioPYTHIA,         (TH1F**)ahSignalRsubRatioPYTHIAMe};
std::vector<TGraphErrors**> gSignalXsubP           = {(TGraphErrors**)agSignalRsubP,           (TGraphErrors**)agSignalRsubMeP};
std::vector<TGraphErrors**> gSignalXsubRatio       = {(TGraphErrors**)agSignalRsubRatio,       (TGraphErrors**)agSignalRsubRatioMe};
std::vector<TGraphErrors**> gSignalXsubRatioPYTHIA = {(TGraphErrors**)agSignalRsubRatioPYTHIA, (TGraphErrors**)agSignalRsubRatioPYTHIAMe};

namespace finalplot
{
  void preparehist(int plotPYTHIA=1);
  // i: ptbin, l: bkgsub
  TH1F* hppdndr(int i, int l=0) { return (hSignalXsubP.at(l))[0*nPtBins+i]; }
}

void finalplot::preparehist(int plotPYTHIA)
{
  for(int i=0;i<nPtBins;i++)
    {
      Float_t ax[nDrBins], aex[nDrBins], ayPYTHIA[nDrBins], aeyPYTHIA[nDrBins];
      for(int j=0;j<nDrBins;j++)
        {
          ax[j] = (drBins[j+1]+drBins[j]) / 2.;
          aex[j] = (drBins[j+1]-drBins[j]) / 2.;
          if(plotPYTHIA)
            {
              ayPYTHIA[j] = ahSignalRsubPYTHIA[i]->GetBinContent(j+1);
              aeyPYTHIA[j] = ahSignalRsubPYTHIA[i]->GetBinError(j+1);
            }
        }
      agSignalRsubPYTHIA[i] = new TGraphErrors(nDrBins, ax, ayPYTHIA, aex, aeyPYTHIA);
      agSignalRsubPYTHIA[i]->SetName(Form("agSignalRsubPYTHIA_%d",i));
      for(int l=0;l<2;l++)
        {
          if((hSignalXsubP.at(l))[1*nPtBins+i]->GetBinContent(nDrBins)<=0 || !l)
            {
              (hSignalXsubP.at(l))[1*nPtBins+i]->SetBinContent(nDrBins, 1.e-10);
              (hSignalXsubRatio.at(l))[i]->SetBinContent(nDrBins, -10);
            }
          Float_t ayPP[nDrBins], ayPbPb[nDrBins], ayRatio[nDrBins], ayRatioPYTHIA[nDrBins], ayPPPYTHIA[nDrBins], aeyPP[nDrBins], aeyPbPb[nDrBins], aeyRatio[nDrBins], aeyRatioPYTHIA[nDrBins], aeyPPPYTHIA[nDrBins];
          for(int j=0;j<nDrBins;j++)
            {
              ax[j] = (drBins[j+1]+drBins[j]) / 2.;
              aex[j] = (drBins[j+1]-drBins[j]) / 2.;
              ayPP[j] = (hSignalXsubP.at(l))[0*nPtBins+i]->GetBinContent(j+1);
              aeyPP[j] = ayPP[j] * djtsyst::getsyst(i, j, "pp");
              ayPbPb[j] = (hSignalXsubP.at(l))[1*nPtBins+i]->GetBinContent(j+1);
              aeyPbPb[j] = ayPbPb[j] * djtsyst::getsyst(i, j, "PbPb");
              ayRatio[j] = (hSignalXsubRatio.at(l))[i]->GetBinContent(j+1);
              aeyRatio[j] = ayRatio[j] * djtsyst::getsyst(i, j, "ratio");
              if(plotPYTHIA)
                {
                  ayRatioPYTHIA[j] = (hSignalXsubRatioPYTHIA.at(l))[i]->GetBinContent(j+1);
                  aeyRatioPYTHIA[j] = ayRatioPYTHIA[j] * djtsyst::getsyst(i, j, "PbPb");
                  ayPPPYTHIA[j] = ahSignalRsubRatioPYTHIAPP[i]->GetBinContent(j+1);
                  aeyPPPYTHIA[j] = ayPPPYTHIA[j] * djtsyst::getsyst(i, j, "pp");
                }
            }
          (gSignalXsubP.at(l))[0*nPtBins+i] = new TGraphErrors(nDrBins, ax, ayPP, aex, aeyPP);
          (gSignalXsubP.at(l))[0*nPtBins+i]->SetName(Form("agSignalRsubPP_%d%s",i,tname[l].Data()));
          (gSignalXsubP.at(l))[1*nPtBins+i] = new TGraphErrors(nDrBins, ax, ayPbPb, aex, aeyPbPb);
          (gSignalXsubP.at(l))[1*nPtBins+i]->SetName(Form("agSignalRsubPbPb_%d%s",i,tname[l].Data()));
          (gSignalXsubRatio.at(l))[i] = new TGraphErrors(nDrBins, ax, ayRatio, aex, aeyRatio);
          (gSignalXsubRatio.at(l))[i]->SetName(Form("agSignalRsubRatio_%d%s",i,tname[l].Data()));
          if(plotPYTHIA)
            {
              (gSignalXsubRatioPYTHIA.at(l))[i] = new TGraphErrors(nDrBins, ax, ayRatioPYTHIA, aex, aeyRatioPYTHIA);
              (gSignalXsubRatioPYTHIA.at(l))[i]->SetName(Form("agSignalRsubRatioPYTHIA_%d%s",i,tname[l].Data()));
              agSignalRsubRatioPYTHIAPP[i] = new TGraphErrors(nDrBins, ax, ayPPPYTHIA, aex, aeyPPPYTHIA);
              agSignalRsubRatioPYTHIAPP[i]->SetName(Form("ahSignalRsubRatioPYTHIAPP_%d%s",i,tname[l].Data()));
            }
        }
    }
}
