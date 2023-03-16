/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 14:21:07 by llion             #+#    #+#             */
/*   Updated: 2023/03/16 14:12:46 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
      ret = ft_calloc(len + 1, sizeof(char **));
      if (ret == NULL)
         return (NULL);
   }
   else
      return (NULL);
   while (i < len)
   {
      ret[i] = ft_calloc(2, sizeof(char *));
      split = ft_split(tab[i], '=');
      ret[i][0] = ft_calloc(ft_strlen(split[0]), sizeof(char));
      ret[i][1] = ft_calloc(ft_strlen(split[1]), sizeof(char));
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
      ret = ft_calloc(env_len + 2, sizeof(char **));
      if (ret == NULL)
         return (NULL);
   }
   else
      return (NULL);
   ret[env_len + 1] = NULL;
   i = 0;

   while (i < env_len)
   {
      ret[i] = ft_calloc(2, sizeof(char *));
      split = ft_split(envp[i], '=');
      ret[i][0] = ft_strdup(split[0]);
      ret[i][1] = ft_strdup(split[1]);
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
   new_envp = ft_calloc((env_size + 2), sizeof(char *));
   line_size = ft_strlen(arg[0]) + ft_strlen(arg[1]) + 1;
   new_envp[env_size + 1] = 0;
   while (i < env_size && ft_strncmp(envp[i], arg[0], ft_strlen(arg[0])) < 0)
   {
      new_envp[i] = ft_strdup(envp[i]);
      i++;
   }
   new_envp[i] = ft_calloc(line_size + 2, sizeof(char)); 
   ft_strlcpy(new_envp[i], arg[0], ft_strlen(arg[0]) + 1); 
   ft_strlcat(new_envp[i], "=", ft_strlen(new_envp[i]) + 2); 
   ft_strlcat(new_envp[i], arg[1], ft_strlen(new_envp[i]) + ft_strlen(arg[1]) + 1); 
   i++;
   while (i < env_size)
   {
      new_envp[i] = ft_strdup(envp[i]);
      i++;
   }
   return (new_envp);
}

void  edit_variable(char **envp, char *var, char *val, int j)
{
   envp[j] = ft_calloc(ft_strlen(envp[j]) + ft_strlen(val) + 1, sizeof(char));
   ft_strlcat(envp[j], var, ft_strlen(var) + 1); 
   ft_strlcat(envp[j], "=", ft_strlen(envp[j]) + 2); 
   ft_strlcat(envp[j], val, ft_strlen(envp[j]) + ft_strlen(val) + 1); 
}

char   **ms_export(char **envp, int env_len)
{
   int   i;
   int   j;
   int   k;
   int   flag;
   char *string;
   char ***args;
   char ***env;

   i = 0;
   k = 0;
   flag = 0;
   env_len = tab_len(envp);
   string = "LANG=YEAHSHIT USER=YOUSUCK LUCAS=gentil ANTOINE=mechant";
   //string = "";
   args = create_args_list(string);
   env = create_env_list(envp, env_len);
   if (ft_strlen(string) == 0)
      while (envp[k])
         printf("declare -x %s\n", envp[k++]);
   else if (args)
   {
      while (args[i])
      {
         j = 0;
         while (env[j])
         {
            if (ft_strncmp(env[j][0], args[i][0], (ft_strlen(args[i][0] + 1))) == 0)
            {
               edit_variable(envp, args[i][0], args[i][1], j);
               flag = 1;
            }
            j++;
         }
         if (flag == 0)
            envp = add_new_variable(args[i], envp);
         flag = 0;
         i++;
      }
   }
   return (envp);
}


