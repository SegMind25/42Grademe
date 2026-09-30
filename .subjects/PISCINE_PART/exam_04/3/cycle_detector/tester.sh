#!/bin/bash
# Auto-generated grader: your function is compiled with main.c and
# compared with the reference on each test.

FILE='cycle_detector.c'
ASSIGN='cycle_detector'

bash .system/auto_correc_main.sh $FILE $ASSIGN 0 -1
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_main.sh $FILE $ASSIGN 1 -1
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_main.sh $FILE $ASSIGN 1 0
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_main.sh $FILE $ASSIGN 5 -1
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_main.sh $FILE $ASSIGN 5 0
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_main.sh $FILE $ASSIGN 5 4
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_main.sh $FILE $ASSIGN 5 2
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_main.sh $FILE $ASSIGN 1000 500
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_main.sh $FILE $ASSIGN 1000 -1
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_main.sh $FILE $ASSIGN 2 0
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_main.sh $FILE $ASSIGN 2 1
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

touch .system/grading/passed
