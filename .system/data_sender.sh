#!/bin/bash
# Anonymous usage log. Never blocks the exam: short timeout, all output discarded.
userpost="user=$LOGNAMELOG42EXAM"
os="os=$(uname)"
time="time=$(date '+%F_%H:%M:%S')"
usingpost="using=$1"

curl -s --max-time 5 -X POST -F "$userpost" -F "$usingpost" -F "$os" -F "$time" \
    "https://user.grademe.fr/exam.php" >/dev/null 2>&1
exit 0
