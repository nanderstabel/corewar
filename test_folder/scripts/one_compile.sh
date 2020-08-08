# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    one_compile.sh                                     :+:    :+:             #
#                                                      +:+                     #
#    By: mgross <mgross@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2020/07/31 16:23:47 by mgross        #+#    #+#                  #
#    Updated: 2020/08/08 09:43:53 by mgross        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

OS=$(uname -s)
if [ $OS == Linux ]
    then
        OG_ASM="../asm_test_folder/binaries/og_asm_linux"
else
    OG_ASM="../asm_test_folder/binaries/og_asm_mac"
fi

if [ -z "$1" ]
then
    echo "no path"
fi

PLAYER=$1
file=`echo $PLAYER | sed 's/.s$//g'`
echo $file
$OG_ASM "${file}.s"
mv "${PLAYER:0:-2}.cor" ../vm_test_folder/valid_cor_files/
