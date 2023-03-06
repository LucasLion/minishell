/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 14:21:07 by llion             #+#    #+#             */
/*   Updated: 2023/03/06 14:45:26 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*varnew(char *var, char *val)
{
	t_env	*duet;

	duet = (malloc(sizeof(t_env)));
	if (duet == NULL)
		return NULL;
	duet->name = var;
	duet->value = val;
    duet->next = NULL;
	return (duet);
}

t_env	*envlast(t_env *lst) { if (lst)
	{
		while (lst->next)
		{
			lst = lst->next;
		}
	}
	return (lst);
}

void  var_addback(t_env **env, t_env *new)
{
   t_env *cur;

   if (*env == NULL)
      *env = new;
   else
   {
      cur = envlast(*env);
      cur->next = new;
   }
}

t_env	*create_var_list(char **envp)
{
   int   i;
   t_env *env;
   t_env *cur;
   char  *var;
   char  *val;
   char  **duet;

   i = 0;
   env = malloc(sizeof(t_env));
   while (envp[i])
   {
      duet = ft_split(envp[i], '=');
      var = duet[0];
      val = duet[1];
      cur = varnew(var, val);
      var_addback(&env, cur);
      i++;
   }
   i = 0;
   while (env)
   {
      printf("NAME: %s\tVALUE: %s\n", env->name, env->value);
      env = env->next;
   }
   return (env);
}

int   ms_export(char **envp, t_env *env)
{
   (void)envp;
   while (env)
   {
      printf("ENV_VAR: %s\n ENV_VAL: %s\n", env->name, env->value);
      env = env->next;
   }
   return (0);
}

