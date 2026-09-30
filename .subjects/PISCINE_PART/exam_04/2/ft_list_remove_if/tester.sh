#!/bin/bash
# Auto-generated grader: your function is compiled with main.c and
# compared with the reference on each test.

FILE='ft_list_remove_if.c'
ASSIGN='ft_list_remove_if'

bash .system/auto_correc_main.sh $FILE $ASSIGN a a b a c a
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_main.sh $FILE $ASSIGN x a b c
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_main.sh $FILE $ASSIGN a a a a
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_main.sh $FILE $ASSIGN a
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_main.sh $FILE $ASSIGN c a b c
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_main.sh $FILE $ASSIGN b a b c
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_main.sh $FILE $ASSIGN hello hello world hello
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

touch .system/grading/passed
