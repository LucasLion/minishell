# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amouly <amouly@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/09 15:27:43 by llion             #+#    #+#              #
#    Updated: 2023/03/20 11:01:08 by llion            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell 
CC = gcc
FLAGS = -Wall -Werror -Wextra -ggdb3
READLINE = -lreadline
LIBFT = ./libft/libft.a
HEADERS = -I include -I libft 

SOURCES = 	main_lucas.c \
			memory_utils.c	\
			unset.c			\
			verif_line.c \
			split_ms.c \
			echo.c			\
			pwd.c			\
			export.c		\
			list_char.c \
			format_line.c \
			format_list.c \
			parse.c \
			list_string.c \
			list_command.c \
			clean_list.c \
			exec_command.c\
			list_to_tab.c

OBJS = ${addprefix objs/,${notdir ${SOURCES:.c=.o}}}

all :  ${NAME}

#objs/%.o: src/%.c
#	@gcc ${FLAGS} ${HEADERS} -c $< -o $@

${OBJS} : objs/%.o : src/%.c
	@mkdir -p objs
	@${CC} ${FLAGS} ${HEADERS} -c $< -o $@


${NAME} : ${OBJS} 
	@make -sC libft
	@echo "----> libft COMPILED"
	@gcc  ${FLAGS} ${OBJS} ${LIBFT} ${HEADERS} -o ${NAME} ${READLINE}
	@echo "----> minishell COMPILED"
	

debug : ${OBJS} ${OBJBONUS} 
	make -C libft
	gcc ${FLAGS} ${OBJS} ${LIBFT} ${HEADERS} -fsanitize=address -o ${NAME}  ${READLINE}

clean :
	@rm -f ${OBJS} ${OBJBONUS} 
	@echo "----> objects REMOVED"
	@make clean -sC libft
	@echo "----> libft REMOVED"

fclean : clean
	@rm -rf ${NAME} *.dSYM
	@make fclean -sC libft
	@echo "----> Everything is GONE"

re : fclean all
