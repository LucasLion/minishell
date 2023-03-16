/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+ #+#+   +#+          */
/*   Created: 2023/03/10 18:39:28 by llion             #+#    #+#             */
/*   Updated: 2023/03/16 11:55:00 by llion            ###   ########.fr       */
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

char	**args_list(char **envp, char *line)
{
	int		i;
	int		j;
	int		k;
	char	**args;
	char	**vars;
	int		size;

	size = check_args(line, envp);
	args = ft_calloc(size + 1, sizeof(char *));
	vars = ft_split(line, ' ');
	k = 0;
	i = 0;
	while (vars[i])
	{
		j = 0;
		while (envp[j])
		{
			if (ft_strncmp(envp[j], vars[i], size) == 0)
			{
				args[k] = ft_strdup(vars[i]);
				k++;
			}
			j++;
		}
		i++;
	}
	args[k] = 0;
	return (args);
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
char	**unset(char **envp, char *line)
{
	int		i;
	char	**new_envp;
	char	**args;

	// TODO la fonction segfault la deuxieme fois
	// peu d'indices
	args = args_list(envp, line);
	new_envp = ft_calloc(tab_len(envp) - tab_len(args), sizeof(char *));
	i = 0;
	while(i < tab_len(envp) - tab_len(args))
	{
		if (compare_args(envp[i], args))
		{
			new_envp[i] = ft_strdup(envp[i]);	
			// il faudra tout free
			//printf("%d: %s\n", i, new_envp[i]);
		}
		i++;
	}
	new_envp[i] = 0;
	return (new_envp);
}

