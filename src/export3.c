/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:45:14 by llion             #+#    #+#             */
/*   Updated: 2023/03/30 16:46:25 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void  loop(int i, int env_size, char **nenvp, char **envp)
{
   while (i < env_size)
   {
      nenvp[i] = ft_strdup((envp)[i]);
      i++;
   }
}

void  cat(char *nenvp, char *arg)
{
   ft_strlcat(nenvp, var(arg), ft_strlen(var(arg)) + 1); 
   ft_strlcat(nenvp, "=", ft_strlen(var(arg)) + 2); 
   ft_strlcat(nenvp, val(arg), ft_strlen(var(arg)) + ft_strlen(val(arg)) + 2); 
}

char **allocate_tab(int size)
{
   char **nenvp;

	nenvp = ft_calloc(size + 2, sizeof(char *));
	if (nenvp == NULL)
		return (NULL);
	return (nenvp);
}

char *allocate(int size, char **nenvp)
{
   char *line;

   line = ft_calloc(size + 1, sizeof(char));
   if (line == NULL)
   {
	  free_tab2(nenvp);
	  return (NULL);
   }
   return (line);
}

char *val(char *arg)
{
   int   i;
   int   j;
   char  *val;

   i = 0;
   j = 0;
   while (arg[i] != '\0' && arg[i] != '=')
      i++;
   if (arg[i] == '\0')
      return (NULL);
   val = ft_calloc(ft_strlen(arg) - i + 1, sizeof(char));
   if (val == NULL)
      return (NULL);
   i++;
   while (arg[i])
   {
      val[j] = arg[i];
      i++;
      j++;
   }
   val[j] = '\0';
   return (val);
}

