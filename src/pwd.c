/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 14:21:07 by llion             #+#    #+#             */
/*   Updated: 2023/03/27 18:44:58 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	write_error(char *cmd, char *input, int error_no)
{
	int len;
	char *err_str;

	write(STDERR_FILENO, "Minishell: ", 11);
	if (cmd != NULL)
	{
		len = ft_strlen(cmd);
		write(STDERR_FILENO, cmd, len);
		write(STDERR_FILENO, ": ", 2);
	}
	if (input != NULL)
	{
		len = ft_strlen(input);
		write(STDERR_FILENO, input, len);
		write(STDERR_FILENO, ": ", 2);
	}
	err_str = strerror(error_no);
	len = ft_strlen(err_str);
	write(STDERR_FILENO, err_str, len);
	write(STDERR_FILENO, "\n", 2);
}

int	ms_exit(char *cmd, char *input, int status)
{
	char *error;

	printf("MS_EXIT\n");
	error = strerror(status);
	(void)error;
	if (status == 14)
		printf("Minishell : command not found\n");
	else if (status == 1)
		printf("export: %s: not a valid identifier\n", cmd);
	else
		write_error(cmd, input, status);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status));
	return (EXIT_SUCCESS);
}

void	pwd()
{
	char buffer[1024];

	if (getcwd(buffer, sizeof(buffer)) == NULL)
	{
		printf("Error");
        //HANDLE ERROR
		int i = ms_exit(NULL, NULL, errno);
		printf("%d\n", i);
	}
	printf("%s\n", buffer);
}

void    env(char **envp)
{
    int i;

    i = 0;
    while (envp[i])
    {
        printf("%s\n", envp[i]);
        i++;
    }
}
