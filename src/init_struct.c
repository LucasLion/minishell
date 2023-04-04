/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 10:45:20 by amouly            #+#    #+#             */
/*   Updated: 2023/04/04 13:09:48 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_struct_ltt(t_list_to_tab *cs)
{
	cs->i = 0;
	cs->j = 0;
	cs->flag = 0;
	cs->count = 0;
	cs->ret = NULL;
}

void	add_one(int *a, int *b)
{
	if (a != NULL)
		(*a)++;
	if (b != NULL)
		(*b)++;
}

void	init_core(t_core *minishell)
{
	minishell->list_of_command = NULL;
	minishell->redir = NULL;
	minishell->input = readline("Minishell> ");
	add_history(minishell->input);
	if (minishell->input
		&& ft_strncmp(minishell->input, "./minishell", 11) != 0)
		g_global.catch = 0;
}

void	loop(int *i, int env_size, char **nenvp, char **envp)
{
	while (*i < env_size)
	{
		nenvp[*i] = ft_strdup((envp)[*i]);
		(*i)++;
	}
}

void	init_golbal(t_core	*minishell)
{
	minishell->last_status = g_global.status;
	g_global.status = 0;
}
