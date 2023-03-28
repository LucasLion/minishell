# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amouly <amouly@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/09 15:27:43 by llion             #+#    #+#              #
#    Updated: 2023/03/28 17:06:39 by amouly           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell 
CC = gcc
FLAGS = -Wall -Werror -Wextra -ggdb3
READLINE = -lreadline -L ~/.brew/opt/readline/lib
LIBFT = ./libft/libft.a
HEADERS = -I include -I libft -I ~/.brew/opt/readline/include

SOURCES = 	cd.c			\
			clean_list.c	\
			echo.c			\
			exec_command.c	\
			execute.c		\
			exit.c			\
			export.c		\
			export2.c		\
			format_line.c	\
			format_list.c	\
			list_char.c		\
			list_command.c	\
			list_string.c	\
			list_to_tab.c	\
			list_to_tab2.c	\
			main.c			\
			memory_utils.c	\
			parse.c			\
			pipe_utils.c	\
			pipe.c			\
			pwd_env.c		\
			redir.c			\
			redir2.c		\
			signals.c		\
			split_ms.c 		\
			split_ms2.c		\
			tab_utils.c		\
			unset.c			\
			verif_line.c	\
			
			

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
