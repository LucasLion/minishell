/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:25:17 by llion             #+#    #+#             */
/*   Updated: 2023/03/31 16:59:50 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
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


typedef struct s_list_to_tab
{
 	char   *ret;
    int 	i;
    int 	j;
	int		flag;
	int		flag1;
	int 	count;
	
}					t_list_to_tab;


typedef struct s_pipe
{
	int			nbr_of_pipes;
	int			nbr_of_commands;
	int			i;
	char		*cmd;
	char		**tab_arg;
	int			fd_input;
	int			fd_output;
	
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
	int					append_or_heredoc;
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
	int					order;
	int					pipe_after;
	int					status;
	int					last_status;
    struct s_command	*next;
	struct s_command	*previous;
	
}					t_command;

typedef struct s_core
{
	t_command 		*list_of_command;
	int				last_status;
	char			*input;
	char			**envp;
	char			*redir;
	
	
}					t_core;

/* -------------- CD.c -------------- */

char 	*get_env_variable(char **envp, char *variable);
char	*create_absolute_path(char *input, char **envp);
int		cd(char *input, char **envp);

/* -------------- CLEAN_LIST.c -------------- */

void	clean_list_char(t_char **list);
void	clean_list_string(t_string **list);
void	clean_list_command(t_command **list);

/* -------------- ECHO.c -------------- */

int		print_tab_echo(char **tab, int i);
int		echo(char **argv);

/* -------------- EXEC_COMMAND.c -------------- */

char	**get_path_split(char **envp);
char	*get_path(char **envp, char *cmd);
char 	*is_builtin(char *cmd);
int		exec_builtin(char *builtin, char **argv, t_core *minishell);
void	exec_command(char *command, char **argv, char ***envp);

/* -------------- EXECUTE.c -------------- */

void 	init_pipe_info(t_pipe *pipe_info, t_command *list);
void 	execute_one_command(t_core *minishell, t_pipe *pipe_info);
int 	execute(t_core *minishell);

/* -------------- EXIT.c -------------- */

int		exit_shell(int status, char **argv, t_core *minishell);
void    wait_proof(t_core *minishell, int pid);
void	write_error(char *cmd, char *input, int error_no);
int		ms_error(char *cmd, char *input, int error);

/* -------------- EXPORT.c -------------- */

int  	parse_arg(char *arg, int *status);
int  	parse_arg2(char *arg, int *status);
char 	**sort_tab(char **tab, int size);
char  	*add_double_quotes(char *str);
void  	display_export(char **envp);

/* -------------- EXPORT2.c -------------- */

int   	check_if_variable(char *arg, char **envp);
char  	**add_new_variable(char *arg, char **envp);
char  	**edit_variable(char *arg, char **envp);
int		modifiy_env(char *arg, char ***envp);
int   	ms_export(char **argv, char ***envp, int *status);

/* -------------- EXPORT3.c -------------- */

void	cat(char *nenvp, char *arg);
char	**allocate_tab(int size);
char	*allocate(int size, char **nenvp);
char	*val(char *arg);
char 	*var(char *arg);

/* -------------- FORMAT_LINE.c -------------- */

int     length_list(t_char *list);
char    *list_to_string(t_char *list);
char    *format_line(char *line);
void    print_input_after_formating(char *line_input);
int		only_space_left(t_char *node);

/* -------------- FORMAT_LIST.c -------------- */
int     add_space_before (t_char *node);
int     format_pipe(t_char *node);
int     format_chevron_inf(t_char *node);
int     format_chevron_sup(t_char *node);
int     format_list(t_char *list);

/* -------------- INIT_STRUCT.c -------------- */

void 	init_struct_ltt(t_list_to_tab *cs);
void 	add_one(int *a, int *b);
void 	init_core(t_core *minishell);
void	loop(int *i, int env_size, char **nenvp, char **envp);

 /* -------------- LIST_CHAR.c -------------- */

int	    lstadd_back_ms(t_char **list, t_char *new);
int     fill_list(char *line, t_char **list);
int     insert_space_node(t_char *previous, t_char *next);
int     insert_two_space(t_char *node);

/* -------------- LIST_COMMAND.c -------------- */

void    init_struct_command(t_command *list_of_command);
int		lstadd_back_list_command(t_command **list, t_command *new);
int 	length_list_command(t_command *list, int *nb_of_pipes);

/* -------------- LIST_STRING.c -------------- */

int		lstadd_back_list_string(t_string **list, t_string *new);
int 	fill_list_string(char *str, t_string **list);
int 	fill_list_string_append_or_heredoc(char *str, t_string **list);
void 	print_list_string_from_head(t_string *list);
void 	print_list_string_from_head_command(t_string *list);

/* -------------- LIST_TO_TAB.c -------------- */

int 	length_list_string(t_string *list);
int 	size_var(char *string_list, int *i);
int 	count_size_env(char *string_list, int *i, char **envp, int status);
void 	last_error(char *ret, int *j, int status);

/* -------------- LIST_TO_TAB2.c -------------- */

void 	copy_env_var_2(char *env, t_list_to_tab *cs);
void	copy_env_var(char *string_list, char **envp, int status, t_list_to_tab *cs);
int 	count_char(char *string_list, char **envp, int status);
char 	*copy_string(char *string_list, char **envp, int status);
char 	**list_to_tab(t_command *list, char **envp, int status );

/* -------------- MEMORY_UTILS.c -------------- */

void	free_tab2(char **tab);
void	free_tab3(char ***tab);
void 	free_export(char *val_arg, char *var_arg, char	*var_env, char **envp);

/* -------------- PARSE.c -------------- */

void 	handle_chevrons(char **tab, int index, t_command *new);
int 	find_command_until_pipe(char **tab, int *i, t_command *new, t_core *minishell);
int 	fill_list_command(char **tab, int *i, t_core *minishell, int *count);
int 	parse_input(t_core *minishell);

/* -------------- PIPE_UTILS.c -------------- */

int 	**create_pipes(int nb_of_pipes, int **fd);
void 	close_fd_everyhing(int **fd, int nbr_of_pipes);
void 	close_fd_everyhing_but_one(int **fd, int nbr_of_pipes, int a, int b);
void 	close_fd_everyhing_but_two(int **fd, int nbr_of_pipes, int read, int write);
void 	wait_all_pid(int *pid, int nbr_of_command, t_core *minishell);

/* -------------- PIPE.c -------------- */

void    child_first_pipe(t_pipe *pipe_info, int **fd, char **envp);
void    child_last_pipe(t_pipe *pipe_info, int **fd, char **envp);
void    child_middle_pipe(t_pipe *pipe_info, int **fd, char **envp);
int 	child_process(t_pipe *pipe_info, int **fd, char **envp);
int 	managing_pipe(t_core *minishell, t_pipe *pipe_info, int **fd);

/* -------------- PWD_ENV.c -------------- */

int		pwd();
int 	env(char **envp);

/* -------------- REDIR.c -------------- */


int 	handle_del(char *str);
int 	ambiguous_redirect(char *str, t_core *minishell);
int 	find_input(t_string *input, t_core *minishell);
int 	find_output(t_string *output, t_core *minishell);

/* -------------- REDIR2.c -------------- */

int 	init_fd(t_core *minishell, t_pipe *pipe_info, t_command *list);
void 	redir_execve(t_core *minishell, t_pipe *pipe_info);
void 	redir_builtin(t_core *minishell, t_pipe *pipe_info);

/* -------------- SIGNALS.c -------------- */

void	sigint();
void	signals();

/* -------------- SPLIT_MS -------------- */

int     put_flag(char c, int flag);
int	    count_word_ms(char const *str);
int	    len_word(char const *str, int *pos);
void	put_word(char const *str, int *pos, char *line_tab);

/* -------------- SPLIT_MS_2 -------------- */

int	    free_tab_ms_split(char **tab, int i);
int	    fill_tab_split_ms(char **tab, char const *s);
char    **ft_split_ms(char const *s);
void    split_and_print(char *line);

/* -------------- TAB_UTILS.c -------------- */

void 	print_tab(char **tab);
char    **copy_tab(char **tab);
int		count_var_size(char *var);

/* -------------- UNSET.c -------------- */

int 	check_args(char *line, char **envp);
int		compare_args(char *str, char **args);
int		compare_args2(char *str, char **args);
char	**new_argv(char **argv, char **envp);
int		unset(char **argv, char ***envp);

/* -------------- VERIF_LINE -------------- */

int		quotes_verif(char *str);
int     verif_line(char *line);

#endif

