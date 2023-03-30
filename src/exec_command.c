/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:55:58 by llion             #+#    #+#             */
/*   Updated: 2023/03/30 17:40:05 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**get_path_split(char **envp)
{
	int		i;
	char	*path;
	char	**split_path;

	i = 0;
	path = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
			path = ft_strdup(envp[i]);
		i++;
	}
	split_path = ft_split(path + 5, ':');
	free(path);
	return (split_path);
}

char	*get_path(char **envp, char *cmd)
{
	char	**split_path;
	char	*ret;
	char	*tmp;
	int		i;

	i = 0;
	split_path = get_path_split(envp);
	while (split_path[i])
	{
		tmp = ft_strjoin(split_path[i], "/");
		ret = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(ret, X_OK) == 0)
		{
			free_tab2(split_path);
			return (ret);
		}
		free(ret);
		i++;
	}
	free_tab2(split_path);
	if (access(cmd, X_OK) == 0)
		return (cmd);
	return (cmd);
}

char	*is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", ft_strlen(cmd) + 1) == 0)
		return ("echo");
	else if (ft_strncmp(cmd, "cd", ft_strlen(cmd) + 1) == 0)
		return ("cd");
	else if (ft_strncmp(cmd, "pwd", ft_strlen(cmd) + 1) == 0)
		return ("pwd");
	else if (ft_strncmp(cmd, "export", ft_strlen(cmd) + 1) == 0)
		return ("export");
	else if (ft_strncmp(cmd, "unset", ft_strlen(cmd) + 1) == 0)
		return ("unset");
	else if (ft_strncmp(cmd, "env", ft_strlen(cmd) + 1) == 0)
		return ("env");
	else if (ft_strncmp(cmd, "exit", ft_strlen(cmd) + 1) == 0)
		return ("exit");
	else
		return (NULL);
}

int	exec_builtin(char *builtin, char **argv, char ***envp, int *status)
{
	if (ft_strncmp(builtin, "pwd", ft_strlen(builtin)) == 0)
		*status = pwd();
	else if (ft_strncmp(builtin, "export", ft_strlen(builtin)) == 0)
		*status = ms_export(argv, envp);
	else if (ft_strncmp(builtin, "unset", ft_strlen(builtin)) == 0)
		*status = unset(argv, envp);
	else if (ft_strncmp(builtin, "exit", ft_strlen(builtin)) == 0)
		*status = exit_shell(*status, argv);
	else if (ft_strncmp(builtin, "env", ft_strlen(builtin)) == 0)
		*status = env(*envp);
	else if (ft_strncmp(builtin, "echo", ft_strlen(builtin)) == 0)
		*status = echo(argv);
	else if (ft_strncmp(builtin, "cd", ft_strlen(builtin)) == 0)
		*status = cd(argv[1], *envp);
	return (*status % 255);
}

void	exec_command(char *command, char **argv, char ***envp)
{
	char	*path;

	path = get_path(*envp, command);
	signal(SIGQUIT, SIG_DFL);
	if (execve(path, argv, *envp) == -1)
		exit_shell(127, argv);
	signal(SIGQUIT, SIG_IGN);
	exit_shell(errno, argv);
}
