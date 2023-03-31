/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:12:49 by llion             #+#    #+#             */
/*   Updated: 2023/03/31 16:36:42 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_if_variable(char *arg, char **envp)
{
	int		i;
	char	*var_arg;
	char	*var_env;
	int		flag;

	i = 0;
	flag = 0;
	var_arg = var(arg);
	while (envp[i])
	{
		var_env = var(envp[i]);
		if (ft_strncmp(var_env, var_arg, ft_strlen(var_arg) + 1) == 0)
			flag = 1;
		i++;
		free(var_env);
	}
	free(var_arg);
	return (flag);
}

char	**add_new_variable(char *arg, char **envp)
{
	int		i;
	char	*var_arg;
	char	*val_arg;
	char	**nenvp;

	i = 0;
	nenvp = allocate_tab(ft_tablen(envp));
	val_arg = val(arg);
	var_arg = var(arg);
	loop(&i, ft_tablen(envp), nenvp, envp);
	if (val_arg == 0)
	{
		nenvp[i] = ft_calloc(ft_strlen(var_arg) + 2, sizeof(char));
		ft_strlcat(nenvp[i], var_arg, ft_strlen(var_arg) + 1);
	}
	else
	{
		nenvp[i] = allocate((int)ft_strlen(var_arg) + (int)ft_strlen(val_arg)
				+ 2, nenvp);
		cat(nenvp[i], arg);
	}
	free_tab2(envp);
	free(val_arg);
	free(var_arg);
	return (nenvp);
}

char	**edit_variable(char *arg, char **envp)
{
	int		i;
	char	**nenvp;
	char	*val_arg;
	char	*var_arg;
	char	*var_env;

	i = 0;
	val_arg = val(arg);
	var_arg = var(arg);
	if (val_arg == NULL)
		return (envp);
	nenvp = allocate_tab(ft_tablen(envp));
	var_env = var(envp[i]);
	while (i < ft_tablen(envp) && ft_strncmp(var_env, var_arg,
			ft_strlen(var_arg)) != 0)
	{
		nenvp[i] = ft_strdup(envp[i]);
		free(var_env);
		var_env = var(envp[i++]);
	}
	nenvp[i] = allocate(ft_strlen(var_arg) + ft_strlen(val_arg) + 2, nenvp);
	cat(nenvp[i++], arg);
	loop(&i, ft_tablen(envp), nenvp, envp);
	free_export(val_arg, var_arg, var_env, envp);
	return (nenvp);
}

int	modifiy_env(char *arg, char ***envp)
{
	int	is_new;

	is_new = check_if_variable(arg, *envp);
	if (is_new == 0)
		*envp = add_new_variable(arg, *envp);
	else
	{
		*envp = edit_variable(arg, *envp);
		if (*envp == NULL)
			return (ms_error("export", NULL, errno));
	}
	return (0);
}

int	ms_export(char **argv, char ***envp, int *status)
{
	int	i;

	i = 1;
	if (ft_tablen(argv) == 1)
		display_export(*envp);
	else
	{
		while (argv[i])
		{
			if (!parse_arg(argv[i], status))
			{
				i++;
				continue ;
			}
			if (ft_strlen(argv[i]) > 0 && !(ft_strlen(argv[i]) == 1
					&& argv[i][0] == '='))
				modifiy_env(argv[i], envp);
			i++;
		}
	}
	return (*status);
}
