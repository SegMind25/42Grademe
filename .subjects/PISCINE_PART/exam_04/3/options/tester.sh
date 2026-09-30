#!/bin/bash
# Auto-generated grader: each test compares your program with the reference.

FILE='options.c'
ASSIGN='options'
export ALL_C=1

bash .system/auto_correc_program.sh $FILE $ASSIGN
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN -abc -ijk
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN -z
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN -abc -hijk
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN -%
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN -h
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN -a
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN -y -x
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN -abcdefgijklmnopqrstuvwxyz
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN -a -%
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN -aaa
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN -A
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN -q -w -e -r -t -y
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

touch .system/grading/passed
