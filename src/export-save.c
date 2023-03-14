/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 14:21:07 by llion             #+#    #+#             */
/*   Updated: 2023/03/07 14:41:49 by llion            ###   ########.fr       */
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

t_env	*envlast(t_env *lst) 
{ 
   if (lst)
		while (lst->next)
			lst = lst->next;
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
   return (i);
}

char  	***create_args_list(char *args)
{
   int   i;
   char  **tab;
   int   len;
   char  ***ret;
   char  **split;

   if (args == NULL)
      return (NULL);
   i = 0;
   tab =  ft_split(args, ' ');
   len = tab_len(tab);
   if (len > 0)
   {
      ret = malloc(sizeof(char **) * (len + 1));
      if (ret == NULL)
         return (NULL);
   }
   else
      return (NULL);
   while (i < len)
   {
      ret[i] = malloc(sizeof(char *) * 2);
      split = ft_split(tab[i], '=');
      ret[i][0] = split[0];
      ret[i][1] = split[1];
      i++;
   }
   ret[i] = NULL;
   return (ret);
}

int   ms_export(char ***args, t_env *var, char **envp)
{
   int   i;
   int   j;
   t_env *env;

   i = 0;
   j = 0;
   env = var;
   if (args == NULL)
   {
      while (envp[j])
      {
         printf("%s\n", envp[j]);
         j++;
      }
      return (0);
   }
   if (args && env)
   {
      while (args[i])
      {
         while (env)
         {
            //printf("BEFORE: -%s- -%s-\n", env->name, args[i][0]);
            // TODO comprendre pourquoi l'egalite ne fonctionne pas
            if (env->name == args[i][0])
            {
               printf("Ca a marche");
               env->value = args[i][1];
               printf("AFTER: %s - %s\n", env->value, args[i][1]);
            }
            env = env->next;
         }
         env = var;
         i++;
      }
   }
   return (0);
}

