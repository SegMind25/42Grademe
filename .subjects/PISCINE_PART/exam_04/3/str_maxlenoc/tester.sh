# **************************************************************************** #
#                                                                              #
#    tester.sh                                          :+:      :+:    :+:    #
#                                                     +#+  +:+       +#+       #
#                                                     +#+#+#+#+#+   +#+        #
#                                                                              #
# **************************************************************************** #

FILE='str_maxlenoc.c'
ASSIGN='str_maxlenoc'

bash .system/auto_correc_program.sh $FILE $ASSIGN "ab" "bac" "abacabccabcb"
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN "bonjour" "salut" "bonjour" "bonjour"
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN "abc" "def"
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN "bosdsdfnjodur" "atehhellosd" "afkuonjosurafg" "headfgllosf" "fghellosag" "afdfbosnjourafg"
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

bash .system/auto_correc_program.sh $FILE $ASSIGN
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

touch .system/grading/passed;
