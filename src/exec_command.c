/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:55:58 by llion             #+#    #+#             */
/*   Updated: 2023/03/17 15:13:54 by llion            ###   ########.fr       */
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



int	exec_command(char *command, char **argv, char **envp)
{
	size_t	exit_status;
	int		status;
	pid_t	pid;
	//char	**path;
    (void)command;
	pid = fork();
	//path = get_path(envp);
	if (pid == 0)
		exit_status = execve("/bin/df", argv, envp);
	else if (pid < 0)
		return (EXIT_FAILURE);
	else
	{
		exit_status = EXIT_FAILURE;
		wait(&status);
	}
	return (exit_status);
}
