/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:12:49 by llion             #+#    #+#             */
/*   Updated: 2023/03/30 16:44:33 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int   check_if_variable(char *arg, char **envp)
{
   int   i;
   char  *var_arg;
   char  *var_env;
   int   flag;

   i = 0;
   flag = 0;
   var_arg = var(arg);
   while (envp[i])
   {
      var_env = var(envp[i]);
      if (ft_strncmp(var_env, var_arg, ft_strlen(var_arg) + 1) == 0)
         flag = 1;
      i++;
      free(var_env);
   }
   free(var_arg);
   return (flag);
}

char  **add_new_variable(char *arg, char **envp)
{
   int   i;
   int   env_size;
   int   line_size;
   char  **nenvp;

   i = 0;
   env_size = ft_tablen(envp);
   nenvp = allocate_tab(env_size);
   loop(i, env_size, nenvp, envp);
   if (val(arg) == 0)
   {
      line_size = (int)ft_strlen(var(arg)) + 1;
      nenvp[i] = ft_calloc(line_size + 1, sizeof(char)); 
      ft_strlcat(nenvp[i], var(arg), ft_strlen(var(arg)) + 1); 
   }
   else
   {
      line_size = (int)ft_strlen(var(arg)) + (int)ft_strlen(val(arg)) + 2;
      nenvp[i] = allocate(line_size, nenvp);
	  cat(nenvp[i], arg);
   }
   free_tab2(envp);
   return (nenvp);
}

char  **edit_variable(char *arg, char **envp)
{
   int   i;
   char  **nenvp;

   i = 0;
   if (val(arg) != NULL)
   {
	  nenvp = allocate_tab(ft_tablen(envp));
      while (i < ft_tablen(envp) && ft_strncmp(var(envp[i]), var(arg), ft_strlen(var(arg))) != 0)
      {
         nenvp[i] = ft_strdup(envp[i]);
         i++;
      }
      nenvp[i] = allocate(ft_strlen(var(arg)) + ft_strlen(val(arg)) + 2, nenvp);
	  cat(nenvp[i++], arg);
	  while (i < ft_tablen(envp))
	  {
		 nenvp[i] = ft_strdup((envp)[i]);
		 i++;
	  }
      nenvp[i] = 0;
      free_tab2(envp);
      return (nenvp);
   }
   return (envp);
}

int  modifiy_env(char *arg, char ***envp)
{
   int	 flag;

   flag = check_if_variable(arg, *envp);
   if (flag == 0)
	  *envp = add_new_variable(arg, *envp);
   else
   {
	  *envp = edit_variable(arg, *envp);
	  if (*envp == NULL)
		 return (ms_error("export", NULL, errno));
   }
   return (0);
}

int   ms_export(char **argv, char ***envp)
{
   int   i;

   i = 1; 
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
			modifiy_env(argv[i], envp);
         i++;
      }
   }
   return (0);
}
