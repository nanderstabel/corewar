#!/bin/bash 

OS=$(uname -s)
if [ $OS == Linux ]
    then
        OG_ASM="./cor_bin/lin/asm"
else
    OG_ASM="./cor_bin/mac/asm"
fi

# rm valid_asm/*.cor
# rm valid_asm/.*.cor
for file in $@; do
	echo $file
	$OG_ASM "${file}"
	sleep 1
done
mv ../valid_asm/*.cor ../valid_asm/valid_cor/