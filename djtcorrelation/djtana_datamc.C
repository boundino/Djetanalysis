#include "djtana.h"
#include "TString.h"
#include "TRegexp.h"
#include "../includes/djet.h"

void djtana_datamc()
{
    xjjroot::setgstyle();
    cout << "start" << endl;
    std::string collsyst[2] = {"pp", "PbPb"};
    std::string gentype[2] = {"data_RecoD_RecoJet","MC_RecoD_RecoJet"};//,"MC_RecoD_GenJet","MC_GenD_RecoJet","MC_GenD_GenJet"};
    Color_t gencols[2] = {kBlack,kRed};//,kBlue,kGreen,kOrange};
    Style_t genstyl[2] = {20,21};//,22,23,24};
    TH1F* phis[2];
    TH1F* phiratio;
    TFile* f[2];
    for(int i=0;i<2;i++)
    {
        for(int k=0;k<2;k++)
        {
            cout << i << endl;
            TLegend *leg = new TLegend(0.3,0.4,0.5,0.6);
            for(int j=0;j<2;j++)
            {
                cout << j << endl;
                f[j] = new TFile(Form("rootfiles/masstpl_Djet_%s_%s_jetpt_40p0_jeteta_0p0_2p0_noHLT.root",collsyst[i].c_str(),gentype[j].c_str()));
                if(f[j]->IsZombie())
                {
                    cout << "bad file " << collsyst[i] << "_" << gentype[j] << endl;
                    return;
                }
                phis[j] = (TH1F*)f[j]->Get(Form("hDPhi_pt_%d",k));
                phis[j]->Sumw2();
                phis[j]->Scale(1./phis[j]->Integral("w"));
            }
            phiratio = (TH1F*)phis[0]->Clone();
            phiratio->Divide(phis[1]);
            TCanvas *c = new TCanvas("c","",600,600);
            TPad *p = new TPad("plot","",0.,0.3,1.,1.);
            p->SetMargin(xjjroot::margin_pad_left,xjjroot::margin_pad_right,0.05,xjjroot::margin_pad_top);
            p->Draw();
            p->cd();
            TH2F* hempty = new TH2F("hempty",Form("D #phi for %s, pt_%d;#phi;#frac{#partial N}{#partial #phi}",collsyst[i].c_str(),k),1,-TMath::Pi(),TMath::Pi(),1,0.,.025);
            xjjroot::sethempty(hempty,0,0.5);
            hempty->Draw();
            xjjroot::drawCMS(collsyst[i]);
            for(int j=0;j<2;j++)
            {
                xjjroot::setthgrstyle(phis[j],gencols[j],genstyl[j],1.2,gencols[j],1,1,-1,-1,-1);
                if(j!=4)phis[j]->DrawClone("pe same");
                else phis[j]->DrawClone("p same");
                leg->AddEntry(phis[j],gentype[j].c_str());
            }
            xjjroot::setleg(leg);
            leg->Draw();
            c->cd();
            TPad* pratio = new TPad("ratio","",0.,0.,1.,0.3);
            pratio->SetMargin(xjjroot::margin_pad_left,xjjroot::margin_pad_right,0.25,xjjroot::margin_pad_top*.95);
            pratio->Draw();
            pratio->cd();
            TH2F* hempty2 = new TH2F("hempty2",";#phi;data/MC",1,-TMath::Pi(),TMath::Pi(),1,0.8,1.2);
            xjjroot::sethempty(hempty2,0,0.1);
            hempty2->GetXaxis()->SetTitleSize(hempty2->GetXaxis()->GetTitleSize() / 0.4);
            hempty2->GetYaxis()->SetTitleSize(hempty2->GetYaxis()->GetTitleSize() / 0.4);
            hempty2->GetXaxis()->SetLabelSize(hempty2->GetXaxis()->GetLabelSize() / 0.4);
            hempty2->GetYaxis()->SetLabelSize(hempty2->GetYaxis()->GetLabelSize() / 0.4);
            hempty2->GetXaxis()->SetTitleOffset(hempty2->GetXaxis()->GetTitleOffset() * 0.9);
            hempty2->GetYaxis()->SetTitleOffset(hempty2->GetYaxis()->GetTitleOffset() * 0.5);
            hempty2->GetXaxis()->SetLabelOffset(hempty2->GetXaxis()->GetLabelOffset() * 0.9);
            hempty2->GetYaxis()->SetLabelOffset(hempty2->GetYaxis()->GetLabelOffset() * 0.5);
            hempty2->Draw();
            xjjroot::setthgrstyle(phiratio,kBlack,20,1.2,kBlack,1,1,-1,-1,-1);
            phiratio->Draw("pe same");
            xjjroot::drawline(-TMath::Pi(),1.,TMath::Pi(),1.,kBlack,1,2);
            c->SaveAs(Form("plots/%s_mcdata_pt_%d.pdf",collsyst[i].c_str(),k));
            delete hempty;
            delete hempty2;
            delete p;
            delete pratio;
            delete c;
        }
    }        
}

