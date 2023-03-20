/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 14:21:07 by llion             #+#    #+#             */
/*   Updated: 2023/03/20 13:59:03 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ms_exit()
{
	int	status;

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status));
	return (EXIT_FAILURE);
}

void	pwd()
{
	char buffer[1024];

	if (getcwd(buffer, sizeof(buffer)) == NULL)
	{
		printf("Error");
		exit(EXIT_FAILURE);
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
