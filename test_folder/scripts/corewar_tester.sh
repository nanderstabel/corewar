# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    corewar_tester.sh                                  :+:    :+:             #
#                                                      +:+                     #
#    By: mgross <mgross@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2020/07/31 16:13:27 by mgross        #+#    #+#                  #
#    Updated: 2020/08/06 23:40:33 by mgross        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

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
INCREMENT=100
FAIL=0
SUCCESS=0
NUM_TESTS=0
ZERO_FLAGS=0
MULTI=0

USAGE="Usage: ./corewar_tester\t- [ -all | & [ -d N ] | & [ -i N ] <champion.cor\n\t\t\t- [ -a | -b | -c | -e | -f ] | & [ -d N ] <champion.cor\n\n\t\t\t-0\t: Run [ -all ] without extra flags\n\t\t\t-all\t: Cycles through all files from given path,\n\t\t\t\t  by default with all flags [ -a, -b, -c, -e, -f ] \n\t\t\t\t  or no flags with [ -0 ] until max dump [ -d N ] \n\t\t\t\t  incremented by given steps [ -i N ]\n\n\t\t\t-a\t: Equivalent to original -v  4\n\t\t\t-b\t: Equivalent to original -v 16\n\t\t\t-c\t: Equivalent to original -v  8\n\t\t\t-e\t: Equivalent to original -v  2\n\t\t\t-f\t: Equivalent to original -v  1\n\t\t\t-d N\t: Number of cycles befor dump. Default is 12000 cycles\n\t\t\t-i N\t: Number to increment cycles befor dump. Default is 100 \n\t\t\t-help\t: Extra info\n"

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
if [ "$1" == "-multi" ]; then
	shift
	MULTI=1
fi

if [ "$1" == "-all" ]; then
    ALL=1
    shift
    while [[ "$1" =~ ^- ]]; do
        if [[ "$1" =~ -[di0] ]]; then
			if [ "$1" == "-0" ]; then
				ZERO_FLAGS=1
				shift
        	elif ! [[ $2 =~ $REG_NUM ]] ; then
            	printf "$USAGE"
            	exit 1
       		else
			   	if [ "$1" == "-d" ]; then
				   shift
				   DUMP=$1
				   shift
				else
            		shift
					INCREMENT=$1
            	shift
				fi
			fi
		else
			printf "$USAGE" 
            exit 1
        fi
    done
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
            fi
        else
            printf "$USAGE" 
            exit 1

        fi
    done
fi

if [ "$MULTI" == 1 ]; then
	rm ../vm_test_folder/valid_cor_files/*.cor
fi

if [ -z "$(ls $DIR)" ]; then
    ./all_compile.sh ../asm_test_folder/valid_s_files/*.s
	rm ../vm_test_folder/valid_cor_files/salamahenagalabadoun.cor
fi

if ! [ -z "$(ls $FIX_DIR)" ]; then
    rm ../vm_test_folder/need_fixing/*.s
    rm ../vm_test_folder/need_fixing/*.cor
fi

if ! [ -z "$(ls ../vm_test_folder/logs/)" ]; then
    rm ../vm_test_folder/logs/*.log
fi
touch $LOG_FILE


function		print_message()
{
	THIRD=$((NUM_TESTS/3))

if ! [ $1 -gt $THIRD ]; then
	printf "\n\n[\e[38;5;9m$1\e[0m/\e[38;5;34m$NUM_TESTS\e[0m]\n\e[0m"
	printf "\n\e[38;5;9m  _      ____ _______ _____    ____  ______   ______ _____  _____   ____  _____   _____               
 | |    / __ \__   __/ ____|  / __ \|  ____| |  ____|  __ \|  __ \ / __ \|  __ \ / ____|              
 | |   | |  | | | | | (___   | |  | | |__    | |__  | |__) | |__) | |  | | |__) | (___                
 | |   | |  | | | |  \___ \  | |  | |  __|   |  __| |  _  /|  _  /| |  | |  _  / \___ \               
 | |___| |__| | | |  ____) | | |__| | |      | |____| | \ \| | \ \| |__| | | \ \ ____) |              
 |______\____/  |_|_|_____/  _\____/|_|__   _|______|_|__\_\_|  \_\\____/|_|__\_\_____/ _____  ______ 
 |  _ \   /\   / ____| |/ / |__   __/ __ \  \ \   / / __ \| |  | |  __ \   / ____/ __ \|  __ \|  ____|
 | |_) | /  \ | |    | ' /     | | | |  | |  \ \_/ / |  | | |  | | |__) | | |   | |  | | |  | | |__   
 |  _ < / /\ \| |    |  <      | | | |  | |   \   /| |  | | |  | |  _  /  | |   | |  | | |  | |  __|  
 | |_) / ____ \ |____| . \     | | | |__| |    | | | |__| | |__| | | \ \  | |___| |__| | |__| | |____ 
 |____/_/    \_\_____|_|\_\    |_|  \____/     |_|  \____/ \____/|_|  \_\  \_____\____/|_____/|______|\n\n- Find your error log in test_folder/vm_folder/logs/ and run the output in the terminal inside test_folder\n- Find the files you failed in ../vm_folder/need_fixing/\n\e[0m"
elif ! [ $1 -gt $((THIRD*2)) ]; then
	printf "\n\n[\e[38;5;208m$1\e[0m/\e[38;5;34m$NUM_TESTS\e[0m]\n\e[0m"
	printf "\e[38;5;208m   _____ _______ _____ _      _        _      ____ _______ _____   _______ ____    _____   ____  
  / ____|__   __|_   _| |    | |      | |    / __ \__   __/ ____| |__   __/ __ \  |  __ \ / __ \ 
 | (___    | |    | | | |    | |      | |   | |  | | | | | (___      | | | |  | | | |  | | |  | |
  \___ \   | |    | | | |    | |      | |   | |  | | | |  \___ \     | | | |  | | | |  | | |  | |
  ____) |  | |   _| |_| |____| |____  | |___| |__| | | |  ____) |    | | | |__| | | |__| | |__| |
 |_____/   |_|  |_____|______|______| |______\____/  |_| |_____/     |_|  \____/  |_____/ \____/ \n\n- Find your error log in test_folder/vm_folder/logs/ and run the output in the terminal inside test_folder\n- Find the files you failed in ../vm_folder/need_fixing/\n\e[0m"
elif ! [ $1 -eq $NUM_TESTS ]; then
	printf "\n\n[\e[38;5;11m$1\e[0m/\e[38;5;34m$NUM_TESTS\e[0m]\n\e[0m"
	printf "\e[38;5;11m  _____  _____  ______ _______ _________     __   _____  ____   ____  _____          
 |  __ \|  __ \|  ____|__   __|__   __\ \   / /  / ____|/ __ \ / __ \|  __ \         
 | |__) | |__) | |__     | |     | |   \ \_/ /  | |  __| |  | | |  | | |  | |        
 |  ___/|  _  /|  __|    | |     | |    \   /   | | |_ | |  | | |  | | |  | |        
 | |    | | \ \| |____   | |     | |     | |    | |__| | |__| | |__| | |__| |        
 |_|    |_|_ \_\______|_ |_|__   |_|__ __|_|__   \_____|\____/_\____/|_____/  ______ 
     /\   | |    |  \/  |/ __ \ / ____|__   __| |__   __| |  | |  ____|  __ \|  ____|
    /  \  | |    | \  / | |  | | (___    | |       | |  | |__| | |__  | |__) | |__   
   / /\ \ | |    | |\/| | |  | |\___ \   | |       | |  |  __  |  __| |  _  /|  __|  
  / ____ \| |____| |  | | |__| |____) |  | |       | |  | |  | | |____| | \ \| |____ 
 /_/    \_\______|_|  |_|\____/|_____/   |_|       |_|  |_|  |_|______|_|  \_\______|\n\n- Find your error log in test_folder/vm_folder/logs/ and run the output in the terminal inside test_folder\n- Find the files you failed in ../vm_folder/need_fixing/\n\e[0m"
else
	printf "\n\n[\e[38;5;34m$1\e[0m/\e[38;5;34m$NUM_TESTS\e[0m]\n\e[0m"
	printf "\e[38;5;34m  _____  ______ _____  ______ ______ _____ _______   _   _   _   _   _ 
 |  __ \|  ____|  __ \|  ____|  ____/ ____|__   __| | | | | | | | | | |
 | |__) | |__  | |__) | |__  | |__ | |       | |    | | | | | | | | | |
 |  ___/|  __| |  _  /|  __| |  __|| |       | |    | | | | | | | | | |
 | |    | |____| | \ \| |    | |___| |____   | |    |_| |_| |_| |_| |_|
 |_|    |______|_|  \_\_|    |______\_____|  |_|    (_) (_) (_) (_) (_)\n\n\e[0m"
 printf "\e[38;5;34m __     ______  _    _ _ _____  ______       __          ________  _____  ____  __  __ ______ 
 \ \   / / __ \| |  | ( )  __ \|  ____|     /\ \        / /  ____|/ ____|/ __ \|  \/  |  ____|
  \ \_/ / |  | | |  | |/| |__) | |__       /  \ \  /\  / /| |__  | (___ | |  | | \  / | |__   
   \   /| |  | | |  | | |  _  /|  __|     / /\ \ \/  \/ / |  __|  \___ \| |  | | |\/| |  __|  
    | | | |__| | |__| | | | \ \| |____   / ____ \  /\  /  | |____ ____) | |__| | |  | | |____ 
    |_|  \____/ \____/  |_|  \_\______| /_/    \_\/  \/   |______|_____/ \____/|_|  |_|______|\n\n\e[0m"
fi

}

PATH_PLAYERS=$@

function	MULTI_player_compare()
{

	rm diff_folder/our_output diff_folder/og_output
	if [ -z "$6" ] && [ -z "$7" ]; then
		$OUR_COR $3 -d $5 "$DIR"$1 "$DIR"$2 > diff_folder/our_output
		$OG_COR $4 -d $5 "$DIR"$1 "$DIR"$2 > diff_folder/og_output
		DIFF=$(diff "diff_folder/our_output" "diff_folder/og_output")
		((NUM_TESTS++))
		if [ "$DIFF" != "" ]; then
			((FAIL++))
			printf '\e[0m[%s + %s] ' "$1" "$2"
			if [ -z "$3" ]; then
				printf "\e[38;5;9mOutput is NOT the same with flag      [-d]\n\e[0m" ;
			else
				printf "\e[38;5;9mOutput is NOT the same with flag [%s] [-d]\n\e[0m" "$3" ;
			fi
			diff "diff_folder/our_output" "diff_folder/og_output"
			printf "./corewar_tester.sh -multi "$3" -d "$5" "$DIR"$1 "$DIR"$2 \n\n" >> $LOG_FILE
			if [ $ALL == 0 ]; then
				print_message "$SUCCESS"
				exit 1
			fi
		else
			((SUCCESS++))
			printf "\e[0m[%s + %s] " "$1" "$2"
			if [ -z "$3" ]; then
					printf "\e[38;5;34mPerfect! Output is the same until %s cycles with flag     [-d]\n\e[0m" "$5"
			else
				printf "\e[38;5;34mPerfect! Output is the same until %s cycles with flag [%s][-d]\n\e[0m" "$5" "$3"
			fi
		fi

	elif [ -z "$7" ]; then
		$OUR_COR $4 -d $6 "$DIR"$1 "$DIR"$2 "$DIR"$3 > diff_folder/our_output
		$OG_COR $5 -d $6 "$DIR"$1 "$DIR"$2 "$DIR"$3 > diff_folder/og_output
		DIFF=$(diff "diff_folder/our_output" "diff_folder/og_output")
		((NUM_TESTS++))
		if [ "$DIFF" != "" ]; then
			((FAIL++))
			printf '\e[0m[%s + %s + %s] ' "$1"  "$2"  "$3"
			if [ -z "$4" ]; then
				printf "\e[38;5;9mOutput is NOT the same with flag      [-d]\n\e[0m" ;
			else
				printf "\e[38;5;9mOutput is NOT the same with flag [%s] [-d]\n\e[0m" "$4" ;
			fi
			diff "diff_folder/our_output" "diff_folder/og_output"
			printf "./corewar_tester.sh -multi "$4" -d "$6" "$DIR"$1 "$DIR"$2 "$DIR"$3 \n\n" >> $LOG_FILE
			if [ $ALL == 0 ]; then
				print_message "$SUCCESS"
				exit 1
			fi
		else
			((SUCCESS++))
			printf "\e[0m[%s + %s + %s] " "$1"  "$2"  "$3"
			if [ -z "$4" ]; then
					printf "\e[38;5;34mPerfect! Output is the same until %s cycles with flag     [-d]\n\e[0m" "$6"
			else
				printf "\e[38;5;34mPerfect! Output is the same until %s cycles with flag [%s][-d]\n\e[0m" "$6" "$4"
			fi
		fi

	else
		$OUR_COR $5 -d $7 "$DIR"$1 "$DIR"$2 "$DIR"$3 "$DIR"$4 > diff_folder/our_output
		$OG_COR $6 -d $7 "$DIR"$1 "$DIR"$2 "$DIR"$3 "$DIR"$4 > diff_folder/og_output
		DIFF=$(diff "diff_folder/our_output" "diff_folder/og_output")
		((NUM_TESTS++))
		if [ "$DIFF" != "" ]; then
			((FAIL++))
			printf '\e[0m[%s + %s + %s + %s] ' "$1"  "$2"  "$3"  "$4"
			if [ -z "$5" ]; then
				printf "\e[38;5;9mOutput is NOT the same with flag      [-d]\n\e[0m" ;
			else
				printf "\e[38;5;9mOutput is NOT the same with flag [%s] [-d]\n\e[0m" "$5" ;
			fi
			diff "diff_folder/our_output" "diff_folder/og_output"
			printf "./corewar_tester.sh -multi "$5" -d "$7" "$DIR"$1 "$DIR"$2 "$DIR"$3 "$DIR"$4\n\n" >> $LOG_FILE
			if [ $ALL == 0 ]; then
				print_message "$SUCCESS"
				exit 1
			fi
		else
			((SUCCESS++))
			printf "\e[%s + %s + %s + %s] " "$1"  "$2"  "$3"  "$4"
			if [ -z "$5" ]; then
					printf "\e[38;5;34mPerfect! Output is the same until %s cycles with flag     [-d]\n\e[0m" "$7"
			else
				printf "\e[38;5;34mPerfect! Output is the same until %s cycles with flag [%s][-d]\n\e[0m" "$7" "$5"
			fi
		fi

	fi

	
	# printf ""$DIR"$1 -- "$DIR"$2 -- "$DIR"$3 -- "$DIR"$4 -- $5 -- $6 -- $7\n"
}

function    one_file_compare()
{
    for PLAYER in $1; do
        filename=$(basename $PLAYER)
        extension="${filename##*.}"
        filename="${filename%.*}"
		if [ "$extension" != "cor" ]; then
			printf '\e[0m[%10s] ' "$PLAYER"
			printf "\e[38;5;9mNot a valid file\n\e[0m"
			exit 1
		fi
		rm diff_folder/our_output diff_folder/og_output
		$OUR_COR $PLAYER $2 -d $4 > diff_folder/our_output
		$OG_COR $PLAYER $3 -d $4 > diff_folder/og_output
		DIFF=$(diff "diff_folder/our_output" "diff_folder/og_output")
		((NUM_TESTS++))
		if [ "$DIFF" != "" ]; then
			((FAIL++))
			printf '\e[0m[%10s] ' "$PLAYER"
			if [ -z "$2" ]; then
				printf "\e[38;5;9mOutput is NOT the same with flag      [-d]\n\e[0m" ;
			else
				printf "\e[38;5;9mOutput is NOT the same with flag [%s] [-d]\n\e[0m" "$2" ;
			fi
			diff "diff_folder/our_output" "diff_folder/og_output"
			cp $PLAYER ../vm_test_folder/need_fixing

			cp "../asm_test_folder/valid_s_files/"$filename".s" ../vm_test_folder/need_fixing/
			printf "./manual_diff.sh $2 -d $4 $PLAYER\n\n" >> $LOG_FILE
			if [ $ALL == 0 ]; then
				print_message "$SUCCESS"
				exit 1
			fi
		else
			((SUCCESS++))
			printf "\e[0m[%10s] " "$PLAYER"
			if [ -z "$2" ]; then
					printf "\e[38;5;34mPerfect! Output is the same until %s cycles with flag     [-d]\n\e[0m" "$4"
			else
				printf "\e[38;5;34mPerfect! Output is the same until %s cycles with flag [%s][-d]\n\e[0m" "$4" "$2"
			fi
		fi

    done
}

if [ $ALL == 1 ] && [ $MULTI != 1 ]; then
    for PLAYER in $PATH_PLAYERS; do
        for (( i=0; i <= $DUMP ; i+=$INCREMENT)); do
            INDEX=0
			if [ $ZERO_FLAGS == 1 ]; then
				one_file_compare "$PLAYER" "" "" "$i"
                ((INDEX++))
			else
				while (( $INDEX < $NUM_OF_FLAGS )); do
					one_file_compare "$PLAYER" "${FLAGS_ARRAY_OUR[$INDEX]}" "${FLAGS_ARRAY_OG[$INDEX]}" "$i"
					((INDEX++))
            	done
			fi
        done
    done
elif [ $MULTI == 1 ]; then
	if [ $ALL != 1 ]; then
		IFS=' ' read -r -a MULTI_PLAYERS <<< "$PATH_PLAYERS"
		while [ ! -z "$MULTI_PLAYERS" ]; do
			in_array=${#MULTI_PLAYERS[*]}
			if [[ $in_array == "4" ]]; then
				MULTI_player_compare "$(basename ${MULTI_PLAYERS[0]})" "$(basename ${MULTI_PLAYERS[1]})" "$(basename ${MULTI_PLAYERS[2]})" "$(basename ${MULTI_PLAYERS[3]})" "$FLAG" "$FLAG_OG" "$DUMP"
			elif [ "$in_array" == "3" ]; then
				MULTI_player_compare "$(basename ${MULTI_PLAYERS[0]})" "$(basename ${MULTI_PLAYERS[1]})" "$(basename ${MULTI_PLAYERS[2]})" "$FLAG" "$FLAG_OG" "$DUMP"
			elif [ "$in_array" == "2" ]; then
				MULTI_player_compare "$(basename ${MULTI_PLAYERS[0]})" "$(basename ${MULTI_PLAYERS[1]})" "$FLAG" "$FLAG_OG" "$DUMP"
			else
				printf "\e[38;5;11mTester stopped. Less then 2 champions to compete\e[0m\n"
				print_message "$SUCCESS" 
				exit 1
			fi
			echo "here111"
			print_message "$SUCCESS" 
				exit 1
		done
	elif [ $ALL == 1 ]; then
		MULTI_PLAYERS=($(ls ../vm_test_folder/valid_cor_files/ | grep -v ".gitignore" | shuf -n 4))
		while [ ! -z "$MULTI_PLAYERS" ]; do
			in_array=${#MULTI_PLAYERS[*]}
			for (( i=0; i <= $DUMP ; i+=$INCREMENT)); do
				INDEX=0
				if [ $ZERO_FLAGS == 1 ]; then
					if [[ $in_array == "4" ]]; then
						MULTI_player_compare ""${MULTI_PLAYERS[0]}"" ""${MULTI_PLAYERS[1]}"" ""${MULTI_PLAYERS[2]}"" ""${MULTI_PLAYERS[3]}"" "" "" "$i" 
					elif [ "$in_array" == "3" ]; then
						MULTI_player_compare ""${MULTI_PLAYERS[0]}"" ""${MULTI_PLAYERS[1]}"" ""${MULTI_PLAYERS[2]}"" "" "" "$i" 
					elif [ "$in_array" == "2" ]; then
						MULTI_player_compare ""${MULTI_PLAYERS[0]}"" ""${MULTI_PLAYERS[1]}"" "" "" "$i"
					else
						printf "\e[38;5;11mTester stopped. Less then 2 champions to compete\e[0m\n"
						exit 1
					fi
					MULTI_player_compare
					((INDEX++))
				else
					while (( $INDEX < $NUM_OF_FLAGS )); do
						if [[ $in_array == "4" ]]; then
							MULTI_player_compare ""${MULTI_PLAYERS[0]}"" ""${MULTI_PLAYERS[1]}"" ""${MULTI_PLAYERS[2]}"" ""${MULTI_PLAYERS[3]}"" "${FLAGS_ARRAY_OUR[$INDEX]}" "${FLAGS_ARRAY_OG[$INDEX]}" "$i" 
						elif [ "$in_array" == "3" ]; then
							MULTI_player_compare ""${MULTI_PLAYERS[0]}"" ""${MULTI_PLAYERS[1]}"" ""${MULTI_PLAYERS[2]}"" "${FLAGS_ARRAY_OUR[$INDEX]}" "${FLAGS_ARRAY_OG[$INDEX]}" "$i" 
						elif [ "$in_array" == "2" ]; then
							MULTI_player_compare ""${MULTI_PLAYERS[0]}"" ""${MULTI_PLAYERS[1]}"" "${FLAGS_ARRAY_OUR[$INDEX]}" "${FLAGS_ARRAY_OG[$INDEX]}" "$i" 
						else
							printf "\e[38;5;11mTester stopped. Less then 2 champions to compete\e[0m\n"
							print_message "$SUCCESS" 
							exit 1
						fi
						((INDEX++))
					done
				fi
			done
			for player in $MULTI_PLAYERS; do
				rm "../vm_test_folder/valid_cor_files/"$player
			done
			MULTI_PLAYERS=($(ls ../vm_test_folder/valid_cor_files/ | grep -v ".gitignore" | shuf -n 4))
		done		
	fi
else
    one_file_compare "$PATH_PLAYERS" "$FLAG" "$FLAG_OG" "$DUMP"
fi

print_message "$SUCCESS" 

