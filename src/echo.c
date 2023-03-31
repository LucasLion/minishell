/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 14:59:28 by llion             #+#    #+#             */
/*   Updated: 2023/03/31 13:39:56 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	new_strlen(char *str)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	j = ft_strlen(str);
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1] == '\\')
			i++;
		else if (str[i] == '\\')
		{
			count++;
			i++;
		}
		i++;
	}
	return (j - count);
}

char	*parse(char *str)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	ret = ft_calloc(new_strlen(str) + 1, sizeof(char));
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\\')
			i++;
		ret[j] = str[i];
		j++;
		i++;
	}
	return (ret);
}

int	print_tab_echo(char **tab, int i)
{
	int		counter;
	char	*parsed_word;

	counter = 0;
	while (tab[counter])
		counter++;
	while (i < counter - 1)
	{
		if (tab[i] == NULL)
			return (ms_error("echo", NULL, -1));
		parsed_word = parse(tab[i]);
		printf("%s ", parsed_word);
		free(parsed_word);
		i++;
	}
	parsed_word = parse(tab[i]);
	printf("%s", parsed_word);
	free(parsed_word);
	return (0);
}

int	is_valid_arg(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] != '-')
		return (0);
	while (arg[++i])
	{
		if (arg[i] != 'n')
			return (0);
	}
	return (1);
}

int	echo(char **argv)
{
	int	i;
	int	backline;

	i = 1;
	backline = 1;
	if (argv == NULL)
		return (ms_error("echo", NULL, -1));
	while (argv[i])
	{
		if (is_valid_arg(argv[i]))
		{
			backline = 0;
			i++;
		}
		else
			break ;
	}
	print_tab_echo(argv, i);
	if (backline)
		printf("\n");
	return (0);
}
