/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:55:58 by llion             #+#    #+#             */
/*   Updated: 2023/04/03 16:04:33 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	frexit(int flag, int i, char **argv, t_core *minishell)
{
	ft_freetab(minishell->envp);
	if (flag == 1)
	{
		ms_error("exit", argv[i], -4);
		exit(255);
	}
	if (flag == 2)
	{
		printf("Exiting minishell...\n");
		exit(ft_atoi(argv[i]) % 256);
	}
	if (flag == 3)
	{
		printf("Exiting minishell...\n");
		exit(i);
	}
}

int	exit_shell(char **argv, t_core *minishell)
{
	int	i;

	i = 0;
	if (argv[1])
	{
		while (argv[1][i])
		{
			if (argv[1][i] < '0' || argv[1][i] > '9')
				frexit(1, i, argv, minishell);
			i++;
		}
		if (ft_tablen(argv) > 2)
		{
			ms_error("exit", NULL, -10);
			return (1);
		}
		else
			frexit(2, 1, argv, minishell);
	}
	frexit(3, 0, argv, minishell);
	return (0);
}

void	write_error(char *cmd, char *input, int error_no)
{
	int		len;
	char	*err_str;

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

void	wait_proof(t_core *minishell, int pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		minishell->last_status = WEXITSTATUS(status) % 255;
}

int	ms_error(char *cmd, char *input, int error)
{
	if (error == 0)
		return (error);
	else if (error == -3)
		printf("Minishell: syntax error near unexpected token `newline'\n");
	else if (error == -2)
		printf("Minishell: %s: ambiguous redirect \n", cmd);
	else if (error == 127)
		printf("Minishell: %s: command not found \n", cmd);
	else if (error == -5 && ft_strncmp(cmd, "exit", 4) == 0)
		printf("Minishell: %s: too many arguments\n", cmd);
	else if (error == -5)
		printf("Minishell: %s: `%s': not a valid identifier\n", cmd, input);
	else if (error == -4)
		printf("Minishell: %s: argument numérique nécessaire\n", cmd);
	else if (error == -10)
		printf("Minishell: %s: too many arguments\n", cmd);
	else
		write_error(cmd, input, error);
	return (errno);
}
