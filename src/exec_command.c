/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:55:58 by llion             #+#    #+#             */
/*   Updated: 2023/04/03 19:58:47 by llion            ###   ########.fr       */
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
	if (path == NULL)
		return (NULL);
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
	while (split_path && split_path[i])
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
	if (split_path == NULL)
		return (NULL);
	free_tab2(split_path);
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

int	exec_builtin(char *builtin, char **argv, t_core *m)
{
	if (ft_strncmp(builtin, "pwd", ft_strlen(builtin)) == 0)
		m->last_status = pwd();
	else if (ft_strncmp(builtin, "export", ft_strlen(builtin)) == 0)
		m->last_status = ms_export(argv, &(m->envp), &(m->last_status));
	else if (ft_strncmp(builtin, "unset", ft_strlen(builtin)) == 0 && argv)
		m->last_status = unset(argv, &m->envp);
	else if (ft_strncmp(builtin, "exit", ft_strlen(builtin)) == 0)
		m->last_status = exit_shell(argv, m);
	else if (ft_strncmp(builtin, "env", ft_strlen(builtin)) == 0)
		m->last_status = env(m->envp);
	else if (ft_strncmp(builtin, "echo", ft_strlen(builtin)) == 0)
		m->last_status = echo(argv);
	else if (ft_strncmp(builtin, "cd", ft_strlen(builtin)) == 0)
		m->last_status = cd(argv[1], m->envp);
	return (m->last_status % 255);
}

int	exec_command(char *cmd, char **argv, char ***envp)
{
	char	*path;

	signal(SIGQUIT, SIG_DFL);
	path = get_path(*envp, cmd);
	if ((cmd && cmd[0] == '/') || path == NULL)
	{
		if (access(cmd, X_OK) == 0)
			execve(cmd, argv, *envp);
		else
		{
			ms_error(cmd, NULL, 2);
			exit(127);
		}
	}
	else
	{
		if (execve(path, argv, *envp) == -1)
			exit(127);
	}
	signal(SIGQUIT, SIG_IGN);
	exit(0);
}
