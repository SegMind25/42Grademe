#!/bin/bash
# Auto-generated grader: each test compares your program with the reference.

FILE='brackets.c'
ASSIGN='brackets'
export ALL_C=1

bash .system/auto_correc_program.sh $FILE $ASSIGN '(johndoe)'
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN '([)]'
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN '' '{[(0 + 0)(1 + 1)](3*(-1)){()}}'
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN ')('
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN '((('
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN '}'
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN 'no brackets at all'
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN '{[()()]}[]' 'a(b[c{d}e]f)g' '((]'
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN '[' ']'
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN '{{{{{{{{{{}}}}}}}}}}'
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN 'int main(void) { return (tab[i] + f(x)); }'
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

touch .system/grading/passed
