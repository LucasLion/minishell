/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 14:21:07 by llion             #+#    #+#             */
/*   Updated: 2023/03/09 16:28:52 by llion            ###   ########.fr       */
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

char  ***create_env_list(char **envp, int env_len)
{
   int   i;
   char  **split;
   char  ***ret;

   env_len = tab_len(envp);
   if (env_len > 0)
   {
      ret = malloc(sizeof(char **) * (env_len + 2));
      if (ret == NULL)
         return (NULL);
   }
   else
      return (NULL);
   ret[env_len + 1] = NULL;
   i = 0;

   while (i < env_len)
   {
      ret[i] = malloc(sizeof(char *) * 2);
      //printf("%s", ret[i][1]);
      split = ft_split(envp[i], '=');
      ret[i][0] = ft_strdup(split[0]);//malloc(sizeof(char) * (ft_strlen(split[0]) + 1));
      ret[i][1] = ft_strdup(split[1]);//malloc(sizeof(char) * (ft_strlen(split[1]) + 1));
      //ft_strlcpy(ret[i][0], split[0], (ft_strlen(split[0]) + 1));
      //ft_strlcpy(ret[i][1], split[1], (ft_strlen(split[1]) + 1));
      i++;
   }
   ret[i] = NULL;
   return (ret);

}

char  **add_new_variable(char **arg, char **envp)
{
   int   i;
   int   env_size;
   int   line_size;
   char **new_envp;

   i = 0;
   env_size = tab_len(envp);
   new_envp = malloc(sizeof(char *) * (env_size + 2));
   line_size = ft_strlen(arg[0]) + ft_strlen(arg[1]) + 1;
   while (i < env_size)
   {
      new_envp[i] = ft_strdup(envp[i]);
      i++;
   }
   new_envp[env_size] = malloc(sizeof(char) * (line_size + 2));
   ft_strlcat(new_envp[env_size], arg[0], ft_strlen(arg[0]) + 1); 
   ft_strlcat(new_envp[env_size], "=", ft_strlen(new_envp[env_size]) + 2); 
   ft_strlcat(new_envp[env_size], arg[1], ft_strlen(new_envp[env_size]) + ft_strlen(arg[1]) + 1); 
   new_envp[env_size + 1] = 0;
   envp = new_envp;
   return (envp);
}

char   **ms_export(char **envp, int env_len)
{
   int   i;
   int   j;
   int   flag;
   char *test;
   char ***args;
   char ***env;

   i = 0;
   flag = 0;
   env_len = tab_len(envp);
   test = "LANG=YEAHSHIT USER=YOUSUCK LUCAS=gentil ANTOINE=mechant";
   args = create_args_list(test);
   env = create_env_list(envp, env_len);
   while (args[i])
   {
      j = 0;
      while (env[j])
      {
         if (ft_strncmp(env[j][0], args[i][0], (ft_strlen(env[i][0] + 1))) == 0)
         {
            ft_strlcpy(env[j][1], args[i][1], (ft_strlen(args[i][1]) + 1));
            flag = 1;
         }
         j++;
      }
      if (flag == 0)
         envp = add_new_variable(args[i], envp);
      flag = 0;
      i++;
   }
   return (envp);
}


