/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:55:58 by llion             #+#    #+#             */
/*   Updated: 2023/03/29 17:24:16 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exit_shell(int status)
{
	exit(status % 255);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status));
	return (EXIT_SUCCESS);
}

void    wait_proof(t_core *minishell, int pid)
{
    int status;
    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        minishell->last_status = WEXITSTATUS(status) % 255;
}

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

int	ms_error(char *cmd, char *input, int error)
{
	char *str_error;

	if (error == 0)
		return (error);
	str_error = strerror(error);
	if (error == 127)
		printf("Minishell: %s: command not found \n", cmd);
	else if (error == 1)
		printf("export: %s: not a valid identifier\n", cmd);
	else
	{
		printf("error: %d\n", error);
		write_error(cmd, input, error);
	}
	return (errno);
}

