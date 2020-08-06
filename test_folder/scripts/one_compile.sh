# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    one_compile.sh                                     :+:    :+:             #
#                                                      +:+                     #
#    By: mgross <mgross@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2020/07/31 16:23:47 by mgross        #+#    #+#                  #
#    Updated: 2020/07/31 16:23:49 by mgross        ########   odam.nl          #
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
# if [ ${PLAYER:(-2)} != ".s" ]
#     then
#         echo "not a .s file"
#         exit 1
# fi
file=`echo $PLAYER | sed 's/.s$//g'`
echo $file
# echo  "${PLAYER:0:-2}.cor"
$OG_ASM "${file}.s"
mv "${PLAYER:0:-2}.cor" ../vm_test_folder/valid_cor_files/
