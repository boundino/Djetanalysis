#!/bin/bash
# dodjtana.sh #

if [[ $(hostname) == "submit-hi2.mit.edu" ]]; then
    PREFIX="/export/d00"
elif [[ $(hostname) == "submit.mit.edu" ]]; then
    PREFIX="/mnt/T2_US_MIT/submit-hi2"
else
    echo "warning: input samples are saved at submit(-hi2).mit.edu"
fi

DO_SAVETPL=${1:-0}
DO_SAVEHIST=${2:-0}
DO_USEHIST=${3:-0}
DO_PLOTHIST=${4:-0}

HLTOPT="noHLT"
# HLTOPT="HLT_AK4PFJet60_Eta5p1_v1"
# HLTOPT="HLT_HIPuAK4CaloJet60Jet80_Eta5p1_v1"

# Select the systems the macros run on 
iCOL=(0 1 2 3)
jJET=(0)
kRECOGEN=(0 1 2 3)

##

# nCOL loop
COLSYST=('pp' 'pp' 'PbPb' 'PbPb')
ISMC=(1 0 1 0)

# nJET loop
JETPTMIN=(40 60)
JETETAMIN=(0 0.3)
JETETAMAX=(2.0 1.6)

# nRECOGEN loop
RECOGEN=('RecoD_RecoJet' 'GenD_RecoJet' 'RecoD_GenJet' 'GenD_GenJet')

# dataset[nCOL]
INPUTDANAME=(
    "$PREFIX/scratch/jwang/Djets/MC/DjetFiles_20171127_pp_5TeV_TuneCUETP8M1_Dfinder_MC_20170404_pthatweight.root"
    # "$PREFIX/scratch/jwang/Djets/data/DjetFiles_20170619_pp_5TeV_HighPtLowerJets_dPt4tkPt1p5Alpha0p2Decay2_D0Dstar_20170614.root"
    "$PREFIX/scratch/jwang/Djets/data/DjetFiles_20171120_pp_5TeV_HighPtLowerJets_dPt4tkPt1p5Alpha0p2Decay2_D0Dstar_20170614.root"
    "$PREFIX/scratch/jwang/Djets/MC/DjetFiles_20171127_PbPb_5TeV_TuneCUETP8M1_Dfinder_MC_20170508_pthatweight.root"
    # "$PREFIX/scratch/ginnocen/DjetFiles_PbPb_5TeV_HardProbes_Dfinder_skimmed_1unit_part1_2_3_4_26March_finalMerge2April_v1/merged_total.root"
    "$PREFIX/scratch/jwang/Djets/data/DjetFiles_20171120_PbPb_5TeV_HIHardProbes_skimmed_1unit_part1234_26March_20170326_HLTHIPuAK4CaloJet406080.root"
)
INPUTMCNAME=(
    #'/export/d00/scratch/jwang/Djets/MC/DjetFiles_20170506_pp_5TeV_TuneCUETP8M1_Dfinder_MC_20170404_pthatweight.root'
    #'/export/d00/scratch/jwang/Djets/MC/DjetFiles_20170506_pp_5TeV_TuneCUETP8M1_Dfinder_MC_20170404_pthatweight.root'
    #'/export/d00/scratch/jwang/Djets/MC/DjetFiles_20170510_PbPb_5TeV_TuneCUETP8M1_Dfinder_MC_20170508_pthatweight.root'
    #'/export/d00/scratch/jwang/Djets/MC/DjetFiles_20170510_PbPb_5TeV_TuneCUETP8M1_Dfinder_MC_20170508_pthatweight.root'
    '/mnt/T2_US_MIT/submit-hi2/scratch/jwang/Djets/MC/DjetFiles_20170506_pp_5TeV_TuneCUETP8M1_Dfinder_MC_20170404_pthatweight.root'
    '/mnt/T2_US_MIT/submit-hi2/scratch/jwang/Djets/MC/DjetFiles_20170506_pp_5TeV_TuneCUETP8M1_Dfinder_MC_20170404_pthatweight.root'
    '/mnt/T2_US_MIT/submit-hi2/scratch/jwang/Djets/MC/DjetFiles_20170510_PbPb_5TeV_TuneCUETP8M1_Dfinder_MC_20170508_pthatweight.root'
    '/mnt/T2_US_MIT/submit-hi2/scratch/jwang/Djets/MC/DjetFiles_20170510_PbPb_5TeV_TuneCUETP8M1_Dfinder_MC_20170508_pthatweight.root'
)

# Do not touch the macros below if you don't know what they mean #

[[ $DO_SAVETPL -eq 0 && $DO_SAVEHIST -eq 0 && $DO_USEHIST -eq 0 && $DO_PLOTHIST -eq 0 ]] && echo "./dodjtana.sh [DO_SAVETPL] [DO_SAVEHIST] [DO_USEHIST] [DO_PLOTHIST]"

#
nCOL=${#COLSYST[@]}
nRECOGEN=${#RECOGEN[@]}
nJET=${#JETPTMIN[@]}

#
NC='\033[0m'
FUNCOLOR='\033[1;33m'
ARGCOLOR='\033[1;32m'
ERRCOLOR='\033[1;31m'
tMC=('data' 'MC')

#
function float_to_string()
{
    if [[ $# -ne 1 ]]
    then
        echo -e "${ERRCOLOR}error:${NC} invalid argument number - float_to_string()"
        return 1
    fi
    part1=`echo $1 | awk -F "." '{print $1}'`
    part2=`echo $1 | awk -F "." '{print $2}'`
    rt_float_to_string=${part1:-0}p${part2:-0}
    echo $rt_float_to_string
}

function produce_postfix()
{
    if [[ $# -ne 3 ]]
    then
        echo -e "\033[1;31merror:${NC} invalid argument number - produce_postfix()"
        return 1
    fi
    echo ${COLSYST[$1]}_${tMC[${ISMC[$1]}]}_${RECOGEN[$3]}_jetpt_$(float_to_string ${JETPTMIN[$2]})_jeteta_$(float_to_string ${JETETAMIN[$2]})_$(float_to_string ${JETETAMAX[$2]})_${HLTOPT}
}

#
FOLDERS=("plotfits" "plotxsecs" "ploteff" "rootfiles" "plots")
for i in ${FOLDERS[@]}
do
    if [[ ! -d $i ]]
    then
	mkdir -p $i
    fi
done

PLOTFOLDERS=("hDEta" "hDPhi" "hDdelEta" "hDdelPhi" "hJetEta" "hJetPhi" "hCorr" "hDphivsDtrk1hit" "hDphivsDtrk2hit" "hDphivsDtrk1algo" "hDphivsDtrk2algo")
cd plots
for j in ${PLOTFOLDERS[@]}
do
    if [[ ! -d $j ]]
    then
        mkdir -p $j
    fi
done
cd ..


##

# djtana_savetpl_corr.C + djtana_savehist.C #
g++ djtana_savetpl_corr.C $(root-config --cflags --libs) -g -o djtana_savetpl_corr.exe || return 1;
g++ djtana_plothist.C $(root-config --cflags --libs) -g -o djtana_plothist.exe || return 1;
g++ djtana_tree.C $(root-config --cflags --libs) -g -o djtana_tree.exe || return 1;


for i in ${iCOL[@]}
do
    for j in ${jJET[@]}
    do
        for k in ${kRECOGEN[@]}
        do
                if [[ k -eq 0 || ${ISMC[i]} -eq 1 ]] # only RecoD_RecoJet will run for data
                then
                    tPOSTFIX=Djet_$(produce_postfix $i $j $k)
                    cd plots
                    if [[ ! -d ${tPOSTFIX} ]]
                    then
                        mkdir -p ${tPOSTFIX}
                    fi
                    cd ..
                    if [[ $DO_SAVETPL -eq 1 ]]
                    then
                        echo -e "-- Processing ${FUNCOLOR}djtana_savetpl_corr.C${NC} :: ${ARGCOLOR}${COLSYST[i]}${NC} - ${ARGCOLOR}${tMC[${ISMC[i]}]}${NC} - ${ARGCOLOR}${RECOGEN[k]}${NC}"
                        ./djtana_savetpl_corr.exe "${INPUTDANAME[i]}" "rootfiles/masstpl_${tPOSTFIX}" "${COLSYST[i]}" ${ISMC[i]} $k ${JETPTMIN[j]} ${JETETAMIN[j]} ${JETETAMAX[j]} &
                        echo
                    fi
                    if [[ $DO_PLOTHIST -eq 1 ]]
                    then
                        echo -e "-- Processing ${FUNCOLOR}djtana_plothist.C${NC} :: ${ARGCOLOR}${COLSYST[i]}${NC} - ${ARGCOLOR}${tMC[${ISMC[i]}]}${NC} - ${ARGCOLOR}${RECOGEN[k]}${NC}"
                        ./djtana_plothist.exe "rootfiles/masstpl_${tPOSTFIX}" "${tPOSTFIX}" "${COLSYST[i]}" ${ISMC[i]} ${JETPTMIN[j]} ${JETETAMIN[j]} ${JETETAMAX[j]} &
                        echo
                    fi 
                    if [[ $DO_USEHIST -eq 1 && l -eq 0 ]]
                    then
                        echo -e "-- Processing ${FUNCOLOR}djtana_tree.C${NC} :: ${ARGCOLOR}${COLSYST[i]}${NC} - ${ARGCOLOR}${tMC[${ISMC[i]}]}${NC} - ${ARGCOLOR}${RECOGEN[k]}${NC}"
                        ./djtana_tree.exe "${INPUTDANAME[i]}" "${tPOSTFIX}" "${COLSYST[i]}" ${ISMC[i]} $k ${JETPTMIN[j]} ${JETETAMIN[j]} ${JETETAMAX[j]} &
                    fi
                fi
        done
    done
done

wait
if [[ $DO_PLOTHIST -eq 1 ]]
then
    rm djtana_plothist.exe
fi
if [[ $DO_SAVETPL -eq 1 ]]
then
    rm djtana_savetpl_corr.exe
fi
if [[ $DO_USEHIST -eq 1 ]]
then
    rm djtana_tree.exe
fi
