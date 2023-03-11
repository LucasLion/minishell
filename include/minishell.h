/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:25:17 by llion             #+#    #+#             */
/*   Updated: 2023/03/11 13:44:59 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct s_number
{
	int			        nbr;
	struct s_number	    *next;
    struct s_number	    *previous;
}					t_number;

typedef struct s_char
{
	char			character;
	struct s_char	*next;
    struct s_char	*previous;
}					t_char;

typedef struct s_string
{
	char				*string;
	int					append;
	struct s_string		*next;
    struct s_string		*previous;
}					t_string;

typedef struct s_command
{
	t_string			*command;
	t_string			*input;
	int					redir_input;
	t_string			*output;
	int					redir_output;
	t_string			*delimiters;
	int					delimiter;
	int					order;
	int					pipe_after;
    struct s_command	*next;
	struct s_command	*previous;
}					t_command;


/* -------------- BUILTINS -------------- */

void	echo(char **args);
void	pwd();
int		ms_export(char **args, char **envp);

/* -------------- VERIF_LINE -------------- */

int		quotes_verif(char *str);
int     verif_line(char *line);

/* -------------- SPLIT_MS -------------- */

int     put_flag(char c, int flag);
int	    count_word_ms(char const *str);
int	    len_word(char const *str, int *pos);
void	put_word(char const *str, int *pos, char *line_tab);
int	    free_tab_ms_split(char **tab, int i);
int	    fill_tab_split_ms(char **tab, char const *s);
char    **ft_split_ms(char const *s);
void    split_and_print(char *line);


/* -------------- PARSING -------------- */

void	free_tab_ms(char **tab);
void	print_args(char **tab, int i);
int		quotes_nbr(char *str);
int		command_len(char *str);
char	**find_args(char *str);

/* -------------- LIST_CHAR.c -------------- */

int	    lstadd_back_ms(t_char **list, t_char *new);
int     fill_list(char *line, t_char **list);
void    print_list_from_head(t_char *list);
void    print_list_from_bottom(t_char *list);
int     insert_space_node(t_char *previous, t_char *next);
int     insert_two_space(t_char *node);
void    insert_space_everywhere(t_char **list);

/* -------------- LIST_INT.c -------------- */

int	    lstadd_back_list_int(t_number **list, t_number *new);
int     fill_list_int(int nbr, t_number **list);
void    print_list_int_from_head(t_number *list);
void    print_list_int_from_bottom(t_number *list);

/* -------------- LIST_STRING.c -------------- */

int		lstadd_back_list_string(t_string **list, t_string *new);
int 	fill_list_string(char *str, t_string **list);
int 	fill_list_string_append(char *str, t_string **list);
void 	print_list_string_from_head(t_string *list);
void 	print_list_string_from_head_command(t_string *list);

/* -------------- LIST_COMMAND.c -------------- */

void    init_struct_command(t_command *list_of_command);
int		lstadd_back_list_command(t_command **list, t_command *new);
void 	print_list_command_from_head(t_command *list);

/* -------------- FORMAT_LIST.c -------------- */

int     add_space_before (t_char *node);
int     format_pipe(t_char *node);
int     format_chevron_inf(t_char *node);
int     format_chevron_sup(t_char *node);
int     format_list(t_char *list);

/* -------------- FORMAT_LINE.c -------------- */

int     length_list(t_char *list);
char    *list_to_string(t_char *list);
char    *format_line(char *line);
void    print_input_after_formating(char *line_input);

/* -------------- PARSE.c -------------- */

void 	handle_chevrons(char **tab, int index, t_command *new);
void 	find_command_until_pipe(char **tab, int *i,t_command *new);
int 	fill_list_command(char **tab, int *i, t_command **list, int *count);
void    parse_input(char *input);

/* -------------- PARSE_V1.c -------------- */

int 	count_nb_of_pipes(char **tab);
void 	handle_chevrons_v1(char **tab, int index);
void 	find_command_until_pipe_v1(char **tab, int *i, int *cmd, int *arg);
void    parse_input_v1(char *input);

#endif

