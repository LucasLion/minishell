/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:25:17 by llion             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/03/06 11:26:16 by amouly           ###   ########.fr       */
=======
/*   Updated: 2023/03/04 15:24:01 by llion            ###   ########.fr       */
>>>>>>> master
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
int		ms_export(char **args, char **envp);

/* -------------- PARSING -------------- */

void	free_tab_ms(char **tab);
void	print_args(char **tab, int i);
int		quotes_nbr(char *str);
int		command_len(char *str);
char	**find_args(char *str);

int add_space(char *line, t_char **list);

#endif

