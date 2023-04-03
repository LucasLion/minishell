/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 18:39:28 by llion             #+#    #+#             */
/*   Updated: 2023/04/03 12:49:23 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_args(char *line, char **envp)
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
			if (ft_strncmp(envp[j], vars[i], var_size) == 0
				&& ((int)ft_strlen(vars[i]) == var_size))
				count++;
			j++;
		}
		i++;
	}
	ft_freetab(vars);
	return (count);
}

int	compare_args(char *str, char **envp)
{
	int		i;
	char	*var_arg;

	i = 0;
	while (envp[i])
	{
		var_arg = var(envp[i]);
		if (ft_strncmp(var_arg, str, ft_strlen(str) + 1) == 0)
		{
			free(var_arg);
			return (0);
		}
		i++;
		free(var_arg);
	}
	return (1);
}

int	compare_args2(char *str, char **args)
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

char	**new_argv(char **argv, char **envp)
{
	int		i;
	int		j;
	int		count;
	char	**nargv;

	i = 1;
	j = 0;
	count = 0;
	while (argv[i])
	{
		if (!compare_args(argv[i], envp))
			count++;
		i++;
	}
	nargv = ft_calloc(count + 1, sizeof(char *));
	i = 1;
	while (argv[i])
	{
		if (!compare_args(argv[i], envp))
			nargv[j++] = ft_strdup(argv[i]);
		i++;
	}
	return (nargv);
}

int	unset(char **argv, char ***envp)
{
	int		i;
	int		j;
	char	**new_envp;
	char	**nargv;
	int		new_len;

	i = 1;
	j = 0;
	if (argv[1])
	{
		new_len = ft_tablen(*envp) - ft_tablen(argv) + 1;
		new_envp = ft_calloc(new_len + 1, sizeof(char *));
		nargv = new_argv(argv, *envp);
		if (new_envp == NULL)
			return (ms_error("unset", NULL, errno));
		while (i < new_len + 1 && new_len > 0)
		{
			if (compare_args2((*envp)[i], nargv))
				new_envp[j++] = ft_strdup((*envp)[i]);
			i++;
		}
		
		ft_freetab(nargv);
		ft_freetab(*envp);
		*envp = new_envp;	
	}
	return (0);
}

