#include "jetresolution.h"

void jetreso_savehist(TString inputname, TString outputname, TString collisionsyst,
                      Int_t maxevt=-1)
{
  int arguerr(TString collisionsyst);
  if(arguerr(collisionsyst)) return;
  Int_t ispp = collisionsyst=="pp"?1:0;
  init(ispp);
  djtweight::init();
  djtcorr::setParameters(ispp);

  if(createhists("savehist")) return;
  djet djt(inputname, ispp, 1);

  int64_t nentries = djt.fChain->GetEntriesFast();
  int rnentries = (maxevt>0&&maxevt<=nentries)?maxevt:nentries;
  for(int i=0;i<rnentries;i++)
    {
      if(i%10000==0) std::cout<<std::setiosflags(std::ios::left)<<"  [ \033[1;36m"<<std::setw(10)<<i<<"\033[0m"<<" / "<<std::setw(10)<<rnentries<<" ] "<<"\033[1;36m"<<std::setw(4)<<Form("%.0f%s",100.*i/rnentries,"%")<<"\033[0m"<<"   >>   jetreso_savehist("<<std::setw(20)<<Form("%s)",collisionsyst.Data())<<"\r"<<std::flush;
      //
      djt.fChain->GetEntry(i);
      //

      if(djt.pthat < 15) continue; // to be discussed ...

      Int_t ibincent = ispp?0:xjjc::findibin(&centBins, (float)(djt.hiBin/2.));
      if(ibincent<0) {std::cout<<"wrong ibincent"<<std::endl; return;}

      Float_t cweight = ispp?1.:djtweight::getcentweight(djt.hiBin);
      Float_t evtweight = djt.pthatweight*cweight;

      // loop jets
      for(int jj=0;jj<djt.njet_akpu3pf;jj++)
        {
          if((*djt.subid_akpu3pf)[jj]!=0) continue;
          // if(TMath::Abs((*djt.gjetflavor_akpu3pf)[jj])!=4) continue;

          Int_t ibineta = xjjc::findibin(&jtetaBins, (*djt.jeteta_akpu3pf)[jj]);
          if(ibineta<0) continue;
          Int_t ibinpt = xjjc::findibin(&resojtptBins, (*djt.jetpt_akpu3pf)[jj]);
          if(ibinpt<0) continue;

          Float_t jetrecopt = (*djt.jetpt_akpu3pf)[jj];
          Float_t jetrecopt_vRMatGPt = (*djt.jetpt_akpu3pf)[jj];
          Float_t jetrecopt_vFfScalePt = (*djt.jetpt_akpu3pf)[jj];
          if( djtcorr::ptCorr(5, jetrecopt_vRMatGPt, 0., ibincent) ) return;
          if( djtcorr::ptCorr(4, jetrecopt_vFfScalePt, (*djt.jetnpfpart_akpu3pf)[jj], ibincent) ) return;

          ahHistoResoPt[ibincent][0][ibinpt]->Fill(jetrecopt/(*djt.gjetpt_akpu3pf)[jj], evtweight);
          ahHistoResoPtCorr[ibincent][0][ibinpt]->Fill(jetrecopt_vRMatGPt/(*djt.gjetpt_akpu3pf)[jj], evtweight);
          ahHistoResoPtFfCorr[ibincent][0][ibinpt]->Fill(jetrecopt_vFfScalePt/(*djt.gjetpt_akpu3pf)[jj], evtweight);
          ahHistoResoPhi[ibincent][0][ibinpt]->Fill((*djt.jetphi_akpu3pf)[jj]-(*djt.gjetphi_akpu3pf)[jj], evtweight);
          ahHistoResoEta[ibincent][0][ibinpt]->Fill((*djt.jeteta_akpu3pf)[jj]-(*djt.gjeteta_akpu3pf)[jj], evtweight);

          ahHistoResoPt[ibincent][ibineta+1][ibinpt]->Fill(jetrecopt/(*djt.gjetpt_akpu3pf)[jj], evtweight);
          ahHistoResoPtCorr[ibincent][ibineta+1][ibinpt]->Fill(jetrecopt_vRMatGPt/(*djt.gjetpt_akpu3pf)[jj], evtweight);
          ahHistoResoPtFfCorr[ibincent][ibineta+1][ibinpt]->Fill(jetrecopt_vFfScalePt/(*djt.gjetpt_akpu3pf)[jj], evtweight);
          ahHistoResoPhi[ibincent][ibineta+1][ibinpt]->Fill((*djt.jetphi_akpu3pf)[jj]-(*djt.gjetphi_akpu3pf)[jj], evtweight);
          ahHistoResoEta[ibincent][ibineta+1][ibinpt]->Fill((*djt.jeteta_akpu3pf)[jj]-(*djt.gjeteta_akpu3pf)[jj], evtweight);
        }
    }
  std::cout<<std::setiosflags(std::ios::left)<<"  Processed "<<"\033[1;31m"<<rnentries<<"\033[0m out of\033[1;31m "<<nentries<<"\033[0m event(s)."<<"   >>   jetreso_savehist("<<std::setw(30)<<Form("%s)",collisionsyst.Data())<<std::endl;
  std::cout<<std::endl;

  TFile* outf = new TFile(Form("%s.root",outputname.Data()), "recreate");
  outf->cd();
  if(writehists("savehist")) return;
  outf->Write();
  outf->Close();
}

int main(int argc, char* argv[])
{
  if(argc==5)
    {
      jetreso_savehist(argv[1], argv[2], argv[3], atoi(argv[4]));
      return 0;
    }
  return 1;
}

int arguerr(TString collisionsyst)
{
  if(collsyst_list.find(collisionsyst)==collsyst_list.end())
    {
      std::cout<<"\033[1;31merror:\033[0m invalid \"collisionsyst\""<<std::endl;
      return 1;
    }
  return 0;
}
