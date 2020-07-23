#!/bin/bash
OG_COR="cor_bin/mac/corewar"
OUR_COR="../../corewar"
PATH_TO_PLAYER="../valid_asm/"
PLAYER="vm_test"

DUMP=5
rm diff/og_output diff/our_output
$OG_COR $PATH_TO_PLAYER$PLAYER.cor -d $DUMP > diff/og_output
$OUR_COR $PATH_TO_PLAYER$PLAYER.cor -d $DUMP > diff/our_output
if ! cmp -s "diff diff/og_output" "diff/our_output"; then
    printf '-----no diff'
fi