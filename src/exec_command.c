/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:55:58 by llion             #+#    #+#             */
/*   Updated: 2023/03/18 16:10:06 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**get_path(char **envp)
{
	int	i;
	char	*path;
	char	**split_path;

	i = 0;
	path = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
		{
			path = ft_strdup(envp[i]);
			ft_strlcat(path, "/", ft_strlen(path) + 1);
		}
		i++;
	}
	split_path = ft_split(path+5, ':');
	return (split_path);
}

char	*get_command(t_command *list, char **envp)
{
	char	*cmd;
	char	*pre_cmd;
	char	**path;
	int	i;

	i = 0;
	path = get_path(envp);
	pre_cmd = NULL;
	cmd = NULL;
	while (path[i])
	{
		pre_cmd = ft_strjoin(path[i], "/");
		cmd = ft_strjoin(pre_cmd, list->command->string);
		if (access(cmd, F_OK) == 0)
			return (cmd);
		i++;
	}
	return (cmd);
}

int	exec_command(char **argv, char **envp, t_command *list, char *line)
{
	(void)argv;
	(void)envp;
	int	exit_status;
	int		status;
	char	*cmd;

	pid_t	pid;
	pid = fork();
	if (pid == 0)
	{
		parse_input(line, &list);
		add_history(line);
		cmd = get_command(list, envp);
		exit_status = execve(cmd, argv, envp);
	}
	else if (pid < 0)
		return (EXIT_FAILURE);
	else
	{
		exit_status = EXIT_FAILURE;
		wait(&status);
	}
	return (exit_status);
}
