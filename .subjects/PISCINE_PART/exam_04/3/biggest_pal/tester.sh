#!/bin/bash
# Auto-generated grader: each test compares your program with the reference.

FILE='biggest_pal.c'
ASSIGN='biggest_pal'
export ALL_C=1

bash .system/auto_correc_program.sh $FILE $ASSIGN abcba
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN aaaaaaaaaabbcbbaaaa
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN aooibdaoiwhoihwdoinzeldaisaboyobasiadlezfdsfnslk
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN aeibaabaammaabaalek
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN abeb qpinqwjobo qkmnwoiq
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN a
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN ab
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN abcd
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN abaxcdc
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN aaaa
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN ''
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN zzabcdedcbaqqracecarxyzyxracecar
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

touch .system/grading/passed
