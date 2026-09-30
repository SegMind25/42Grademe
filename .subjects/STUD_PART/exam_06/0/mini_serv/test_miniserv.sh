#!/bin/bash
# usage: bash test_miniserv.sh <port>   (run from .system/grading)
# Starts the student's server, connects a listener (catchmsg.sh) and several
# short-lived clients, then stores everything the listener received in `bim`.
# Only uses bash's /dev/tcp, so it does not depend on the installed nc flavor.

PORT=$1
rm -f bim trace final

fail()
{
    {
        echo "----------------8<-------------[ START TEST "
        printf "%b" "$1"
        echo "----------------8<------------- END TEST ]"
    } >> traceback
}

send_msg()
{
    exec 3<>"/dev/tcp/127.0.0.1/$PORT" || return 1
    cat >&3
    exec 3>&-
}

# 0 = listening, 1 = not listening, 2 = no tool available to check
port_listening()
{
    if command -v ss >/dev/null 2>&1; then
        ss -tln 2>/dev/null | grep -q "[.:]$PORT "
    elif command -v lsof >/dev/null 2>&1; then
        lsof -nP -iTCP:"$PORT" -sTCP:LISTEN >/dev/null 2>&1
    elif command -v netstat >/dev/null 2>&1; then
        netstat -an 2>/dev/null | grep -E "[.:]$PORT " | grep -q LISTEN
    else
        return 2
    fi
}

CC=$(command -v clang || command -v cc || command -v gcc)
if ! "$CC" -o final ../../rendu/mini_serv/mini_serv.c > trace 2>&1 || [ ! -e final ]; then
    fail "        🔎 YOUR OUTPUT:\n$(cat trace)\n        ❌ COMPILATION ERROR\n"
    exit 1
fi

SERVER=""
CATCH=""

cleanup()
{
    # stop the server first: the listener then reads EOF and flushes `bim`
    [ -n "$SERVER" ] && kill "$SERVER" 2>/dev/null
    [ -n "$SERVER" ] && wait "$SERVER" 2>/dev/null
    if [ -n "$CATCH" ]; then
        for _ in $(seq 1 20); do
            kill -0 "$CATCH" 2>/dev/null || break
            sleep 0.1
        done
        kill "$CATCH" 2>/dev/null
        wait "$CATCH" 2>/dev/null
    fi
}
trap cleanup EXIT

# start the server and wait (max 3s) until it listens
# 0 = listening, 1 = never listened, 2 = the process exited (e.g. bind failed)
start_server()
{
    ./final "$PORT" > /dev/null 2>&1 &
    SERVER=$!
    for _ in $(seq 1 30); do
        port_listening
        case $? in
            0) return 0 ;;
            2) sleep 1; kill -0 "$SERVER" 2>/dev/null && return 0 || return 2 ;;
        esac
        kill -0 "$SERVER" 2>/dev/null || return 2
        sleep 0.1
    done
    return 1
}

# A port can still be busy (TIME_WAIT) right after a previous run, which
# makes bind() fail: if the server exits at startup, retry on other ports.
attempt=1
while true; do
    start_server
    status=$?
    [ $status -eq 0 ] && break
    kill "$SERVER" 2>/dev/null
    wait "$SERVER" 2>/dev/null
    SERVER=""
    if [ $status -eq 1 ] || [ $attempt -ge 5 ]; then
        fail "        ❌ PORT IS NOT OPEN \n        💻 TEST\n./a.out $PORT\n Connecting after the server is started\n        Cannot connect to port $PORT\n"
        exit 1
    fi
    attempt=$((attempt + 1))
    PORT=$(bash findport.sh $((PORT + 1)))
done

bash catchmsg.sh "$PORT" >> bim &
CATCH=$!
sleep 1

echo "Si vous ne voyez QUE ce message, c'est mauvais signe." | send_msg
sleep 0.2
echo "Bienvenue sur le test de votre miniserv" | send_msg
sleep 0.2
echo "Ceci est un message" | send_msg
sleep 0.2
printf "Voici un texte sans retour a la ligne" | send_msg
sleep 0.2
echo -n "This is a text without backline at the end" | send_msg
sleep 0.4
printf "Et voici un texte avec plusieurs\nretours\na\nla\nligne\n" | send_msg
sleep 0.2

bash test_eof.sh "$PORT"
sleep 1

send_msg < very_long_msg.txt
sleep 1

send_msg < other_long_msg.txt
sleep 2
