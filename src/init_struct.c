/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 10:45:20 by amouly            #+#    #+#             */
/*   Updated: 2023/03/31 12:15:46 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void init_struct_ltt(t_list_to_tab *cs)
{
	cs->i = 0;
	cs->j = 0;
	cs->flag = 0;
	cs->count = 0;
	cs->ret = NULL;
}

void add_one(int *a, int *b)
{
	if (a != NULL)
		(*a)++;
	if (b != NULL)
		(*b)++;
}

void init_core(t_core *minishell)
{
	minishell->list_of_command = NULL;
	minishell->redir = NULL;
	minishell->input = readline("Minishell> ");
	add_history(minishell->input);
}