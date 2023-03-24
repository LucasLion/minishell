/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 18:33:35 by llion             #+#    #+#             */
/*   Updated: 2023/03/24 18:58:12 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// TODO EN CHANTIER

char *get_user(char **envp)
{
	int		i;
	//char	*user;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(extract_var(envp[i]), "USER", 5) == 0)
			printf("env: %s\n", envp[i]);
			//user = extract_val(envp[i]);
	}
	return (NULL);
}

int	cd(char *path, char **envp)
{
	(void)path;
	//int	id;
	char	*user;

	user = get_user(envp);
	printf("User Baby! %s\n", user);
	//id = chdir(path);
	//if (id != 0)
	//{
	//	printf("Erreur lors du changement de répertoire de travail\n");
	//	return (1);
	//}
	//printf("Répertoire de travail modifié\n");
	return (0);
}
