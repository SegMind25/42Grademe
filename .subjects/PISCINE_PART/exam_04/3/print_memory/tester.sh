#!/bin/bash
# Auto-generated grader: your function is compiled with main.c and
# compared with the reference on each test.

FILE='print_memory.c'
ASSIGN='print_memory'

bash .system/auto_correc_main.sh $FILE $ASSIGN 1
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_main.sh $FILE $ASSIGN 2
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_main.sh $FILE $ASSIGN 3
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_main.sh $FILE $ASSIGN 4
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_main.sh $FILE $ASSIGN 5
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_main.sh $FILE $ASSIGN 6
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

touch .system/grading/passed
