#!/bin/bash
# Auto-generated grader: your function is compiled with main.c and
# compared with the reference on each test.

FILE='sort_int_tab.c'
ASSIGN='sort_int_tab'

bash .system/auto_correc_main.sh $FILE $ASSIGN 5 3 9 -1 0 3 2147483647 -2147483648 7
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_main.sh $FILE $ASSIGN 1
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_main.sh $FILE $ASSIGN 3 2 1
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_main.sh $FILE $ASSIGN 1 1 1 0
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_main.sh $FILE $ASSIGN 1 2 3 4 5
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_main.sh $FILE $ASSIGN -5 -10 0 -5 10
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_main.sh $FILE $ASSIGN 42 -7 13 0 99 -100 13 5 8 1 2 3 77 -1 0 6
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

touch .system/grading/passed
