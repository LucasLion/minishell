/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 14:21:07 by llion             #+#    #+#             */
/*   Updated: 2023/03/28 14:10:37 by llion            ###   ########.fr       */
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

int	ms_error(char *cmd, char *input, int error)
{
	char *str_error;

	printf("MS_EXIT\n");
	str_error = strerror(error);
	if (error == 14)
		printf("Minishell : command not found hihi / erreur %d \n", error);
	else if (error == 1)
		printf("export: %s: not a valid identifier\n", cmd);
	else
		write_error(cmd, input, error);
	return (errno);
}

int	pwd()
{
	char buffer[1024];

	if (getcwd(buffer, sizeof(buffer)) == NULL)
		return (ms_error(NULL, NULL, errno));
	printf("%s\n", buffer);
	return (0);
}

int env(char **envp)
{
    int i;

    i = 0;
    while (envp[i])
	{
		if (envp[i] == NULL)
			return (ms_error("env", NULL, errno));
        printf("%s\n", envp[i++]);
	}
	return (0);
}
