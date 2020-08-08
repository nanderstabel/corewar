#!/bin/bash
OS=$(uname -s)
if [ $OS == Linux ]
    then
        OG_COR="../asm_test_folder/binaries/og_asm_linux"
else
    OG_COR="../asm_test_folder/binaries/og_asm_mac"
fi

rm ../asm_test_folder/valid_s_files/*.cor
for file in $@; do
	# echo $file
	$OG_COR $file
	file=`echo $file | sed 's/.s$//g'`
	mv "${file}.cor" "${file}_2.cor"
	../../asm "${file}.s"
	sleep 1
	diff <(xxd "${file}.cor") <(xxd "${file}_2.cor")
done
