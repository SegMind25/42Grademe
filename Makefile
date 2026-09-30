# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/21 01:05:24 by jcluzet           #+#    #+#              #
#    Updated: 2023/01/13 02:33:46 by nnuno-ca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all re grade gradejustinstall clean fclean help

all:
	@bash .system/launch.sh all

re: clean
	@bash .system/launch.sh

gradejustinstall:
	@bash .system/launch.sh gradejustinstall

grade: clean
	@bash .system/launch.sh grade

clean:
	@rm -rf .system/a.out .system/a.out.dSYM

fclean: clean
	@rm -rf .system/exam_token .system/grading rendu subjects traces

help:
	@printf "\033[37mType \033[32mmake\033[37m to start the exam\n"
	@printf "\033[37m     \033[32mmake fclean\033[37m to erase the current exam, settings and rendu\033[0m\n"
