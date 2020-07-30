#!/bin/bash
OUR_COR="../../corewar"
REG_NUM='^[0-9]+$'
FLAG=""
DUMP=12000
FLAG_OG=""
USAGE="Usage: ./manual_diff [ -a | -b | -c | -e | -f ] | & [ -d N ] <champion.cor\n\t-a\t: Equivalent to original -v  4\n\t-b\t: Equivalent to original -v 16\n\t-c\t: Equivalent to original -v  8\n\t-e\t: Equivalent to original -v  2\n\t-f\t: Equivalent to original -v  1\n\t-d N\t: Number of cycles befor dump. Default is 12000 cycles\n"

if [ -z "$1" ] || [ "$1" == "-help" ]
    then
        printf "$USAGE" 
        exit 1
fi

OS=$(uname -s)
if [ $OS == Linux ]
    then
        OG_COR="../vm_test_folder/binaries/og_corewar_linux"
else
    OG_COR="../vm_test_folder/binaries/og_corewar_mac"
fi

while [[ "$1" =~ ^- ]]; do
    if [[ "$1" =~ -[a-f] ]]; then
        if [ "$1" == "-d" ]; then
            shift
            if ! [[ $1 =~ $REG_NUM ]] ; then
                printf "$USAGE" 
                exit 1
            else
                DUMP=$1
                shift
            fi

        elif  [ -z "$FLAG" ]; then
            FLAG=$1
            if  [ "$1" == "-a" ]
                then
                    FLAG_OG="-v  4"
                    shift
            elif [ "$1" == "-b" ]
                then
                    FLAG_OG="-v  16"
                    shift
            elif [ "$1" == "-c" ]
                then
                    FLAG_OG="-v  8"
                    shift
            elif [ "$1" == "-e" ]
                then
                    FLAG_OG="-v  2"
                    shift
            elif [ "$1" == "-f" ]
                then
                    FLAG_OG="-v  1"
                    shift
            fi
		fi
	else
		printf "$USAGE" 
		exit 1
    fi
done

PLAYER=$@
rm diff_folder/our_output diff_folder/og_output
$OUR_COR $PLAYER $FLAG -d $DUMP > diff_folder/our_output
$OG_COR $PLAYER $FLAG_OG -d $DUMP > diff_folder/og_output
DIFF=$(diff "diff_folder/our_output" "diff_folder/og_output")
echo $DIFF
if [ "$DIFF" != "" ]
then
	printf '\033[0m[%10s] ' "$PLAYER"
	printf "\033[0;31mOutput is NOT the same\n\033[0m"
	diff "diff_folder/our_output" "diff_folder/og_output"
else
	printf '\033[0m[%10s] ' "$PLAYER"
    printf '\033[0;32mPerfect! Output is the same\n\033[0m'
fi
