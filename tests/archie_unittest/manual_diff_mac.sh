#!/bin/bash
OG_COR="cor_bin/mac/corewar"
OUR_COR="../../corewar"
PATH_TO_PLAYER="../valid_asm/"
PLAYER="vm_test"

if [ -z "$1" ]
  then
    DUMP=5
    else
    DUMP=$1
fi
echo $DUMP


rm diff/og_output diff/our_output
$OG_COR $PATH_TO_PLAYER$PLAYER.cor -d $DUMP > diff/og_output
$OUR_COR $PATH_TO_PLAYER$PLAYER.cor -d $DUMP > diff/our_output
if ! cmp -s "diff diff/og_output" "diff/our_output"; then
    echo '-----no diff'
fi