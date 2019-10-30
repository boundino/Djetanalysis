#ifndef SYSTMETICS_
#define SYSTMETICS_

#include <vector>
#include <TMath.h>
#include <iostream>
#include <iomanip>

namespace djtsyst
{
  // jet energy scale
  std::vector<std::vector<Float_t>> syst60999_SCALE_pp = {{6.8, 15.2, 7.7, 10.3},
                                                          {1.6, 7.2, 9.6, 17.5}};
  std::vector<std::vector<Float_t>> syst60999_SCALE_PbPb = {{24.3, 31.5, 8.1, 35.8},
                                                            {1.8, 5.0, 11.5, 41.8}};
  std::vector<std::vector<Float_t>> syst6080_SCALE_pp = {{3.4, 5.8, 13.3, 26.5}};
  std::vector<std::vector<Float_t>> syst80100_SCALE_pp = {{0.8, 3.0, 3.5, 8.2}};
  std::vector<std::vector<Float_t>> syst100999_SCALE_pp = {{0.6, 3.2, 2.8, 3.5}};
  std::vector<std::vector<Float_t>> syst6080_SCALE_PbPb = {{8.6, 7.0, 17.7, 17.4}};
  std::vector<std::vector<Float_t>> syst80100_SCALE_PbPb = {{6.7, 2.2, 21.5, 26.6}};
  std::vector<std::vector<Float_t>> syst100999_SCALE_PbPb = {{0.9, 6.6, 11.2, 24.6}};

  // jet resolution
  // std::vector<std::vector<Float_t>> syst60999_RESO_pp = {{3.0, 0.3, 1.2, 1.3},
  //                                                        {0.4, 1.2, 2.5, 0.8}};
  std::vector<std::vector<Float_t>> syst60999_RESO_pp = {{0.0, 0.0, 0.0, 0.0},
                                                         {0.0, 0.0, 0.0, 0.0}};
  std::vector<std::vector<Float_t>> syst60999_RESO_PbPb = {{5.6, 1.3, 2.9, 3.7},
                                                           {0.6, 0.7, 4.9, 1.8}};
  std::vector<std::vector<Float_t>> syst6080_RESO_pp = {{0.3, 0.5, 0.5, 0.2}};
  std::vector<std::vector<Float_t>> syst80100_RESO_pp = {{0.1, 0.3, 0.6, 0.6}};
  std::vector<std::vector<Float_t>> syst100999_RESO_pp = {{0.2, 0.1, 0.5, 0.7}};
  std::vector<std::vector<Float_t>> syst6080_RESO_PbPb = {{0.0, 0.2, 0.4, 0.5}};
  std::vector<std::vector<Float_t>> syst80100_RESO_PbPb = {{0.3, 0.3, 1.1, 1.0}};
  std::vector<std::vector<Float_t>> syst100999_RESO_PbPb = {{0.3, 0.3, 1.0, 0.6}};

  // pdf variation
  std::vector<std::vector<Float_t>> syst60999_PDF_pp = {{4.5, 4.8, 3.1, 2.6},
                                                        {3.8, 3.7, 3.8, 5.4}};
  std::vector<std::vector<Float_t>> syst60999_PDF_PbPb = {{4.9, 5.2, 4.8, 7.7},
                                                          {5.9, 5.0, 8.2, 1.4}};
  std::vector<std::vector<Float_t>> syst6080_PDF_pp = {{3.8, 3.7, 3.2, 2.8}};
  std::vector<std::vector<Float_t>> syst80100_PDF_pp = {{3.9, 3.1, 3.4, 3.0}};
  std::vector<std::vector<Float_t>> syst100999_PDF_pp = {{4.3, 4.1, 3.3, 2.5}};
  std::vector<std::vector<Float_t>> syst6080_PDF_PbPb = {{6.1, 4.8, 6.3, 8.2}};
  std::vector<std::vector<Float_t>> syst80100_PDF_PbPb = {{4.9, 4.6, 6.7, 3.9}};
  std::vector<std::vector<Float_t>> syst100999_PDF_PbPb = {{6.4, 6.8, 7.0, 9.5}};
  std::vector<std::vector<Float_t>> syst60999_PDF_ratio = {{2.0, 3.0, 1.9, 8.2},
                                                           {2.5, 2.3, 6.5, 7.2}};
  std::vector<std::vector<Float_t>> syst6080_PDF_ratio = {{2.4, 1.9, 4.8, 5.5}};
  std::vector<std::vector<Float_t>> syst80100_PDF_ratio = {{1.5, 1.6, 3.6, 1.1}};
  std::vector<std::vector<Float_t>> syst100999_PDF_ratio = {{3.3, 3.3, 3.8, 7.3}};

  // non-closure
  std::vector<std::vector<Float_t>> syst60999_NONCLOSURE_pp = {{12.7, 1.3, 6.1, 6.4},
                                                               {4.4, 14.3, 30.1, 30.7}};
  std::vector<std::vector<Float_t>> syst60999_NONCLOSURE_PbPb = {{6.2, 3.2, 0.7, 1.1},
                                                                 {6.3, 17.8, 30.1, 31.5}};
  std::vector<std::vector<Float_t>> syst6080_NONCLOSURE_pp = {{9.7, 12.0, 25.9, 26.1}};
  std::vector<std::vector<Float_t>> syst80100_NONCLOSURE_pp = {{10.0, 14.0, 20.3, 21.1}};
  std::vector<std::vector<Float_t>> syst100999_NONCLOSURE_pp = {{10.3, 12.9, 17.6, 15.8}};
  std::vector<std::vector<Float_t>> syst6080_NONCLOSURE_PbPb = {{9.7, 13.7, 26.9, 29.7}};
  std::vector<std::vector<Float_t>> syst80100_NONCLOSURE_PbPb = {{10.7, 19.6, 33.6, 29.7}};
  std::vector<std::vector<Float_t>> syst100999_NONCLOSURE_PbPb = {{14.5, 32.0, 36.5, 29.5}};
  std::vector<std::vector<Float_t>> syst60999_NONCLOSURE_ratio = {{5.8, 4.4, 5.7, 8.0},
                                                                  {1.7, 4.1, 0.0, 1.2}};
  std::vector<std::vector<Float_t>> syst6080_NONCLOSURE_ratio = {{0.0, 1.9, 1.4, 4.9}};
  std::vector<std::vector<Float_t>> syst80100_NONCLOSURE_ratio = {{0.7, 6.6, 16.6, 10.9}};
  std::vector<std::vector<Float_t>> syst100999_NONCLOSURE_ratio = {{3.7, 21.9, 22.9, 16.3}};

  // trigger efficiency
  std::vector<std::vector<Float_t>> syst60999_TRIGGER_pp = {{1.1, 1.8, 1.8, 1.6},
                                                            {0.3, 0.6, 2.7, 1.3}};
  std::vector<std::vector<Float_t>> syst60999_TRIGGER_PbPb = {{7.4, 6.2, 0.7, 14.5},
                                                              {0.8, 1.6, 4.8, 8.5}};
  std::vector<std::vector<Float_t>> syst6080_TRIGGER_pp = {{0.4, 0.4, 0.7, 0.8}};
  std::vector<std::vector<Float_t>> syst80100_TRIGGER_pp = {{0.2, 0.7, 0.2, 1.6}};
  std::vector<std::vector<Float_t>> syst100999_TRIGGER_pp = {{0.0, 0.3, 0.1, 0.4}};
  std::vector<std::vector<Float_t>> syst6080_TRIGGER_PbPb = {{10.9, 20.6, 7.7, 10.3}};
  std::vector<std::vector<Float_t>> syst80100_TRIGGER_PbPb = {{7.4, 19.3, 1.1, 7.7}};
  std::vector<std::vector<Float_t>> syst100999_TRIGGER_PbPb = {{4.6, 6.7, 10.9, 15.8}};

  // cut variation
  std::vector<Float_t> syst_CUT_pp = {3.6, 0.5};
  std::vector<Float_t> syst_CUT_PbPb = {3.5, 2.7};

  //
  std::vector<std::vector<Float_t>>* syst_SCALE_pp = 0;  
  std::vector<std::vector<Float_t>>* syst_SCALE_PbPb = 0;  
  std::vector<std::vector<Float_t>>* syst_RESO_pp = 0;  
  std::vector<std::vector<Float_t>>* syst_RESO_PbPb = 0;  
  std::vector<std::vector<Float_t>>* syst_PDF_pp = 0;  
  std::vector<std::vector<Float_t>>* syst_PDF_PbPb = 0;  
  std::vector<std::vector<Float_t>>* syst_PDF_ratio = 0;  
  std::vector<std::vector<Float_t>>* syst_NONCLOSURE_pp = 0;  
  std::vector<std::vector<Float_t>>* syst_NONCLOSURE_PbPb = 0;  
  std::vector<std::vector<Float_t>>* syst_NONCLOSURE_ratio = 0;  
  std::vector<std::vector<Float_t>>* syst_TRIGGER_pp = 0;  
  std::vector<std::vector<Float_t>>* syst_TRIGGER_PbPb = 0;  

  int initsyst(float jetptmin, float jetptmax)
  {
    if(jetptmin==60 && jetptmax==999)
      {
        syst_SCALE_pp = &syst60999_SCALE_pp;
        syst_SCALE_PbPb = &syst60999_SCALE_PbPb;
        syst_RESO_pp = &syst60999_RESO_pp;
        syst_RESO_PbPb = &syst60999_RESO_PbPb;
        syst_PDF_pp = &syst60999_PDF_pp;
        syst_PDF_PbPb = &syst60999_PDF_PbPb;
        syst_PDF_ratio = &syst60999_PDF_ratio;
        syst_NONCLOSURE_pp = &syst60999_NONCLOSURE_pp;
        syst_NONCLOSURE_PbPb = &syst60999_NONCLOSURE_PbPb;
        syst_NONCLOSURE_ratio = &syst60999_NONCLOSURE_ratio;
        syst_TRIGGER_pp = &syst60999_TRIGGER_pp;
        syst_TRIGGER_PbPb = &syst60999_TRIGGER_PbPb;
        return 0;
      }
    if(jetptmin==60 && jetptmax==80)
      {
        syst_SCALE_pp = &syst6080_SCALE_pp;
        syst_SCALE_PbPb = &syst6080_SCALE_PbPb;
        syst_RESO_pp = &syst6080_RESO_pp;
        syst_RESO_PbPb = &syst6080_RESO_PbPb;
        syst_PDF_pp = &syst6080_PDF_pp;
        syst_PDF_PbPb = &syst6080_PDF_PbPb;
        syst_PDF_ratio = &syst6080_PDF_ratio;
        syst_NONCLOSURE_pp = &syst6080_NONCLOSURE_pp;
        syst_NONCLOSURE_PbPb = &syst6080_NONCLOSURE_PbPb;
        syst_NONCLOSURE_ratio = &syst6080_NONCLOSURE_ratio;
        syst_TRIGGER_pp = &syst6080_TRIGGER_pp;
        syst_TRIGGER_PbPb = &syst6080_TRIGGER_PbPb;
        return 0;
      }
    if(jetptmin==80 && jetptmax==100)
      {
        syst_SCALE_pp = &syst80100_SCALE_pp;
        syst_SCALE_PbPb = &syst80100_SCALE_PbPb;
        syst_RESO_pp = &syst80100_RESO_pp;
        syst_RESO_PbPb = &syst80100_RESO_PbPb;
        syst_PDF_pp = &syst80100_PDF_pp;
        syst_PDF_PbPb = &syst80100_PDF_PbPb;
        syst_PDF_ratio = &syst80100_PDF_ratio;
        syst_NONCLOSURE_pp = &syst80100_NONCLOSURE_pp;
        syst_NONCLOSURE_PbPb = &syst80100_NONCLOSURE_PbPb;
        syst_NONCLOSURE_ratio = &syst80100_NONCLOSURE_ratio;
        syst_TRIGGER_pp = &syst80100_TRIGGER_pp;
        syst_TRIGGER_PbPb = &syst80100_TRIGGER_PbPb;
        return 0;
      }
    if(jetptmin==100 && jetptmax==999)
      {
        syst_SCALE_pp = &syst100999_SCALE_pp;
        syst_SCALE_PbPb = &syst100999_SCALE_PbPb;
        syst_RESO_pp = &syst100999_RESO_pp;
        syst_RESO_PbPb = &syst100999_RESO_PbPb;
        syst_PDF_pp = &syst100999_PDF_pp;
        syst_PDF_PbPb = &syst100999_PDF_PbPb;
        syst_PDF_ratio = &syst100999_PDF_ratio;
        syst_NONCLOSURE_pp = &syst100999_NONCLOSURE_pp;
        syst_NONCLOSURE_PbPb = &syst100999_NONCLOSURE_PbPb;
        syst_NONCLOSURE_ratio = &syst100999_NONCLOSURE_ratio;
        syst_TRIGGER_pp = &syst100999_TRIGGER_pp;
        syst_TRIGGER_PbPb = &syst100999_TRIGGER_PbPb;
        return 0;
      }
    std::cout<<"error: invalid jetptmin or jetptmax"<<std::endl;
    return 1;
  }

  Float_t getsyst(int ibinpt, int ibindr, Option_t* option)
  {
    TString opt  = option;
    Float_t syst = 0;

    if(!syst_SCALE_pp || !syst_SCALE_PbPb || !syst_RESO_pp || !syst_RESO_PbPb || !syst_PDF_pp || !syst_PDF_PbPb || !syst_NONCLOSURE_pp || !syst_NONCLOSURE_PbPb || !syst_TRIGGER_pp || !syst_TRIGGER_PbPb) 
      { std::cout<<"error: init syst first."<<std::endl; return -1; }

    if(opt=="pp")
      {
        syst += syst_CUT_pp[ibinpt] * syst_CUT_pp[ibinpt] + 
          syst_SCALE_pp->at(ibinpt).at(ibindr) * syst_SCALE_pp->at(ibinpt).at(ibindr) + 
          syst_RESO_pp->at(ibinpt).at(ibindr) * syst_RESO_pp->at(ibinpt).at(ibindr) + 
          syst_PDF_pp->at(ibinpt).at(ibindr) * syst_PDF_pp->at(ibinpt).at(ibindr) + 
          syst_NONCLOSURE_pp->at(ibinpt).at(ibindr) * syst_NONCLOSURE_pp->at(ibinpt).at(ibindr);
        syst_TRIGGER_pp->at(ibinpt).at(ibindr) * syst_TRIGGER_pp->at(ibinpt).at(ibindr);
      }
    else if(opt=="PbPb")
      {
        syst += syst_CUT_PbPb[ibinpt] * syst_CUT_PbPb[ibinpt] + 
          syst_SCALE_PbPb->at(ibinpt).at(ibindr) * syst_SCALE_PbPb->at(ibinpt).at(ibindr) + 
          syst_RESO_PbPb->at(ibinpt).at(ibindr) * syst_RESO_PbPb->at(ibinpt).at(ibindr) + 
          syst_PDF_PbPb->at(ibinpt).at(ibindr) * syst_PDF_PbPb->at(ibinpt).at(ibindr) + 
          syst_NONCLOSURE_PbPb->at(ibinpt).at(ibindr) * syst_NONCLOSURE_PbPb->at(ibinpt).at(ibindr);
        syst_TRIGGER_PbPb->at(ibinpt).at(ibindr) * syst_TRIGGER_PbPb->at(ibinpt).at(ibindr);
      }
    else if(opt=="ratio")
      {
        syst += syst_CUT_pp[ibinpt] * syst_CUT_pp[ibinpt] + 
          syst_SCALE_pp->at(ibinpt).at(ibindr) * syst_SCALE_pp->at(ibinpt).at(ibindr) + 
          syst_RESO_pp->at(ibinpt).at(ibindr) * syst_RESO_pp->at(ibinpt).at(ibindr) + 
          syst_TRIGGER_pp->at(ibinpt).at(ibindr) * syst_TRIGGER_pp->at(ibinpt).at(ibindr) + 
          syst_CUT_PbPb[ibinpt] * syst_CUT_PbPb[ibinpt] + 
          syst_SCALE_PbPb->at(ibinpt).at(ibindr) * syst_SCALE_PbPb->at(ibinpt).at(ibindr) + 
          syst_RESO_PbPb->at(ibinpt).at(ibindr) * syst_RESO_PbPb->at(ibinpt).at(ibindr) + 
          syst_TRIGGER_PbPb->at(ibinpt).at(ibindr) * syst_TRIGGER_PbPb->at(ibinpt).at(ibindr) + 

          syst_NONCLOSURE_ratio->at(ibinpt).at(ibindr) * syst_NONCLOSURE_ratio->at(ibinpt).at(ibindr) + 
          syst_PDF_ratio->at(ibinpt).at(ibindr) * syst_PDF_ratio->at(ibinpt).at(ibindr);        
      }
    else
      {
        std::cout<<"error: invalid option for getsyst()"<<std::endl;
        return -1;
      }

    return TMath::Sqrt(syst)/100.;
  }

  int printsysts(int projection=0)
  {
    const int widcell = 15, widtitle = 30, nbinpt = 2, nbindr = 4, widall = 1 + widtitle+2 + (widcell+2)*nbinpt*nbindr, nsource = 8;
    std::vector<std::vector<float>> syst_pp_all(nsource), syst_PbPb_all(nsource), syst_ratio_all(nsource);
    std::vector<std::vector<float>> syst_pp_project(nsource), syst_PbPb_project(nsource), syst_ratio_project(nsource);
    std::vector<std::string> str_name = {"Signal extraction", "Selection efficiency", "Jet energy scale", "Jet energy resolution", "Trigger efficiency", "Non-closure", "Total", "Total xcheck"};
    float lumiscale_pp = TMath::Sqrt(650. / 27.4), lumiscale_PbPb = TMath::Sqrt(10. / 0.4), lumiscale_ratio = lumiscale_PbPb;
    std::vector<double> lumiscales_pp = {1./lumiscale_pp, 1./lumiscale_pp, 1./lumiscale_pp, 1., 1./lumiscale_pp, 1., 0., 1.};
    std::vector<double> lumiscales_PbPb = {1./lumiscale_PbPb, 1./lumiscale_PbPb, 1./lumiscale_PbPb, 1., 1./lumiscale_PbPb, 1., 0., 1.};
    std::vector<double> lumiscales_ratio = {1./lumiscale_ratio, 1./lumiscale_ratio, 1./lumiscale_ratio, 1., 1./lumiscale_ratio, 1., 0., 1.};
    int count = 0;
    for(int ibinpt=0; ibinpt<nbinpt/*to change*/; ibinpt++)
      {
        for(int ibindr=0;ibindr<nbindr;ibindr++)
          {
            syst_pp_all[0].push_back(syst_PDF_pp->at(ibinpt).at(ibindr)); // signal extraction
            syst_pp_all[1].push_back(syst_CUT_pp[ibinpt]); // selection
            syst_pp_all[2].push_back(syst_SCALE_pp->at(ibinpt).at(ibindr)); // JEC
            syst_pp_all[3].push_back(syst_RESO_pp->at(ibinpt).at(ibindr)); // JER
            syst_pp_all[4].push_back(syst_TRIGGER_pp->at(ibinpt).at(ibindr)); // trigger
            syst_pp_all[5].push_back(syst_NONCLOSURE_pp->at(ibinpt).at(ibindr)); // non-closure
            syst_pp_all[6].push_back(0);
            syst_pp_all[7].push_back(getsyst(ibinpt, ibindr, "pp") * 100.);

            syst_PbPb_all[0].push_back(syst_PDF_PbPb->at(ibinpt).at(ibindr)); // signal extraction
            syst_PbPb_all[1].push_back(syst_CUT_PbPb[ibinpt]); // selection
            syst_PbPb_all[2].push_back(syst_SCALE_PbPb->at(ibinpt).at(ibindr)); // JEC
            syst_PbPb_all[3].push_back(syst_RESO_PbPb->at(ibinpt).at(ibindr)); // JER
            syst_PbPb_all[4].push_back(syst_TRIGGER_PbPb->at(ibinpt).at(ibindr)); // trigger
            syst_PbPb_all[5].push_back(syst_NONCLOSURE_PbPb->at(ibinpt).at(ibindr)); // non-closure
            syst_PbPb_all[6].push_back(0);
            syst_PbPb_all[7].push_back(getsyst(ibinpt, ibindr, "PbPb") * 100.);

            syst_ratio_all[0].push_back(syst_PDF_ratio->at(ibinpt).at(ibindr) * syst_PDF_ratio->at(ibinpt).at(ibindr)); // signal extraction
            syst_ratio_all[1].push_back(syst_CUT_pp[ibinpt] * syst_CUT_pp[ibinpt] + syst_CUT_PbPb[ibinpt] * syst_CUT_PbPb[ibinpt]); // selection
            syst_ratio_all[2].push_back(syst_SCALE_pp->at(ibinpt).at(ibindr) * syst_SCALE_pp->at(ibinpt).at(ibindr) + syst_SCALE_PbPb->at(ibinpt).at(ibindr) * syst_SCALE_PbPb->at(ibinpt).at(ibindr)); // JEC
            syst_ratio_all[3].push_back(syst_RESO_pp->at(ibinpt).at(ibindr) * syst_RESO_pp->at(ibinpt).at(ibindr) + syst_RESO_PbPb->at(ibinpt).at(ibindr) * syst_RESO_PbPb->at(ibinpt).at(ibindr)); // JER
            syst_ratio_all[4].push_back(syst_TRIGGER_pp->at(ibinpt).at(ibindr) * syst_TRIGGER_pp->at(ibinpt).at(ibindr) + syst_TRIGGER_PbPb->at(ibinpt).at(ibindr) * syst_TRIGGER_PbPb->at(ibinpt).at(ibindr)); // trigger
            syst_ratio_all[5].push_back(syst_NONCLOSURE_ratio->at(ibinpt).at(ibindr) * syst_NONCLOSURE_ratio->at(ibinpt).at(ibindr)); // non-closure
            syst_ratio_all[6].push_back(0);
            syst_ratio_all[7].push_back(getsyst(ibinpt, ibindr, "ratio") * 100.);
            for(int k=0; k<nsource-2; k++) 
              { syst_ratio_all[k].at(count) = TMath::Sqrt(syst_ratio_all[k].at(count)); }

            syst_pp_project[6].push_back(0);
            syst_PbPb_project[6].push_back(0);
            syst_ratio_project[6].push_back(0);
            syst_pp_project[7].push_back(0);
            syst_PbPb_project[7].push_back(0);
            syst_ratio_project[7].push_back(0);
            // calculate total syst
            for(int k=0; k<nsource-2; k++) 
              { 
                syst_pp_all[6].at(count) += syst_pp_all[k].at(count)*syst_pp_all[k].at(count);
                syst_PbPb_all[6].at(count) += syst_PbPb_all[k].at(count)*syst_PbPb_all[k].at(count);
                syst_ratio_all[6].at(count) += syst_ratio_all[k].at(count)*syst_ratio_all[k].at(count);

                syst_pp_project[k].push_back(syst_pp_all[k].at(count) * lumiscales_pp[k]);
                syst_PbPb_project[k].push_back(syst_PbPb_all[k].at(count) * lumiscales_PbPb[k]);
                syst_ratio_project[k].push_back(syst_ratio_all[k].at(count) * lumiscales_ratio[k]);

                syst_pp_project[6].at(count) += syst_pp_project[k].at(count)*syst_pp_project[k].at(count);
                syst_PbPb_project[6].at(count) += syst_PbPb_project[k].at(count)*syst_PbPb_project[k].at(count);
                syst_ratio_project[6].at(count) += syst_ratio_project[k].at(count)*syst_ratio_project[k].at(count);
              }
            syst_pp_all[6].at(count) = TMath::Sqrt(syst_pp_all[6].at(count));
            syst_PbPb_all[6].at(count) = TMath::Sqrt(syst_PbPb_all[6].at(count));
            syst_ratio_all[6].at(count) = TMath::Sqrt(syst_ratio_all[6].at(count));

            syst_pp_project[6].at(count) = TMath::Sqrt(syst_pp_project[6].at(count));
            syst_PbPb_project[6].at(count) = TMath::Sqrt(syst_PbPb_project[6].at(count));
            syst_ratio_project[6].at(count) = TMath::Sqrt(syst_ratio_project[6].at(count));
            
            count++;
          }
      } 
    //
    std::cout<<"\e[33;1m"<<std::endl;
    std::cout<<std::endl<<std::string(10, '>')<<std::endl;
    std::cout<<std::endl<<" >> pp >>"<<std::endl;
    std::cout<<std::left<<std::string(widall, '=')<<std::endl; 
    std::cout<<std::left<<"| "<<std::setw(widtitle)<<"D pt"<<"| "; for(int i=0;i<nbinpt;i++) { std::cout<<std::left<<std::setw((widcell+2)*nbindr-2)<<"ibinpt "+std::string(Form("%i",i))<<"| "; } ; std::cout<<std::endl<<std::string(widall, '-')<<std::endl;
    std::cout<<std::left<<"| "<<std::setw(widtitle)<<"dr"<<"| "; for(int i=0;i<nbinpt;i++) { for(int j=0;j<nbindr;j++) { std::cout<<std::left<<std::setw(widcell)<<"ibindr "+std::string(Form("%i",j))<<"| "; } } ; std::cout<<std::endl<<std::string(widall, '=')<<std::endl;
    for(int k=0;k<nsource;k++) 
      {  
        bool ifscale = lumiscales_pp[k]<1;
        std::cout<<std::left<<"| "<<std::setw(widtitle)<<str_name[k]<<"| "; for(int i=0;i<nbinpt;i++) { for(int j=0;j<nbindr;j++) { std::cout<<std::left<<std::setw(widcell)<<std::string(Form("%.1f%s",syst_pp_all[k].at(i*nbindr+j),(ifscale?Form(" => %.1f",syst_pp_project[k].at(i*nbindr+j)):"")))<<"| "; } } ; 
        std::cout<<std::endl<<std::string(widall, (k==5||k==7?'=':'-'))<<std::endl;
      }
    std::cout<<std::endl<<" >> PbPb >>"<<std::endl;
    std::cout<<std::left<<std::string(widall, '=')<<std::endl; 
    std::cout<<std::left<<"| "<<std::setw(widtitle)<<"D pt"<<"| "; for(int i=0;i<nbinpt;i++) { std::cout<<std::left<<std::setw((widcell+2)*nbindr-2)<<"ibinpt "+std::string(Form("%i",i))<<"| "; } ; std::cout<<std::endl<<std::string(widall, '-')<<std::endl;
    std::cout<<std::left<<"| "<<std::setw(widtitle)<<"dr"<<"| "; for(int i=0;i<nbinpt;i++) { for(int j=0;j<nbindr;j++) { std::cout<<std::left<<std::setw(widcell)<<"ibindr "+std::string(Form("%i",j))<<"| "; } } ; std::cout<<std::endl<<std::string(widall, '=')<<std::endl;
    for(int k=0;k<nsource;k++) 
      {
        bool ifscale = lumiscales_PbPb[k]<1;
        std::cout<<std::left<<"| "<<std::setw(widtitle)<<str_name[k]<<"| "; for(int i=0;i<nbinpt;i++) { for(int j=0;j<nbindr;j++) { std::cout<<std::left<<std::setw(widcell)<<std::string(Form("%.1f%s",syst_PbPb_all[k].at(i*nbindr+j),(ifscale?Form(" => %.1f",syst_PbPb_project[k].at(i*nbindr+j)):"")))<<"| "; } } ; 
        std::cout<<std::endl<<std::string(widall, (k==5||k==7?'=':'-'))<<std::endl;
      }
    std::cout<<std::endl<<" >> ratio >>"<<std::endl;
    std::cout<<std::left<<std::string(widall, '=')<<std::endl; 
    std::cout<<std::left<<"| "<<std::setw(widtitle)<<"D pt"<<"| "; for(int i=0;i<nbinpt;i++) { std::cout<<std::left<<std::setw((widcell+2)*nbindr-2)<<"ibinpt "+std::string(Form("%i",i))<<"| "; } ; std::cout<<std::endl<<std::string(widall, '-')<<std::endl;
    std::cout<<std::left<<"| "<<std::setw(widtitle)<<"dr"<<"| "; for(int i=0;i<nbinpt;i++) { for(int j=0;j<nbindr;j++) { std::cout<<std::left<<std::setw(widcell)<<"ibindr "+std::string(Form("%i",j))<<"| "; } } ; std::cout<<std::endl<<std::string(widall, '=')<<std::endl;
    for(int k=0;k<nsource;k++) 
      {  
        bool ifscale = lumiscales_ratio[k]<1;
        std::cout<<std::left<<"| "<<std::setw(widtitle)<<str_name[k]<<"| "; for(int i=0;i<nbinpt;i++) { for(int j=0;j<nbindr;j++) { std::cout<<std::left<<std::setw(widcell)<<std::string(Form("%.1f%s",syst_ratio_all[k].at(i*nbindr+j),(ifscale?Form(" => %.1f",syst_ratio_project[k].at(i*nbindr+j)):"")))<<"| "; } } ; 
        std::cout<<std::endl<<std::string(widall, (k==5||k==7?'=':'-'))<<std::endl;
      }

    std::cout<<std::endl<<std::string(10, '<')<<std::endl<<std::endl;
    std::cout<<"\e[0m"<<std::endl;

    //
    std::cout<<"\e[34;1m"<<std::endl;
    std::cout<<std::endl<<std::string(10, '>')<<std::endl;
    std::cout<<std::endl<<" >> pp >>"<<std::endl;
    for(int k=0;k<nsource;k++) 
      {
        bool ifscale = lumiscales_pp[k]<1;
        std::cout<<std::left<<std::setw(24)<<str_name[k];
        for(int i=0;i<nbinpt;i++) { for(int j=0;j<nbindr;j++) { std::cout<<"& "<<(ifscale?"{\\color{red}":"")<<std::string(Form("%.1f",syst_pp_all[k].at(i*nbindr+j)))<<(ifscale?Form("}$\\rightarrow${\\color{blue}%.1f}",syst_pp_project[k].at(i*nbindr+j)):"")<<" "; } } ;
        std::cout<<"\\\\"<<std::endl<<"\\hline"<<std::endl;
        if(k==5) std::cout<<"\\hline"<<std::endl;
      }
    std::cout<<std::endl<<" >> PbPb >>"<<std::endl;
    for(int k=0;k<nsource;k++) 
      {  
        bool ifscale = lumiscales_PbPb[k]<1;
        std::cout<<std::left<<std::setw(24)<<str_name[k];
        for(int i=0;i<nbinpt;i++) { for(int j=0;j<nbindr;j++) { std::cout<<"& "<<(ifscale?"{\\color{red}":"")<<std::string(Form("%.1f",syst_PbPb_all[k].at(i*nbindr+j)))<<(ifscale?Form("}$\\rightarrow${\\color{blue}%.1f}",syst_PbPb_project[k].at(i*nbindr+j)):"")<<" "; } } ;
        std::cout<<"\\\\"<<std::endl<<"\\hline"<<std::endl;
        if(k==5) std::cout<<"\\hline"<<std::endl;
      }
    std::cout<<std::endl<<" >> ratio >>"<<std::endl;
    for(int k=0;k<nsource;k++) 
      {  
        bool ifscale = lumiscales_ratio[k]<1;
        std::cout<<std::left<<std::setw(24)<<str_name[k];
        for(int i=0;i<nbinpt;i++) { for(int j=0;j<nbindr;j++) { std::cout<<"& "<<(ifscale?"{\\color{red}":"")<<std::string(Form("%.1f",syst_ratio_all[k].at(i*nbindr+j)))<<(ifscale?Form("}$\\rightarrow${\\color{blue}%.1f}",syst_ratio_project[k].at(i*nbindr+j)):"")<<" "; } } ;
        std::cout<<"\\\\"<<std::endl<<"\\hline"<<std::endl;
        if(k==5) std::cout<<"\\hline"<<std::endl;
      }

    std::cout<<std::endl<<std::string(10, '<')<<std::endl<<std::endl;
    std::cout<<"\e[0m"<<std::endl;


    std::cout<<"\e[35;1m"<<std::endl;
    std::cout<<"std::vector<std::vector<double>> vaeyPPsyst = {";
    for(int i=0;i<nbinpt;i++)
      {
        std::cout<<"{";
        for(int j=0;j<nbindr;j++) { std::cout<<syst_pp_all[6].at(i*nbindr+j)/100.<<(j==nbindr-1?"}":", "); }
        std::cout<<(i==nbinpt-1?"};":",")<<std::endl;
      }
    std::cout<<"std::vector<std::vector<double>> vaeyPPsyst_scale = {";
    for(int i=0;i<nbinpt;i++)
      {
        std::cout<<"{";
        for(int j=0;j<nbindr;j++) { std::cout<<syst_pp_project[6].at(i*nbindr+j)/100.<<(j==nbindr-1?"}":", "); }
        std::cout<<(i==nbinpt-1?"};":",")<<std::endl;
      }
    std::cout<<"std::vector<std::vector<double>> vaeyPbPbsyst = {";
    for(int i=0;i<nbinpt;i++)
      {
        std::cout<<"{";
        for(int j=0;j<nbindr;j++) { std::cout<<syst_PbPb_all[6].at(i*nbindr+j)/100.<<(j==nbindr-1?"}":", "); }
        std::cout<<(i==nbinpt-1?"};":",")<<std::endl;
      }
    std::cout<<"std::vector<std::vector<double>> vaeyPbPbsyst_scale = {";
    for(int i=0;i<nbinpt;i++)
      {
        std::cout<<"{";
        for(int j=0;j<nbindr;j++) { std::cout<<syst_PbPb_project[6].at(i*nbindr+j)/100.<<(j==nbindr-1?"}":", "); }
        std::cout<<(i==nbinpt-1?"};":",")<<std::endl;
      }
    std::cout<<"std::vector<std::vector<double>> vaeyRatiosyst = {";
    for(int i=0;i<nbinpt;i++)
      {
        std::cout<<"{";
        for(int j=0;j<nbindr;j++) { std::cout<<syst_ratio_all[6].at(i*nbindr+j)/100.<<(j==nbindr-1?"}":", "); }
        std::cout<<(i==nbinpt-1?"};":",")<<std::endl;
      }
    std::cout<<"std::vector<std::vector<double>> vaeyRatiosyst_scale = {";
    for(int i=0;i<nbinpt;i++)
      {
        std::cout<<"{";
        for(int j=0;j<nbindr;j++) { std::cout<<syst_ratio_project[6].at(i*nbindr+j)/100.<<(j==nbindr-1?"}":", "); }
        std::cout<<(i==nbinpt-1?"};":",")<<std::endl;
      }

    std::cout<<"\e[0m"<<std::endl;
    
  }
}

#endif
