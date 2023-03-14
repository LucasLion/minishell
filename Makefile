# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llion <llion@student.42mulhouse.fr >       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/09 15:27:43 by llion             #+#    #+#              #
#    Updated: 2023/03/14 12:40:24 by llion            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell 
CC = gcc
FLAGS = -Wall -Werror -Wextra -ggdb3 
READLINE = -lreadline
LIBFT = ./libft/libft.a
HEADERS = -I include -I libft 

SOURCES = 	main_antoine.c \
			main-lucas.c	\
			memory_utils.c	\
			unset.c			\
			find_arg.c \
			verif_line.c \
			split_ms.c \
			echo.c			\
			pwd.c			\
			export.c		\
			list_char.c \
			format_line.c \
			format_list.c \
			parse.c \
			parse_v1.c \
			list_int.c \
			list_string.c \
			list_command.c 

OBJS = ${addprefix src/,${SOURCES:.c=.o}}
OBJBONUS = ${addprefix src/,${SRCBONUS:.c=.o}}

all :  ${NAME}

.c.o: 
	gcc ${FLAGS} ${HEADERS} -c $< -o ${<:.c=.o}

${NAME} : ${OBJS} 
	make -C libft
	gcc  ${FLAGS} ${OBJS} ${LIBFT} ${HEADERS} -o ${NAME} ${READLINE}

bonus : ${OBJBONUS} 
	make -C libft
	gcc ${FLAGS} ${OBJBONUS} ${LIBFT} ${HEADERS} -o ${NAME} ${READLINE}

debug : ${OBJS} ${OBJBONUS} 
	make -C libft
	gcc ${FLAGS} ${OBJS} ${LIBFT} ${HEADERS} -fsanitize=address -o ${NAME}  ${READLINE}

clean :
	rm -f ${OBJS} ${OBJBONUS} 
	make clean -C libft

fclean : clean
	rm -f ${NAME} 
	make fclean -C libft

re : fclean all
