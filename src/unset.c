/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+ #+#+   +#+          */
/*   Created: 2023/03/10 18:39:28 by llion             #+#    #+#             */
/*   Updated: 2023/03/20 13:57:16 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_var_size(char *var)
{
	int	i;

	i = 0;
	while (var[i] != '=')
		i++;
	return (i);
}

int check_args(char *line, char **envp)
{
	int		i;
	int		j;
	int		count;
	int		var_size;
	char	**vars;

	vars = ft_split(line, ' ');
	i = 0;
	count = 0;
	while (vars[i])
	{
		j = 0;
		while (envp[j])
		{
			var_size = count_var_size(envp[j]);
			if (ft_strncmp(envp[j], vars[i], var_size) == 0 && ((int)ft_strlen(vars[i]) == var_size))
				count++;
			j++;
		}
		i++;
	}
	free_tab2(vars);
	return (count);
}

int	compare_args(char *str, char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (ft_strncmp(args[i], str, ft_strlen(args[i])) == 0)
			return (0);
		i++;
	}
	return (1);
}

char	**unset(char **argv, char **envp)
{
	int		i;
	int		j;
	char	**new_envp;
	int		new_len;

	new_len = tab_len(envp) - tab_len(argv) + 1;
	new_envp = ft_calloc(new_len + 1, sizeof(char *));
	new_envp[new_len] = 0;
	i = 0;
	j = 0;
	while(i < new_len + 1) 
	{
		if (compare_args(envp[i], argv))
		{
			new_envp[j] = ft_strdup(envp[i]);	
			j++;
		}
		i++;
	}
	free_tab2(envp);
	return (new_envp);
}

