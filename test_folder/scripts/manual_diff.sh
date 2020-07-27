#!/bin/bash
OUR_COR="../../corewar"
# PATH_TO_PLAYER="../valid_asm/valid_cor/"
PLAYER=$1

if [ -z "$2" ]
  then
    DUMP=5
    else
    DUMP=$2
fi

OS=$(uname -s)
if [ $OS == Linux ]
    then
        OG_COR="../vm_test_folder/binaries/og_corewar_linux"
else
    OG_COR="cor_bin/mac/corewar"
fi
# echo $OS

rm og_output our_output
$OG_COR $PLAYER -v 4 -d $DUMP > og_output
$OUR_COR $PLAYER -a -d $DUMP > our_output
DIFF=$(diff "our_output" "og_output")
echo $DIFF
if [ "$DIFF" != "" ]
then
  diff "og_output" "our_output"

else
    echo '-----no diff'
fi
