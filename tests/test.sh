#!/bin/bash 

for file in $@; do
	echo $file
	./vm-champ-linux/asm $file
	file=`echo $file | sed 's/.s$//g'`
	mv "${file}.cor" "${file}_2.cor"
	../asm "${file}.s"
	sleep 1
	diff <(xxd "${file}.cor") <(xxd "${file}_2.cor")
done
