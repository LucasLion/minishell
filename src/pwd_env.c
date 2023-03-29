/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 14:21:07 by llion             #+#    #+#             */
/*   Updated: 2023/03/29 13:23:12 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


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
    int		i;
	char	*val;

    i = 0;
    while (envp[i])
	{
		val = extract_val(envp[i]);
		if (envp[i] == NULL)
			return (ms_error("env", NULL, errno));
		else if (val == NULL)
			i++;
		else
			printf("%s\n", envp[i++]);
	}
	return (0);
}
