/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 18:33:35 by llion             #+#    #+#             */
/*   Updated: 2023/03/25 13:49:02 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *get_env_variable(char **envp, char *variable)
{
	int		i;
	char	*user;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(extract_var(envp[i]), variable, ft_strlen(variable)) == 0)
		{
			user = extract_val(envp[i]);
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
	parsed = ft_calloc(ft_strlen(tilde) + ft_strlen(input) - 2 + 1, sizeof(char));
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
	else if (input[0] == '-' && input[1] == '\0')
		return (get_env_variable(envp, "OLDPWD"));
	return (parsed);
}

int	cd(char *input, char **envp)
{
	int		id;
	char	*abs_path;

	if (input[0] == '~' || input[0] == '-')
	{
		abs_path = create_absolute_path(input, envp);
		id = chdir(abs_path);
	}
	else 
		id = chdir(input);
	if (id != 0)
		return (1);
	return (0);
}
