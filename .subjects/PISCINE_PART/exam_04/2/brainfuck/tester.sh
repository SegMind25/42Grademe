#!/bin/bash
# Auto-generated grader: each test compares your program with the reference.

FILE='brainfuck.c'
ASSIGN='brainfuck'
export ALL_C=1

bash .system/auto_correc_program.sh $FILE $ASSIGN '++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.'
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN '+++++[>++++[>++++H>+++++i<<-]>>>++\n<<<<-]>>--------.>+++++.>.'
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN '++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.'
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN '++++++[>++++++++<-]>+.+.+.>++++++++++.'
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN 'This is a comment: +++++++++[>++++++++<-]>. and the end'
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN '[.+]++++++++++[>+++++++<-]>-.'
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN '>+++++[<++++++++++>-]<++.[-]>+++++[<++++++++++>-]<.[-]>+++[<++++++++++>-]<++.[-]>+++++++++[<++++++++++>-]<++++++++.[-]>+++++++++++[<++++++++++>-]<+.[-]>+++++++++++[<++++++++++>-]<++++.[-]>+++++++++++[<++++++++++>-]<.[-]>+++++[<++++++++++>-]<.[-]>+++++++++[<++++++++++>-]<+++++++++.[-]>+++++++++++[<++++++++++>-]<+.[-]>++++++++++[<++++++++++>-]<.[-]>++++++++++[<++++++++++>-]<+.[-]>+[<++++++++++>-]<.[-]'
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN '+++++[>+++++++++<-]>+++.<+++[>----<-]>.<++[>+++++++<-]>+.'
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
    exit 1
fi

touch .system/grading/passed
