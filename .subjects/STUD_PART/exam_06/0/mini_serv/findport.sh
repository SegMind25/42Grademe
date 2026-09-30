#!/bin/bash
# Print the first free TCP port in [first_port, last_port]
# (default: a random start in 8888-9887, so back-to-back runs use other ports).
# Works with ss (Linux), lsof (macOS/Linux) or netstat, whichever is installed.

first_port=${1:-$((8888 + RANDOM % 1000))}
last_port=${2:-$((first_port + 1000))}

port_in_use()
{
    if command -v ss >/dev/null 2>&1; then
        ss -tuln 2>/dev/null | grep -q "[.:]$1 "
    elif command -v lsof >/dev/null 2>&1; then
        lsof -nP -iTCP:"$1" -sTCP:LISTEN >/dev/null 2>&1
    elif command -v netstat >/dev/null 2>&1; then
        netstat -an 2>/dev/null | grep -E "[.:]$1 " | grep -q LISTEN
    else
        # last resort: something accepts connections on this port
        (exec 3<>"/dev/tcp/127.0.0.1/$1") 2>/dev/null
    fi
}

for ((port = first_port; port <= last_port; port++)); do
    if ! port_in_use "$port"; then
        echo "$port"
        exit 0
    fi
done
echo 0
