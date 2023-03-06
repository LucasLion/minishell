NAME = minishell 
CC = gcc
FLAGS = -Wall -Werror -Wextra -g3 
READLINE = -lreadline
LIBFT = ./libft/libft.a
HEADERS = -I headers -I libft 


<<<<<<< HEAD
SOURCES = 	main.c \
			find_arg.c \
			verif_line.c \
			split_ms.c \
			echo.c			\
			pwd.c			\
			export.c		

			
SRCBONUS = 
		

		

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
	gcc ${FLAGS} ${OBJS} ${LIBFT} ${LIB_MLX} ${HEADERS} -fsanitize=address -o ${NAME} 

clean :
	rm -f ${OBJS} ${OBJBONUS} 
	make clean -C libft

fclean : clean
	rm -f ${NAME} 
	make fclean -C libft

re : fclean all
