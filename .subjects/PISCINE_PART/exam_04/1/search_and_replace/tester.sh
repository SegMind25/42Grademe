# **************************************************************************** #
#                                                                              #
#    tester.sh                                          :+:      :+:    :+:    #
#                                                     +#+  +:+       +#+       #
#                                                     +#+#+#+#+#+   +#+        #
#                                                                              #
# **************************************************************************** #

FILE='search_and_replace.c'
ASSIGN='search_and_replace'

bash .system/auto_correc_program.sh $FILE $ASSIGN "My life for Aizr" "z" "u"
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN "gaetan" "art" "zul"
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN "ol is at home" "ol" "w"
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN "zaz" "r" "u"
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN "jacob" "a" "b" "c" "e"
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN "In foct, stoff crew ore very nice. They like metol." "o" "a"
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

touch .system/grading/passed;
