/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 18:33:35 by llion             #+#    #+#             */
/*   Updated: 2023/04/01 13:14:35 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_env_variable(char **envp, char *variable)
{
	int		i;
	char	*user;

	i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp(var(envp[i]), variable, ft_strlen(variable)) == 0)
		{
			user = val(envp[i]);
			return (user);
		}
		i++;
	}
	return (NULL);
}

char	*create_absolute_path(char *input, char **envp)
{
	char	*tilde;
	char	*parsed;

	tilde = get_env_variable(envp, "HOME");
	parsed = ft_calloc(ft_strlen(tilde) + ft_strlen(input) - 2 + 1,
			sizeof(char));
	if (parsed == NULL)
	{
		free(tilde);
		return (NULL);
	}
	if (input[0] == '~' && input[1] == '/')
		parsed = ft_strjoin(tilde, input + 1);
	else if (input[0] == '~' && input[1] != '/' && input[1] != '\0')
	{
		ft_strlcat(parsed, tilde, ft_strlen(tilde) + 1);
		ft_strlcat(parsed, "/", ft_strlen(tilde) + 2);
		ft_strlcat(parsed, input + 1, ft_strlen(parsed) + ft_strlen(tilde) + 1);
	}
	else if (input[0] == '~' && input[1] == '\0')
		parsed = tilde;
	free(tilde);
	return (parsed);
}

int only_space_until_end(char *str, int i)
{
	if(str[i] == '\0')
		return (1);
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}


int	cd(char *input, char **envp)
{
	int		id;
	char	*abs_path;

	if (input && input[0])
	{
		if (input[0] == '~' || input[0] == '-')
		{
			abs_path = create_absolute_path(input, envp);
			if (abs_path == NULL)
				return (1);
			id = chdir(abs_path);
			free(abs_path);
		}
		else
			id = chdir(input);
		if (id != 0)
		{
			ms_error("cd", input, errno);
			return (1);
		}
	}
	return (0);
}
