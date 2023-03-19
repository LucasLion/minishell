/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:25:17 by llion             #+#    #+#             */
/*   Updated: 2023/03/19 16:23:12 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_number
{
	int			        nbr;
	struct s_number	    *next;
    struct s_number	    *previous;
}					t_number;

typedef struct s_pipe
{
	int			nbr_of_pipes;
	int			reading_index;
    int			writing_index;
	char		*cmd_1;
	char		**tab_argv_1;
	char		*cmd_2;
	char		**tab_argv_2;
	char		**envp;
	int			fd_writing;
	int			fd_reading;
	
}					t_pipe;

typedef struct s_char
{
	char			character;
	struct s_char	*next;
    struct s_char	*previous;
}					t_char;

typedef struct s_env
{
   char           *name;
   char           *value;
   struct s_env   *next;
}              t_env;


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

/* -------------- EXEC -------------- */

char	**get_path_split(char **envp);
char    *get_path(char **envp, char *cmd);
int		exec_command(char *command, char **argv, char **envp);

/* -------------- FREE -------------- */

void	free_tab2(char **tab);
void	free_tab3(char ***tab);

/* -------------- BUILTINS -------------- */

void	echo(char **args);
int		ms_exit(char **argv, char **envp);
void	pwd();
char     **unset(char **envp, char *line);

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

/* -------------- EXPORT -------------- */

char     **ms_export(char **envp, int env_len);
t_env    *create_var_list(char **envp);
char     ***create_args_list(char *args);
char     ***create_env_list(char **envp, int env_len);
int      tab_len(char **envp);
char     **sort_envp(char **envp);

/* -------------- LIST_CHAR.c -------------- */

int	    lstadd_back_ms(t_char **list, t_char *new);
int     fill_list(char *line, t_char **list);
void    print_list_from_head(t_char *list);
void    print_list_from_bottom(t_char *list);
int     insert_space_node(t_char *previous, t_char *next);
int     insert_two_space(t_char *node);
void    insert_space_everywhere(t_char **list);

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
int 	length_list_command(t_command *list, int *nb_of_pipes);

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
void    parse_input(char *input, t_command **list);

/* -------------- CLEAN_LIST.c -------------- */

void	clean_list_char(t_char **list);
void	clean_list_string(t_string **list);
void	clean_list_command(t_command **list);

/* -------------- LIST_TO_TAB.c -------------- */

int 	length_list_string(t_string *list);
int 	size_var(char *string_list, int *i);
int 	count_size_env(char *string_list, int *i, char **envp);
void 	copy_env_var(char *string_list, int *i, char **envp, char *ret, int *j);
int 	count_char(char *string_list, char **envp);
char 	*copy_string(char *string_list, char **envp);
char 	**list_to_tab(t_string *list, char **envp);

/* -------------- TAB_UTILS.c -------------- */

void 	print_tab(char **tab);
int 	len_tab(char **tab);
char    **copy_tab(char **tab);

/* -------------- PIPE.c -------------- */

int 	managing_pipes(t_command *list, char **envp);



#endif

