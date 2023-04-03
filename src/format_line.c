/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:50:37 by amouly            #+#    #+#             */
/*   Updated: 2023/04/03 18:54:42 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	length_list(t_char *list)
{
	int	i;

	i = 0;
	if (list)
	{
		i++;
		while (list->next != NULL)
		{
			list = list->next;
			i++;
		}
		return (i);
	}
	else
		return (0);
}

char	*list_to_string(t_char *list)
{
	int		len;
	char	*ret;
	int		i;
	t_char	*temp;

	temp = list;
	len = length_list(list);
	i = 0;
	ret = malloc(sizeof(char) * (len + 1));
	if (ret == NULL)
		return (NULL);
	while (i < len)
	{
		ret[i] = temp->character;
		i++;
		temp = temp->next;
	}
	ret[i] = '\0';
	return (ret);
}

char	*format_line(t_core *minishell)
{
	t_char	*list;
	char	*line_formated;
//	char 	*line;
	
	
	//line = minishell->input;
	if (verif_line(minishell))
		return (NULL);
//	line = minishell->input;
	printf("la string (ms) dans format line -- %s\n", minishell->input);
	//printf("longueur de ms->input = %zu\n", ft_strlen(minishell->input));
//	printf("la string (input) dans format-- %s\n", line);
	list = NULL;
	if (!fill_list(minishell->input, &list))
	{
		clean_list_char(&list);
		return (NULL);
	}
	if (!format_list(list))
	{
		clean_list_char(&list);
		return (NULL);
	}
	line_formated = list_to_string(list);
	clean_list_char(&list);
	return (line_formated);
}

void	print_input_after_formating(t_core *minishell)
{
	char	*line_formated;
	//char	*line_input;

	//line_input = minishell->input;
	line_formated = format_line(minishell);
	printf("%s\n", line_formated);
	split_and_print(line_formated);
}

int	only_space_left(t_char *node)
{
	t_char	*temp;

	temp = node;
	if (temp == NULL)
		return (1);
	while (temp)
	{
		if (temp->character != ' ' && temp->character != '\t')
			return (0);
		temp = temp->next;
	}
	return (1);
}
