#!/bin/bash 

OS=$(uname -s)
if [ $OS == Linux ]
    then
        OG_ASM="../asm_test_folder/binaries/og_asm_linux"
else
        OG_ASM="../asm_test_folder/binaries/og_asm_mac"
fi

for file in $@; do
	$OG_ASM $file
done
mv ../asm_test_folder/valid_s_files/*.cor ../vm_test_folder/valid_cor_files/