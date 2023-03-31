/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:45:14 by llion             #+#    #+#             */
/*   Updated: 2023/03/31 13:40:38 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	loop(int *i, int env_size, char **nenvp, char **envp)
{
	while (*i < env_size)
	{
		nenvp[*i] = ft_strdup((envp)[*i]);
		(*i)++;
	}
}

void	cat(char *nenvp, char *arg)
{
	char	*var_arg;
	char	*val_arg;

	var_arg = var(arg);
	val_arg = val(arg);
	ft_strlcat(nenvp, var_arg, ft_strlen(var_arg) + 1);
	ft_strlcat(nenvp, "=", ft_strlen(var_arg) + 2);
	ft_strlcat(nenvp, val_arg, ft_strlen(var_arg) + ft_strlen(val_arg) + 2);
	free(var_arg);
	free(val_arg);
}

char	**allocate_tab(int size)
{
	char	**nenvp;

	nenvp = ft_calloc(size + 2, sizeof(char *));
	if (nenvp == NULL)
		return (NULL);
	return (nenvp);
}

char	*allocate(int size, char **nenvp)
{
	char	*line;

	line = ft_calloc(size + 1, sizeof(char));
	if (line == NULL)
	{
		free_tab2(nenvp);
		return (NULL);
	}
	return (line);
}

char	*val(char *arg)
{
	int		i;
	int		j;
	char	*val;

	i = 0;
	j = 0;
	while (arg[i] != '\0' && arg[i] != '=')
		i++;
	if (arg[i] == '\0')
		return (NULL);
	val = ft_calloc(ft_strlen(arg) - i + 1, sizeof(char));
	if (val == NULL)
		return (NULL);
	i++;
	while (arg[i])
	{
		val[j] = arg[i];
		i++;
		j++;
	}
	val[j] = '\0';
	return (val);
}
