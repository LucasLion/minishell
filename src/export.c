/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 14:21:07 by llion             #+#    #+#             */
/*   Updated: 2023/03/08 19:00:05 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
      ret[i][0] = malloc(sizeof(char) * (ft_strlen(split[0])));
      ret[i][1] = malloc(sizeof(char) * (ft_strlen(split[1])));
      ft_strlcpy(ret[i][0], split[0], (ft_strlen(split[0]) + 1));
      ft_strlcpy(ret[i][1], split[1], (ft_strlen(split[1]) + 1));
      i++;
   }
   ret[i] = NULL;
   return (ret);
}

char  ***create_env_list(char **envp)
{
   int   i;
   int   len;
   char  **split;
   char  ***ret;


   len = tab_len(envp);
   if (len > 0)
   {
      ret = malloc(sizeof(char **) * (len + 1));
      if (ret == NULL)
         return (NULL);
   }
   i = 0;
   while (i < len)
   {
      ret[i] = malloc(sizeof(char *) * 2);
      split = ft_split(envp[i], '=');

      ret[i][0] = malloc(sizeof(char) * (ft_strlen(split[0])));
      ret[i][1] = malloc(sizeof(char) * (ft_strlen(split[1])));
      ft_strlcpy(ret[i][0], split[0], (ft_strlen(split[0]) + 1));
      ft_strlcpy(ret[i][1], split[1], (ft_strlen(split[1]) + 1));
      i++;
   }
   // TODO results in undefined value;
   ret[i] = NULL;
   return (ret);

}

int   add_new_variable(char **arg, char **envp)
{
   int   i;
   int   env_size;
   int   line_size;
   char **new_envp;

   i = 0;
   env_size = tab_len(envp);
   new_envp = malloc(sizeof(char *) * (env_size + 1));
   line_size = ft_strlen(arg[0]) + ft_strlen(arg[1]) + 2;
   while (i < env_size)
   {
      new_envp[i] = ft_strdup(envp[i]);
      i++;
   }
   new_envp[i] = malloc(sizeof(char) * (line_size));
   ft_strlcpy(new_envp[i], arg[0], ft_strlen(new_envp[i])); 
   ft_strlcpy(new_envp[i], "=", ft_strlen(new_envp[i])); 
   ft_strlcpy(new_envp[i], arg[1], ft_strlen(new_envp[i])); 
   // TODO bien copier la nouvelle variable a la fin
   // pas sur de comment ajouter le =
   return (0);
}

int   ms_export(char ***args, char ***env, char **envp)
{
   int   i;
   int   j;
   int   flag;

   i = 0;
   flag = 0;
   while (args[i])
   {
      j = 0;
      while (env[j])
      {
         if (ft_strncmp(env[j][0], args[i][0], (ft_strlen(args[i][0] + 1))) == 0)
         {
            ft_strlcpy(env[j][1], args[i][1], (ft_strlen(args[i][1]) + 1));
            flag = 1;
         }
         j++;
      }
      if (flag == 1)
      {
         add_new_variable(args[i], envp);
         flag = 0;
      }
      i++;
   }

   return (0);
}

