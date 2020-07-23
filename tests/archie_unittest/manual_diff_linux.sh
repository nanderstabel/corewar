#!/bin/bash
OG_COR="cor_bin/lin/corewar"
OUR_COR="../../corewar"
PATH_TO_PLAYER="../valid_asm/valid_cor/"
PLAYER="test_and3"

if [ -z "$1" ]
  then
    DUMP=5
    else
    DUMP=$1
fi

rm diff/og_output diff/our_output
$OG_COR $PATH_TO_PLAYER$PLAYER.cor -d $DUMP > diff/og_output
$OUR_COR $PATH_TO_PLAYER$PLAYER.cor -d $DUMP > diff/our_output
DIFF=$(diff "diff/og_output" "diff/our_output")
if [ "$DIFF" != "" ]
then
  diff "diff/og_output" "diff/our_output"

else
    echo '-----no diff'
fi
