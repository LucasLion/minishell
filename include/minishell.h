/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:25:17 by llion             #+#    #+#             */
/*   Updated: 2023/03/06 17:36:11 by amouly           ###   ########.fr       */
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

/* -------------- ADD_SPACE.c -------------- */

int	    lstadd_back_ms(t_char **list, t_char *new);
int     fill_list(char *line, t_char **list);
void    print_list_from_head(t_char *list);
void    print_list_from_bottom(t_char *list);
int     create_insert_node(t_char *previous, t_char *next);
int     insert_space(t_char *node);
void    insert_space_everywhere(t_char **list);

/* -------------- FORMAT_LINE.c -------------- */

void        format_list(t_char *list);
int         length_list(t_char *list);
char        *list_to_string(t_char *list);
void        format_line(char *line_input);

#endif

