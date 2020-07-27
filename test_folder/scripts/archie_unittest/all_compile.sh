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
for file in $@; do
	echo $files
	$OG_ASM $file
done
	mv ../valid_asm/*.cor ../valid_asm/valid_cor/