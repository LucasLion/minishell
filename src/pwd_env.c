/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 14:21:07 by llion             #+#    #+#             */
/*   Updated: 2023/03/31 13:45:00 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	pwd(void)
{
	char	buffer[1024];

	if (getcwd(buffer, sizeof(buffer)) == NULL)
		return (ms_error(NULL, NULL, errno));
	printf("%s\n", buffer);
	return (0);
}

int	env(char **envp)
{
	int		i;
	char	*value;

	i = 0;
	while (envp[i])
	{
		value = val(envp[i]);
		if (envp[i] == NULL)
			return (ms_error("env", NULL, errno));
		else if (value == NULL)
			i++;
		else
			printf("%s\n", envp[i++]);
	}
	return (0);
}
