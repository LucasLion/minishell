# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amouly <amouly@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/09 15:27:43 by llion             #+#    #+#              #
#    Updated: 2023/03/27 15:45:18 by llion            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell 
CC = gcc
FLAGS = -Wall -Werror -Wextra -ggdb3
READLINE = -lreadline -L ~/.brew/opt/readline/lib
LIBFT = ./libft/libft.a
HEADERS = -I include -I libft -I ~/.brew/opt/readline/include

SOURCES = 	memory_utils.c	\
			unset.c			\
			main.c			\
			verif_line.c	\
			signals.c		\
			split_ms.c 		\
			echo.c			\
			pwd.c			\
			cd.c			\
			export.c		\
			list_char.c		\
			format_line.c	\
			format_list.c	\
			parse.c			\
			pipe.c			\
			list_string.c	\
			list_command.c	\
			clean_list.c	\
			exec_command.c	\
			list_to_tab.c	\
			tab_utils.c		\
			redir.c			\
			pipe_utils.c

OBJS = ${addprefix objs/,${notdir ${SOURCES:.c=.o}}}

all :  ${NAME}

objs/%.o : src/%.c
	@mkdir -p objs
	@${CC} ${FLAGS} ${HEADERS} -c $< -o $@


${NAME} : ${OBJS} 
	@make -sC libft
	@echo "----> libft COMPILED"
	@gcc  ${FLAGS} ${OBJS} ${LIBFT} ${READLINE} ${HEADERS} -o ${NAME}	
	@echo "----> minishell COMPILED"
	

debug : ${OBJS} ${OBJBONUS} 
	make -C libft
	gcc ${FLAGS} ${OBJS} ${LIBFT} ${HEADERS} -fsanitize=address -o ${NAME}  ${READLINE}

clean :
	@rm -f ${OBJS} objs/%.o ${OBJBONUS} 
	@echo "----> objects REMOVED"
	@make clean -sC libft
	@echo "----> libft REMOVED"

fclean : clean
	@rm -rf ${NAME} *.dSYM
	@make fclean -sC libft
	@echo "----> Everything is GONE"

re : fclean all
