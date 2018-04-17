#!/bin/bash

DO_SAVETPL=0

DO_USEHIST=1
DO_PLOTHIST=0
DO_PLOTRATIO=0

./dodjtana_2Dbins.sh $DO_SAVETPL
./dodjtana_1Dbins.sh $DO_SAVETPL

./dopdfvariation_2Dbins.sh $DO_USEHIST $DO_PLOTHIST 
./dopdfvariation_1Dbins.sh $DO_USEHIST $DO_PLOTHIST
./dopdfvar_ratio_2Dbins.sh $DO_PLOTRATIO
./dopdfvar_ratio_1Dbins.sh $DO_PLOTRATIO