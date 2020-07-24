#!/bin/bash
OG_COR="cor_bin/lin/corewar"
OUR_COR="../../corewar"
# PATH_TO_PLAYER="../valid_asm/valid_cor/"
PLAYER=$1

if [ -z "$2" ]
  then
    DUMP=5
    else
    DUMP=$2
fi

rm diff/og_output diff/our_output
$OG_COR $PLAYER -d $DUMP > diff/og_output
$OUR_COR $PLAYER -d $DUMP > diff/our_output
DIFF=$(diff "diff/our_output" "diff/og_output")
if [ "$DIFF" != "" ]
then
  diff "diff/og_output" "diff/our_output"

else
    echo '-----no diff'
fi
