#!/bin/bash 

OS=$(uname -s)
if [ $OS == Linux ]
    then
        OG_ASM="../asm_test_folder/binaries/og_asm_linux"
else
    OG_ASM="../asm_test_folder/binaries/og_asm_mac"
fi

rm valid_asm/*.cor
rm valid_asm/.*.cor
for file in $@; do
	echo $file
	../asm_test_fol/asm $file
	file=`echo $file | sed 's/.s$//g'`
	mv "${file}.cor" "${file}_2.cor"
	../asm "${file}.s"
	sleep 1
	diff <(xxd "${file}.cor") <(xxd "${file}_2.cor")
done
