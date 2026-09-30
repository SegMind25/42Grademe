#!/bin/bash
# usage: bash test_eof.sh <port>
# Sends eof_test one word at a time (with a literal ^D inside) on one connection.

PORT=$1

send_msg()
{
    exec 3<>"/dev/tcp/127.0.0.1/$PORT" || return 1
    cat >&3
    exec 3>&-
}

for x in $(cat eof_test); do
    printf "$x"
    sleep 0.1
done | send_msg
