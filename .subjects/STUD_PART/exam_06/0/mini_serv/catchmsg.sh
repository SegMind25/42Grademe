#!/bin/bash

# close fd before init
exec 6<&-
exec 6</dev/tcp/127.0.0.1/"$1"

while read -r <&6
do
    echo "$REPLY"
done
