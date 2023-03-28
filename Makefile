# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amouly <amouly@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/09 15:27:43 by llion             #+#    #+#              #
#    Updated: 2023/03/28 13:54:08 by llion            ###   ########.fr        #
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
	@gcc  ${FLAGS} ${OBJS} ${LIBFT} ${READLINE} ${HEADERS} -o ${NAME}	
	@echo "-----> minishell        \033[32mCOMPILED\033[0m"
	

debug : ${OBJS} ${OBJBONUS} 
	@make -sC libft
	@gcc ${FLAGS} ${OBJS} ${LIBFT} ${HEADERS} -fsanitize=address -o ${NAME}  ${READLINE}
	@echo "-----> minishell \033[31m(DEBUG)\033[32mCOMPILED\033[0m"

clean :
	@rm -f ${OBJS} objs/%.o ${OBJBONUS} 
	@echo "-----> objects          \033[32mREMOVED\033[0m"
	@make clean -sC libft

fclean : clean
	@rm -rf ${NAME} *.dSYM
	@make fclean -sC libft
	@echo "-----> minishell        \033[32mREMOVED\033[0m"

re : fclean all
