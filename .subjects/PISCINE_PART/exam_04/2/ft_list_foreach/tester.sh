#!/bin/bash
# Auto-generated grader: your function is compiled with main.c and
# compared with the reference on each test.

FILE='ft_list_foreach.c'
ASSIGN='ft_list_foreach'

bash .system/auto_correc_main.sh $FILE $ASSIGN
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_main.sh $FILE $ASSIGN hello
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_main.sh $FILE $ASSIGN hello world 42 abc
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_main.sh $FILE $ASSIGN Already upper '' x
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

touch .system/grading/passed
