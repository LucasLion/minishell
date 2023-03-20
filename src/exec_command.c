/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:55:58 by llion             #+#    #+#             */
/*   Updated: 2023/03/20 11:12:49 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

char *is_builtin(char *cmd)
{
    if (ft_strncmp(cmd, "echo", ft_strlen(cmd)) == 0)
        return ("echo");
    else if (ft_strncmp(cmd, "cd", ft_strlen(cmd)) == 0)
        return ("cd");
    else if (ft_strncmp(cmd, "pwd", ft_strlen(cmd)) == 0)
        return ("pwd");
    else if (ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0)
        return ("export");
    else if (ft_strncmp(cmd, "unset", ft_strlen(cmd)) == 0)
        return ("unset");
    else if (ft_strncmp(cmd, "env",	3) == 0)
        return ("env");
    else if (ft_strncmp(cmd, "exit", ft_strlen(cmd)) == 0)
        return ("exit");
    else
        return (NULL);
}

int    exec_builtin(char *builtin, t_command *list, char **envp)
{
    (void)list;

    if (ft_strncmp(builtin, "pwd", 3) == 0)
        pwd();
    else if (ft_strncmp(builtin, "export", 6) == 0)
        ms_export(envp, tab_len(envp), list->input->string);
    else if (ft_strncmp(builtin, "unset", 5) == 0)
        unset(envp, builtin);
    else if (ft_strncmp(builtin, "env", 3) == 0)
        env(envp);
    else if (ft_strncmp(builtin, "exit", 4) == 0)
        ms_exit();
	//else if (ft_strncmp(builtin, "echo", 4) == 0)
    //    echo();
	//else if (ft_strncmp(builtin, "cd", 2) == 0)
	//    cd(list, envp);
    return (0);
}

int	exec_command(char **argv, char **envp, t_command *list, char *line)
{
	int	exit_status;
	int		status;
	char	*cmd;
    char    *builtin;

	pid_t	pid;
	pid = fork();
	if (pid == 0)
	{
		parse_input(line, &list);
		add_history(line);
        builtin = is_builtin(list->command->string);
        cmd = get_command(list, envp);
        if (builtin)
            return (exec_builtin(builtin, list, envp));
        else
            return (execve(cmd, argv, envp));
	}
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

