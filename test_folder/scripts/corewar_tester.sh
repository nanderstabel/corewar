#!/bin/bash
OUR_COR="../../corewar"
DIR="../vm_test_folder/valid_cor_files/"

USAGE="Usage: ./corewar_tester [ -a | -b | -c ] <champion.cor [ N ]\n\t-a\t: Tequivalent to original -v  4\n\t-b\t: Tequivalent to original -v 16\n\t-b\t: Tequivalent to original -v  8\n\t N\t: Number of cycles befor dump. Default is 1000 cycles\n"

if [ -z "$(ls -A $DIR)" ]; then
    ./all_compile.sh ../asm_test_folder/valid_s_files/*.s
fi

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
# echo $@
if [ "$1" == "-a" ] || [ "$1" == "-b" ] || [ "$1" = "-c" ] || [ "$1" = "-e" ] || [ "$1" = "-f" ]
    then
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
elif [ "$1" != "-all" ] && [ "$1" != "-d" ]
    then
    printf "$USAGE" 
    exit 1
fi

if [ "$1" == "-all" ]
then
    ALL=1
    shift
else
    ALL=0
fi

if [ "$1" == "-d" ]
  then
    shift
    DUMP=$1
    shift
    else
        DUMP=12000
fi

if [ -z "$1" ]
    then
    printf "$USAGE" 
        exit  1
fi

PATH_PLAYERS=$@

function    one_file_compare()
{
    for PLAYER in $PATH_PLAYERS; do
    rm diff_folder/our_output diff_folder/og_output
    $OUR_COR $PLAYER $FLAG -d $DUMP > diff_folder/our_output
    $OG_COR $PLAYER $FLAG_OG -d $DUMP > diff_folder/og_output
    DIFF=$(diff "diff_folder/our_output" "diff_folder/og_output")
    # echo $DIFF
    if [ "$DIFF" != "" ]
    then
        printf '\033[0m[%10s] ' "$PLAYER"
        printf "\033[0;31mOutput is NOT the same with flag [%s]\n\033[0m" "$FLAG" ;
        diff "diff_folder/our_output" "diff_folder/og_output"
        cp $PLAYER ../vm_test_folder/need_fixing
        filename=$(basename $PLAYER)
        extension="${filename##*.}"
        filename="${filename%.*}"

        cp "../asm_test_folder/valid_s_files/"$filename".s" ../vm_test_folder/need_fixing/
        if [ $ALL == 0 ]
        then
            exit 1
        fi
    else
        printf '\033[0m[%10s] ' "$PLAYER"
        printf '\033[0;32mPerfect! Output is the same until %s cylcles\n\033[0m' "$DUMP"
    fi

    done
}

if [ $ALL == 1 ]
then
    # CYCLES=30000
    # for (( i=1; ( ( i <= $CYCLES ) && ( $error == 0 ) ) ; i+=100))
    echo "ALL"
else
    one_file_compare
fi

# ${PLAYER:0:-3}s

# function    test_players()
# {
#     # CYCLES=10000
#     error=0

#     for player in $PATH_PLAYERS
#     do
#         ((error=0))
#         # echo $player
#         for (( i=1; ( ( i <= $CYCLES ) && ( $error == 0 ) ) ; i+=100))
#         do
#             $PATH_ORGN_CW $player -d $i | sed -n -e '/^0x/p' > diff/origin_output1
#             $OUR_COR $player -dump $i | sed -n -e'/^0x/p' > diff/yours_output2
#             if ! cmp -s "diff/origin_output1" "diff/yours_output2"; then
#                 printf '\033[0m[%10s] ' "$player"
#                 ((i=i-1))
#                 printf "\033[0;31mmemory is NOT the same at cycle [%d]\n\033[0m" "$i" ;
#                 ((error=1))
#             fi
#         done
#         if [ $error == 0 ] ; then
#             printf '\033[0m[%10s] ' "$player"
#             ((i=i-1))
#             printf '\033[0;32mPerfect! Memory is the same at all cycles until %s\n\033[0m' "$i"
#         fi
#         ((error=0))
#     done
# }

# if [ "$1" == "-help" ] ; then
#     echo "usage: sh vm_tester.sh <filename1.cor> <filename2.cor> <cycles>"
#     exit 1
# elif [ $# -lt 2 ] ; then
#     test_players
#     exit 1
# fi

# CYCLES=${@: -1}
# n=$(($# - 1))
# for arg do
#     [ "$n" -gt 0 ] && set -- "$@" "$arg"
#     shift
#     n=$((n - 1))
# done
# for arg do
#     if [ ! -f $arg ]; then
#         echo "error: file $arg does not exist" ; exit 1
#     fi
# done
# re='^[0-9]+$'
# if ! [[ $CYCLES =~ $re ]]; then
#     echo "error: $CYCLES is not a number" >&2 ; exit 1
# fi
# for (( i=1; i <= $CYCLES; i+=10))
# do
#     $PATH_ORGN_CW $@ -d $i | sed -n -e '/^0x/p' > diff/origin_output1
#     $OUR_COR $@ -dump $i | sed -n -e'/^0x/p' > diff/yours_output2
#     if ! cmp -s "diff/origin_output1" "diff/yours_output2"; then
#         printf "\033[0;31mmemory is NOT the same at cycle [%d]\n\033[0m" "$i" ; exit 1
#     fi
# done
#     printf '\033[0;32mperfect! memory is the same at all cycles until %s\n\033[0m' "$CYCLES"

