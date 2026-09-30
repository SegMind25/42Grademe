# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    auto_correc_main.sh                                :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/20 02:26:11 by jcluzet           #+#    #+#              #
#    Updated: 2022/12/14 15:24:37 by jcluzet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# usage: bash auto_correc_main.sh <file.c> <assign> [args...]
# Compiles the reference solution and the student's rendu, runs both with the
# same arguments and writes a traceback in .system/grading/ on any difference.

FILE="../../rendu/$2/$1"
MAIN='main.c'
TIMEOUT_SEC=20

rm -f .system/grading/traceback

cd .system/grading || exit 1

gcc -o source "$1" $MAIN 2>/dev/null
./source "${@:3}" | cat -e > sourcexam
rm -f source final finalexam .dev

gcc -o final "$FILE" $MAIN 2>.dev
compiled=0
timeout=0
if [ -e final ]; then
    compiled=1
    ( ./final "${@:3}" 2>/dev/null | cat -e > finalexam ) &
    PID=$!
    # poll every 0.1s, give up after TIMEOUT_SEC seconds
    ticks=0
    while kill -0 "$PID" 2>/dev/null; do
        if [ "$ticks" -ge $((TIMEOUT_SEC * 10)) ]; then
            timeout=1
            pkill -KILL -P "$PID" 2>/dev/null
            kill -KILL "$PID" 2>/dev/null
            break
        fi
        if [ "$ticks" -gt 0 ] && [ $((ticks % 50)) -eq 0 ]; then
            echo "waiting..."
        fi
        sleep 0.1
        ticks=$((ticks + 1))
    done
    wait "$PID" 2>/dev/null
else
    : > finalexam
fi

if [ $compiled -eq 0 ] || [ $timeout -eq 1 ] || ! diff -q sourcexam finalexam >/dev/null 2>&1; then
    {
        echo "----------------8<-------------[ START TEST "
        printf "        💻 TEST\n./a.out "
        for arg in "${@:3}"; do
            printf '"%s" ' "$arg"
        done
        printf "\n"
        if [ $compiled -eq 0 ]; then
            cat .dev
            printf "\n        ❌ COMPILATION ERROR\n"
        else
            printf "        🔎 YOUR OUTPUT:\n"
            cat finalexam
            if [ $timeout -eq 1 ]; then
                printf "   ❌ TIMEOUT (more than %ss)\n" "$TIMEOUT_SEC"
            else
                printf "        🗝 EXPECTED OUTPUT:\n"
                cat sourcexam
            fi
        fi
        echo "----------------8<------------- END TEST ]"
    } >> traceback
fi

rm -f final finalexam sourcexam .dev
cd ../..
