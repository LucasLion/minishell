/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:55:58 by llion             #+#    #+#             */
/*   Updated: 2023/03/18 11:14:29 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path_split(char **envp)
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
			//ft_strlcat(path, "/", ft_strlen(path) + 1);
		}
		i++;
	}
	split_path = ft_split(path+5, ':');
	return (split_path);
}

char	*get_path(char **envp, char *cmd)
{
	char	**split_path;
	char	*ret;
	char	*temp;
	int		i;

	i = 0;
	split_path = get_path_split(envp);
	while(split_path[i])
	{
		temp = ft_strjoin(split_path[i], "/");
		ret = ft_strjoin(temp, cmd);
		free(temp);
		if (access(ret, X_OK) == 0)
			return (ret);
		free (ret);
		i++;
	}
	return (NULL);
	
	//print_tab(split_path);
}



/*int	exec_command(char *command, char **argv, char **envp)
{
	size_t	exit_status;
	int		status;
	pid_t	pid;
	char	**path;
	int	path_len;
	int	command_len;
	int	exec_len;

	pid = fork();
	path = get_path(envp);
	command_len = ft_strlen(command);
	path_len = ft_strlen(path[4]);
	exec_len = command_len + path_len + 1;
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
}*/


int	exec_command(char *command, char **argv, char **envp)
{
	char	*path;
	size_t	exit_status;
	int		status;
	pid_t	pid;
	
	path = get_path(envp, command);
	if (path == NULL)
	{
		printf ("%s : command not found \n", command);
		return (0);
	}
	pid = fork();
	if (pid == 0)
		exit_status = execve(path, argv, envp);
	else if (pid < 0)
		return (EXIT_FAILURE);
	else
	{
		exit_status = EXIT_FAILURE;
		wait(&status);
	}
	return (exit_status);
}

