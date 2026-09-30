#!/bin/bash
# Auto-generated grader: each test compares your program with the reference.

FILE='rpn_calc.c'
ASSIGN='rpn_calc'
export ALL_C=1

bash .system/auto_correc_program.sh $FILE $ASSIGN '1 2 * 3 * 4 +'
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN '1 2 3 4 +'
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN '3 4 +'
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN '5 10 9 / - 50 *'
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN '3 1 2 * * 4 -'
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN '1 0 /'
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN '1 0 %'
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN '10 3 %'
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN '-7 2 /'
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN '2 3 4 * +'
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN '1 +'
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN +
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN ''
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN '1 2'
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN 'a b +'
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN '  7   2   -  '
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN '3 4 5 + * 2 -'
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN 42
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN '-5 -5 *'
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN '2 3 -'
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN '2147483647 0 +'
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN '1 2 + +'
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN '3 4+'
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN '1 2 +' extra
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

touch .system/grading/passed
