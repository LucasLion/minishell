/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:03:31 by event             #+#    #+#             */
/*   Updated: 2023/04/03 17:25:00 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_chevrons(char **tab, int index, t_command *new)
{
	if (tab[index][0] == '<')
	{
		if (tab[index][1] == '<')
			fill_list_string_append_or_heredoc(tab[index + 1], &(new->input));
		else
			fill_list_string(tab[index + 1], &(new->input));
		new->redir_input = 1;
	}
	else
	{
		if (tab[index][1] == '>')
			fill_list_string_append_or_heredoc(tab[index + 1], &(new->output));
		else
			fill_list_string(tab[index + 1], &(new->output));
		new->redir_output = 1;
	}
}

int	find_command_until_pipe(char **tab, int *i, t_command *new,
		t_core *minishell)
{
	int	ret;

	ret = 0;
	if (tab[*i][0] == '<' || tab[*i][0] == '>')
	{
		if (tab[*i + 1] == NULL)
		{
			errno = -3;
			minishell->last_status = 258;
			return (1);
		}
		handle_chevrons(tab, *i, new);
		(*i)++;
	}
	else
		fill_list_string(tab[*i], &(new->command));
	return (ret);
}

int	fill_list_command(char **tab, int *i, t_core *minishell, int *count)
{
	t_command	*new;

	new = malloc(sizeof(t_command));
	if (new == NULL)
		return (0);
	init_struct_command(new);
	while (tab[*i] && (tab[*i][0] != '|' || tab[*i][1] != '\0'))
	{
		if (find_command_until_pipe(tab, i, new, minishell))
			return (0);
		(*i)++;
	}
	if (tab[*i] && (tab[*i][0] == '|' && tab[*i][1] == '\0'))
	{
		new->pipe_after = 1;
		(*i)++;
	}
	new->order = *count;
	new->next = NULL;
	if (!lstadd_back_list_command(&(minishell->list_of_command), new))
		return (0);
	return (1);
}

int	no_last_command(t_command *list)
{
	t_command	*temp;

	temp = list;
	while (temp->next != NULL)
		temp = temp->next;
	if (temp->command == NULL)
	{
		printf("ERROR : Pas de commande apres le dernier pipe\n");
		g_global.status = 1;
		return (1);
	}
	else
		return (0);
}

int	parse_input(t_core *minishell)
{
	char	**tab;
	int		i;
	int		count;

	i = 0;
	tab = ft_split_ms(format_line(minishell));
	if (tab == NULL)
		return (0);
	count = 0;
	while (tab[i])
	{
		count++;
		if (!fill_list_command(tab, &i, minishell, &count))
		{
			clean_list_command(&(minishell->list_of_command));
			ms_error(NULL, NULL, errno);
			return (0);
		}
	}
	free_tab2(tab);
	if (no_last_command(minishell->list_of_command))
		return (0);
	return (1);
}
