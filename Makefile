# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amouly <amouly@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/09 15:27:43 by llion             #+#    #+#              #
#    Updated: 2023/03/30 12:06:17 by llion            ###   ########.fr        #
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
			
			

UNAME := $(shell uname)
OBJS = ${addprefix objs/,${notdir ${SOURCES:.c=.o}}}

all :  ${NAME}

objs/%.o : src/%.c
	@mkdir -p objs
	@${CC} ${FLAGS} ${HEADERS} -c $< -o $@


$(NAME) : $(OBJS) 
	@make -sC libft
	@gcc  $(FLAGS) $(OBJS) $(LIBFT) $(READLINE) $(HEADERS) -o $(NAME)	
ifeq ($(UNAME),Linux)
	@echo -e "-----> minishell        \033[32mCOMPILED\033[0m"
endif
ifeq ($(UNAME),Darwin)
	@echo "-----> minishell        \033[32mCOMPILED\033[0m"
endif
	

debug : $(OBJS) $(OBJBONUS) 
	@make -sC libft
	@gcc ${FLAGS} ${OBJS} ${LIBFT} ${HEADERS} -fsanitize=address -o ${NAME}  ${READLINE}
ifeq ($(UNAME),Linux)
	@echo -e  "-----> minishell \033[31m(DEBUG)\033[32mCOMPILED\033[0m"
endif
ifeq ($(UNAME),Darwin)
	@echo "-----> minishell \033[31m(DEBUG)\033[32mCOMPILED\033[0m"
endif

clean :
	@make clean -sC libft
	@rm -f ${OBJS} objs/%.o ${OBJBONUS} 
ifeq ($(UNAME),Linux)
	@echo -e "-----> objects          \033[32mREMOVED\033[0m"
endif
ifeq ($(UNAME),Darwin)
	@echo "-----> objects          \033[32mREMOVED\033[0m"
endif

fclean : clean
	@rm -rf ${NAME} *.dSYM
	@make fclean -sC libft
ifeq ($(UNAME),Linux)
	@echo -e "-----> minishell        \033[32mREMOVED\033[0m"
endif
ifeq ($(UNAME),Darwin)
	@echo "-----> minishell        \033[32mREMOVED\033[0m"
endif

re : fclean all

foo:



