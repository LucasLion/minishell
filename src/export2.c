/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:12:49 by llion             #+#    #+#             */
/*   Updated: 2023/03/29 15:23:04 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *extract_val(char *arg)
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

int   check_if_variable(char *arg, char **envp)
{
   int   i;
   char  *var_arg;
   char  *val_arg;
   char  *var_env;
   char  *val_env;
   int   flag;

   i = 0;
   flag = 0;
   var_arg = extract_var(arg);
   val_arg = extract_val(arg);
   while (envp[i])
   {
      var_env = extract_var(envp[i]);
      val_env = extract_val(envp[i]);
      if (ft_strncmp(var_env, var_arg, ft_strlen(var_arg) + 1) == 0)
         flag = 1;
      i++;
      free(var_env);
      free(val_env);
   }
   free(val_arg);
   free(var_arg);
   return (flag);
}

char  **add_new_variable(char *arg, char **envp)
{
   int   i;
   int   env_size;
   int   line_size;
   char  **nenvp;
   char  *var_arg;
   char  *val_arg;

   i = 0;
   env_size = ft_tablen(envp);
   nenvp = ft_calloc((env_size + 2), sizeof(char *));
   if (nenvp == NULL)
      return (NULL);
   while (i < env_size)
   {
      nenvp[i] = ft_strdup((envp)[i]);
      i++;
   }
   var_arg = extract_var(arg);
   val_arg = extract_val(arg);
   if (val_arg == 0)
   {
      line_size = (int)ft_strlen(var_arg) + 1;
      nenvp[i] = ft_calloc(line_size + 1, sizeof(char)); 
      ft_strlcat(nenvp[i], var_arg, ft_strlen(var_arg) + 1); 
   }
   else
   {
      line_size = (int)ft_strlen(var_arg) + (int)ft_strlen(val_arg) + 2;
      nenvp[i] = ft_calloc(line_size + 1, sizeof(char)); 
      if (nenvp[i] == NULL)
      {
         free_tab2(nenvp);
         return (NULL);
      }
      ft_strlcat(nenvp[i], var_arg, ft_strlen(var_arg) + 1); 
      ft_strlcat(nenvp[i], "=", ft_strlen(var_arg) + 2); 
      ft_strlcat(nenvp[i], val_arg, ft_strlen(var_arg) + ft_strlen(val_arg) + 2); 
   }
   free_tab2(envp);
   free(var_arg);
   free(val_arg);
   return (nenvp) ;
}

char  **edit_variable(char *arg, char **envp)
{
   int   i;
   int   env_size;
   char  **nenvp;
   char  *var_arg;
   char  *val_arg;

   i = 0;
   var_arg = extract_var(arg);
   val_arg = extract_val(arg);
   if (val_arg != NULL)
   {
      env_size = ft_tablen(envp);
      nenvp = ft_calloc((env_size + 2), sizeof(char *));
      if (nenvp == NULL)
         return (NULL);
      while (i < env_size && ft_strncmp(extract_var(envp[i]), var_arg, ft_strlen(var_arg)) != 0)
      {
         nenvp[i] = ft_strdup(envp[i]);
         i++;
      }
      nenvp[i] = ft_calloc(ft_strlen(var_arg) + ft_strlen(arg) + 2, sizeof(char));
      if (nenvp[i] == NULL)
      {
         free_tab2(nenvp);
         return (NULL);
      }
      ft_strlcat(nenvp[i], var_arg, ft_strlen(var_arg) + 1); 
      ft_strlcat(nenvp[i], "=", ft_strlen(var_arg) + 2); 
      ft_strlcat(nenvp[i], val_arg, ft_strlen(var_arg) + ft_strlen(val_arg) + 2); 
      i++;
      while (i < env_size)
      {
         nenvp[i] = ft_strdup(envp[i]);
         i++;
      }
      nenvp[i] = 0;
      free_tab2(envp);
      return (nenvp);
   }
   else
      return (envp);
}

int   ms_export(char **argv, char ***envp)
{
   int   flag;
   int   i;

   i = 1; 
   flag = 0;
   if (ft_tablen(argv) == 1)
      display_export(*envp);
   else
   {
      while (argv[i])
      {
        if (!parse_arg(argv[i]))
        {
            i++;
            continue ;
        }
         if (ft_strlen(argv[i]) > 0 && !(ft_strlen(argv[i]) == 1 && argv[i][0] == '='))
         {
            flag = check_if_variable(argv[i], *envp);
            if (flag == 0)
               *envp = add_new_variable(argv[i], *envp);
            else
            {
               *envp = edit_variable(argv[i], *envp);
               if (*envp == NULL)
                  return (ms_error("export", NULL, errno));
            }
         }
         i++;
      }
      flag = 0;
      i++;
   }
   return (0);
}
