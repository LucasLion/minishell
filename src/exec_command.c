/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:55:58 by llion             #+#    #+#             */
/*   Updated: 2023/03/20 17:45:07 by amouly           ###   ########.fr       */
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
<<<<<<< HEAD
	
	//print_tab(split_path);
}



=======
}

>>>>>>> abc38a2575be912fcddc412a08691c7a26f4904c
char *is_builtin(char *cmd)
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
    else if (ft_strncmp(cmd, "env",	ft_strlen(cmd) + 1) == 0)
        return ("env");
    else if (ft_strncmp(cmd, "exit", ft_strlen(cmd)) == 0)
        return ("exit");
    else
        return (NULL);
}

char    **exec_builtin(char *builtin, char **argv, char **envp)
{
    if (ft_strncmp(builtin, "pwd", ft_strlen(builtin)) == 0)
        pwd();
    else if (ft_strncmp(builtin, "export", ft_strlen(builtin)) == 0)
		envp = ms_export(argv, envp, tab_len(envp));
    else if (ft_strncmp(builtin, "unset", ft_strlen(builtin)) == 0)
        envp = unset(argv, envp);
    else if (ft_strncmp(builtin, "env", ft_strlen(builtin)) == 0)
        env(envp);
    else if (ft_strncmp(builtin, "exit", ft_strlen(builtin)) == 0)
        ms_exit();
    else if (ft_strncmp(builtin, "echo", ft_strlen(builtin)) == 0)
        echo(argv);
	//else if (ft_strncmp(builtin, "cd", ft_strlen(builtin)) == 0)
	//   cd(list, envp);
    return (envp);
}

<<<<<<< HEAD
/*int	exec_command(char **argv, char **envp, t_command *list, char *line)
=======
char	**exec_command(char *command, char **argv, char **envp)
>>>>>>> abc38a2575be912fcddc412a08691c7a26f4904c
{
	char	*path;
	int		status;
	pid_t	pid;
	char	*builtin;
	
	path = get_path(envp, command);
	pid = fork();
	if (pid == 0)
	{
        builtin = is_builtin(command);
        if (builtin)
			envp = exec_builtin(builtin, argv, envp);
        else
            execve(path, argv, envp);
	}
	else if (pid < 0)
		return (NULL);
	else
	{
		wait(&status);
		return (envp);
	}
	return (envp);
}


