/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 14:21:07 by llion             #+#    #+#             */
/*   Updated: 2023/03/06 17:31:36 by llion            ###   ########.fr       */
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

   i = 0;
   env = malloc(sizeof(t_env));
   while (envp[i])
   {
      var = ft_split(envp[i], '=')[0];
      val = ft_split(envp[i], '=')[1];
      cur = varnew(var, val);
      var_addback(&env, cur);
      i++;
   }
   i = 0;
   return (env);
}

int   tab_len(char **tab)
{
   int i;

   i = 0;
   while (tab[i])
   {
      i++;
   }
   printf("%d\n", i);
   return (i);
}

char  	***create_args_list(char *args)
{
   int   i;
   char  **tab;
   int   len;
   char  ***ret;

   i = 0;
   tab =  ft_split(args, ' ');
   len = tab_len(tab);
   ret = malloc(sizeof(char *) * len);
   while (i < len)
   {
      ret[i] = malloc(sizeof(char) * 2);
      ret[i][0] = ft_split(tab[i], '=')[0];
      ret[i][1] = ft_split(tab[i], '=')[1];

      i++;
   }
   ret[i] = 0;
   return (ret);
}

int   ms_export(char **envp, char *args, t_env *var)
{
   (void)envp;
   (void)args;
   t_env *env;

   env = var;
   if (env)
   {
      while (env)
      {
         printf("ENV_VAR: %s\n ENV_VAL: %s\n", env->name, env->value);
         env = env->next;
      }
   }
   return (0);
}

