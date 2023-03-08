/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:25:17 by llion             #+#    #+#             */
/*   Updated: 2023/03/08 18:41:11 by llion            ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_char
{
	char			character;
    int             flag_simple_quote;
    int             flag_double_quote;
	struct s_char	*next;
    struct s_char	*previous;
}					t_char;

typedef struct s_env
{
   char           *name;
   char           *value;
   struct s_env   *next;
}              t_env;


/* -------------- FREE -------------- */

void  free_tab2(char **tab);
void  free_tab3(char ***tab);

/* -------------- BUILTINS -------------- */

/* -------------- VERIF_LINE -------------- */

int verif_line(char *line);

/* -------------- SPLIT_MS.c -------------- */

int     put_flag(char c, int flag);
int	    count_word_ms(char const *str);
int	    len_word(char const *str, int *pos);
int	    free_tab_ms_split(char **tab, int i);
int	    fill_tab_split_ms(char **tab, char const *s);
char    **ft_split_ms(char const *s);
void    split_and_print(char *line);

/* -------------- ADD_SPACE.c -------------- */

void	echo(char **args);
void	pwd();

/* -------------- EXPORT -------------- */

int     ms_export(char ***args, char ***env, char **envp);
t_env   *create_var_list(char **envp);
char  	***create_args_list(char *args);
char  	***create_env_list(char **envp);

/* -------------- PARSING -------------- */

void	free_tab_ms(char **tab);
void	print_args(char **tab, int i);
int		quotes_nbr(char *str);
int		command_len(char *str);
char	**find_args(char *str);

int add_space(char *line, t_char **list);

#endif

