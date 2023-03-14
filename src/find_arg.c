/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:25:17 by llion             #+#    #+#             */
/*   Updated: 2023/03/11 13:37:26 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab_ms(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}


int		quotes_nbr(char *str)
{
	int	i;
	int	flag1;
	int	flag2;

	i = 0;
	flag1 = 0;
	flag2 = 0;
	while (str[i])
	{
		if (str[i] == '"' && flag1 == 0 && flag2 == 0)
			flag1 = 1;
		else if (str[i] == '\'' && flag1 == 0 && flag2 == 0)
			flag2 = 1;
		else if (str[i] == '"' && flag1 == 1 && flag2 == 0)
			flag1 = 0;
		else if (str[i] == '\'' && flag1 == 0 && flag2 == 1)
			flag2 = 0;
		i++;
	}
	if (flag1 == 1 || flag2 == 1)
		return (1);
	else
		return (0);
}


int	command_len(char *str)
{
	int	i;
	int	cmd_len;

	i = 0;
	cmd_len = 0;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && str[i] != ' ' && str[i] != '"' && str[i] != '\'')
	{
		i++;
		cmd_len++;
	}
	return (cmd_len);
}

char	*find_command(char *str)
{
	int			i;
	char		*cmd;

	if (!quotes_nbr(str))
	{
		printf("Erreur de quotes");
		return (NULL);
	}
	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	cmd = malloc(sizeof(char) * (command_len(str) + 1));
	if (cmd == NULL)
		return (NULL);
	ft_strlcpy(cmd, &str[i], command_len(str) + 1);
	printf("cmd_len: %d\n", command_len(str));
	return (cmd);
}

char	**find_args(char *str)
{
	int		i;
	char	**tab;
	
	i = 0;
	tab = NULL;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && str[i] != ' ' && str[i] != '"' && str[i] != '\'')
		i++;
	return (tab);	
}
