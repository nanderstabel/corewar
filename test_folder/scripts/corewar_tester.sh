#!/bin/bash
OUR_COR="../../corewar"
DIR="../vm_test_folder/valid_cor_files/"
FIX_DIR="../vm_test_folder/need_fixing/"
REG_NUM='^[0-9]+$'
FLAG=""
DUMP=12000
FLAG_OG=""
ALL=0
FLAGS_ARRAY_OG=("-v 4" "-v 16" "-v 8" "-v 2" "-v 1" "")
FLAGS_ARRAY_OUR=("-a" "-b" "-c" "-e" "-f" "")
NUM_OF_FLAGS=6
LOG_FILE="../vm_test_folder/logs/error.log"

USAGE="Usage: ./manual_diff [ -a | -b | -c | -e | -f ] | & [ -d N ] <champion.cor\n\t-a\t: Equivalent to original -v  4\n\t-b\t: Equivalent to original -v 16\n\t-c\t: Equivalent to original -v  8\n\t-e\t: Equivalent to original -v  2\n\t-f\t: Equivalent to original -v  1\n\t-d N\t: Number of cycles befor dump. Default is 12000 cycles\n"

if [ -z "$(ls -A $DIR)" ]; then
    ./all_compile.sh ../asm_test_folder/valid_s_files/*.s
fi

if ! [ -z "$(ls -A $FIX_DIR)" ]; then
    rm ../vm_test_folder/need_fixing/*.s
    rm ../vm_test_folder/need_fixing/*.cor
fi

if ! [ -z "$(ls -A ../vm_test_folder/logs/)" ]; then
    rm ../vm_test_folder/logs/*.log
fi
touch $LOG_FILE

OS=$(uname -s)
if [ $OS == Linux ]
    then
        OG_COR="../vm_test_folder/binaries/og_corewar_linux"
else
    OG_COR="../vm_test_folder/binaries/og_corewar_mac"
fi

if [ -z "$1" ] || [ "$1" == "-help" ]
    then
        printf "$USAGE" 
        exit 1
fi

if [ "$1" == "-all" ]; then
    ALL=1
    shift
    if [[ "$1" =~ ^- ]]; then
        if [ "$1" != "-d" ]; then
            printf "$USAGE" 
            exit 1
        elif ! [[ $2 =~ $REG_NUM ]] ; then
            printf "$USAGE" 
            exit 1
        else
            shift
            DUMP=$1
            shift
        fi
    fi

else
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
            else
                printf "$USAGE" 
                exit 1
            fi

        fi
    done
fi

PATH_PLAYERS=$@

function    one_file_compare()
{
    for PLAYER in $1; do
    rm diff_folder/our_output diff_folder/og_output
    $OUR_COR $PLAYER $2 -d $4 > diff_folder/our_output
    $OG_COR $PLAYER $3 -d $4 > diff_folder/og_output
    DIFF=$(diff "diff_folder/our_output" "diff_folder/og_output")
    if [ "$DIFF" != "" ]; then
        printf '\033[0m[%10s] ' "$PLAYER"
        printf "\033[0;31mOutput is NOT the same with flag [%s]\n\033[0m" "$2" ;
        diff "diff_folder/our_output" "diff_folder/og_output"
        cp $PLAYER ../vm_test_folder/need_fixing
        filename=$(basename $PLAYER)
        extension="${filename##*.}"
        filename="${filename%.*}"

        cp "../asm_test_folder/valid_s_files/"$filename".s" ../vm_test_folder/need_fixing/
        if [ $ALL == 0 ]; then
            exit 1
        else
            printf "./manual_diff.sh $2 -d $4 $PLAYER\n\n" >> $LOG_FILE
        fi
    else
        printf '\033[0m[%10s] ' "$PLAYER"
        printf '\033[0;32mPerfect! Output is the same until %s cylcles with flag [%s]\n\033[0m' "$4" "$2"
    fi

    done
}

if [ $ALL == 1 ]; then
    for PLAYER in $PATH_PLAYERS; do
        for (( i=0; i <= $DUMP ; i+=100)); do
            INDEX=0
            while (( $INDEX < $NUM_OF_FLAGS )); do
                one_file_compare "$PLAYER" "${FLAGS_ARRAY_OUR[$INDEX]}" "${FLAGS_ARRAY_OG[$INDEX]}" "$i"
                ((INDEX++))
            done
        done
    done

else
    one_file_compare "$PATH_PLAYERS" "$FLAG" "$FLAG_OG" "$DUMP"
fi
