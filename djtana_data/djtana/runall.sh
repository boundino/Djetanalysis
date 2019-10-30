#!/bin/bash

DO_2DBINS=1
DO_1DBINS=0

SAVETPL=0
SAVEHIST=0
USEHIST=0
PLOTHIST=0

[[ $DO_2DBINS -eq 1 ]] && ./dodjtana_2Dbins.sh $SAVETPL $SAVEHIST $USEHIST $PLOTHIST
[[ $DO_1DBINS -eq 1 ]] && ./dodjtana_1Dbins.sh $SAVETPL $SAVEHIST $USEHIST $PLOTHIST

SAVERATIO=0
PLOTRATIO=0
FINALPLOT=1

[[ $DO_2DBINS -eq 1 ]] && ./dodjtana_ratio_2Dbins.sh $SAVERATIO $PLOTRATIO $FINALPLOT
[[ $DO_1DBINS -eq 1 ]] && ./dodjtana_ratio_1Dbins.sh $SAVERATIO $PLOTRATIO $FINALPLOT

#

FIGARCHIVE=(../../plotArchive/figsup ../../plotArchive/figs)
for i in ${FIGARCHIVE[@]}; do mkdir -p $i ; done ;
echo
echo `readlink -f ../../plotArchive`
echo

PLOTSUP=(
    "plotfitspaper/cmasspaper_Djet_PbPb_data_RecoD_RecoJet_jetpt_60p0_999p0_jeteta_0p0_1p6__wScaleRMG_woSmearPt_woSmearAng_eta_pt_1_dr_1.pdf"
    "plotfitspaper/cmasspaper_Djet_pp_data_RecoD_RecoJet_jetpt_60p0_999p0_jeteta_0p0_1p6__wScaleRMG_woSmearPt_woSmearAng_eta_pt_1_dr_1.pdf"
    "plotxsecspaper/cxsec_dr_Djet_PbPb_data_RecoD_RecoJet_jetpt_60p0_999p0_jeteta_0p0_1p6__wScaleRMG_woSmearPt_woSmearAng_pt_0_Me.pdf"
    "plotxsecspaper/cxsecsub_dr_Djet_PbPb_data_RecoD_RecoJet_jetpt_60p0_999p0_jeteta_0p0_1p6__wScaleRMG_woSmearPt_woSmearAng_pt_0_Me.pdf"
    "plotfinal/cfinal_xsec_Djet_data_RecoD_RecoJet_jetpt_60p0_999p0_jeteta_0p0_1p6___wScaleRMG_woSmearPt_woSmearAng_r_pt_20p0_999p0_Me_dNdronly.pdf"
    "plotfinal/cfinal_xsec_Djet_data_RecoD_RecoJet_jetpt_60p0_999p0_jeteta_0p0_1p6___wScaleRMG_woSmearPt_woSmearAng_r_pt_4p0_20p0_Me_dNdronly.pdf"
    "plotfinal/cfinal_xsec_Djet_data_RecoD_RecoJet_jetpt_60p0_999p0_jeteta_0p0_1p6___wScaleRMG_woSmearPt_woSmearAng_r_pt_20p0_999p0_Me_ratioonly.pdf"
    "plotfinal/cfinal_xsec_Djet_data_RecoD_RecoJet_jetpt_60p0_999p0_jeteta_0p0_1p6___wScaleRMG_woSmearPt_woSmearAng_r_pt_4p0_20p0_Me_ratioonly.pdf"
    "plotfinal/cfinal_xsec_Djet_data_RecoD_RecoJet_jetpt_60p0_999p0_jeteta_0p0_1p6___wScaleRMG_woSmearPt_woSmearAng_r_pt_20p0_999p0_Me_dNdrratio.pdf"
    "plotfinal/cfinal_xsec_Djet_data_RecoD_RecoJet_jetpt_60p0_999p0_jeteta_0p0_1p6___wScaleRMG_woSmearPt_woSmearAng_r_pt_4p0_20p0_Me_dNdrratio.pdf"
    "plotfinal/cfinal_xsec_Djet_data_RecoD_RecoJet_jetpt_60p0_999p0_jeteta_0p0_1p6___wScaleRMG_woSmearPt_woSmearAng_r_pt_20p0_999p0_Me_dNdrpythia.pdf"
    "plotfinal/cfinal_xsec_Djet_data_RecoD_RecoJet_jetpt_60p0_999p0_jeteta_0p0_1p6___wScaleRMG_woSmearPt_woSmearAng_r_pt_4p0_20p0_Me_dNdrpythia.pdf"
)
PLOTPAPER=(
    "plotfinal/cfinal_xsec_Djet_data_RecoD_RecoJet_jetpt_60p0_999p0_jeteta_0p0_1p6___wScaleRMG_woSmearPt_woSmearAng_r_pt_20p0_999p0_Me_pythia.pdf"
    "plotfinal/cfinal_xsec_Djet_data_RecoD_RecoJet_jetpt_60p0_999p0_jeteta_0p0_1p6___wScaleRMG_woSmearPt_woSmearAng_r_pt_4p0_20p0_Me_pythia.pdf"
    "plotfinal/cfinal_xsec_Djet_data_RecoD_RecoJet_jetpt_60p0_999p0_jeteta_0p0_1p6___wScaleRMG_woSmearPt_woSmearAng_r_pt_20p0_999p0_Me_pythia_pre.pdf"
    "plotfinal/cfinal_xsec_Djet_data_RecoD_RecoJet_jetpt_60p0_999p0_jeteta_0p0_1p6___wScaleRMG_woSmearPt_woSmearAng_r_pt_4p0_20p0_Me_pythia_pre.pdf"
)

for i in ${PLOTSUP[@]}
do 
    filename=${i//"6__w"/"6___w"}
    filename=${filename##*/}
    cp $i ../../plotArchive/figsup/${filename//"_data_RecoD_RecoJet_jetpt_60p0_999p0_jeteta_0p0_1p6___wScaleRMG_woSmearPt_woSmearAng_"/"-"}
done
for i in ${PLOTPAPER[@]}
do 
    filename=${i//"6__w"/"6___w"}
    filename=${filename##*/}
    cp $i ../../plotArchive/figs/${filename//"_data_RecoD_RecoJet_jetpt_60p0_999p0_jeteta_0p0_1p6___wScaleRMG_woSmearPt_woSmearAng_"/"-"}
done