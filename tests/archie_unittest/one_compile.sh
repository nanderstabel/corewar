#!/bin/bash 
​
OS=$(uname -s)
if [ $OS == Linux ]
    then
        OG_ASM="./cor_bin/lin/asm"
else
    OG_ASM="./cor_bin/mac/asm"
fi
​
if [ -z "$1" ]
then
    echo "no path"
else
    file=`echo $1 | sed 's/.s$//g'`
    $OG_ASM "${file}.s"
    mv ../valid_asm/"${file}.cor" ../valid_asm/valid_cor/
fi