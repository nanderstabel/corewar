#!/bin/bash
OG_COR="cor_bin/lin/corewar"
OUR_COR="../../corewar"
PATH_TO_PLAYER="../valid_asm/"
PLAYER="vm_test"

DUMP=0
rm diff/og_output diff/our_output
$OG_COR $PATH_TO_PLAYER$PLAYER.cor -d $DUMP > diff/og_output
$OUR_COR $PATH_TO_PLAYER$PLAYER.cor -d $DUMP > diff/our_output
if ! cmp -s "diff diff/og_output" "diff/our_output"; then
    echo '-----no diff'
fi