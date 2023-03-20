/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 14:21:07 by llion             #+#    #+#             */
/*   Updated: 2023/03/20 17:35:18 by llion            ###   ########.fr       */
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

char **sort_tab(char **tab, int size)
{
    int i;
	int	j;
	int	min;
    char *tmp;
    char **sorted_tab;

	i = 0;
    sorted_tab = copy_tab(tab);
    while (i < size - 1)
	{
		j = i + 1;
        min = i;
        while  (j < size)
		{
            if (ft_strncmp(sorted_tab[j], sorted_tab[min], ft_strlen(sorted_tab[j])) < 0)
            {
                min = j;
            }
			j++;
        }
        tmp = sorted_tab[i];
        sorted_tab[i] = sorted_tab[min];
        sorted_tab[min] = tmp;
		i++;
    }
    return (sorted_tab);
}

char  	***create_args_list(char **argv)
{
   int   i;
   int   len;
   char  ***ret;
   char  **split;

   if (argv == NULL)
      return (NULL);
   i = 1;
   len = tab_len(argv);
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
      split = ft_split(argv[i], '=');
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
   line_size = (int)ft_strlen(arg[0]) + (int)ft_strlen(arg[1]) + 1;
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
   free_tab2(envp);
   return (new_envp);
}

void  edit_variable(char **envp, char *var, char *val, int j)
{
   envp[j] = ft_calloc(ft_strlen(envp[j]) + ft_strlen(val) + 1, sizeof(char));
   ft_strlcat(envp[j], var, ft_strlen(var) + 1); 
   ft_strlcat(envp[j], "=", ft_strlen(envp[j]) + 2); 
   ft_strlcat(envp[j], val, ft_strlen(envp[j]) + ft_strlen(val) + 1); 
}

char  *add_double_quotes(char *str)
{
   int   i;
   int   j;
   char *ret;

   i = 0;
   j = 0;
   ret = ft_calloc(ft_strlen(str) + 3, sizeof(char));
   while (str[i] != '=')
   {
      ret[j] = str[i];
      i++;
      j++;
   }
   i++;
   ret[j] = '=';
   j++;
   ret[j] = '"';
   j++;
   while (str[i])
   {
      ret[j] = str[i];
      i++;
      j++;
   }
   ret[j] = '"';
   return (ret);
}

char   **ms_export(char **argv, char **envp, int env_len)
{
   int   i;
   int   j;
   int   k;
   int   flag;
   char ***args;
   char ***env;
   char  **sorted;
   char *formatted;

   i = 1;
   k = 0;
   flag = 0;
   args = create_args_list(argv);
   env = create_env_list(envp, env_len);
   if (tab_len(argv) == 1)
   {
      sorted = sort_tab(envp, tab_len(envp));
      while (sorted[k])
      {
         if (sorted[k][1] == '=' && sorted[k][0] == '_')
            k++;
         else
         {
            formatted = add_double_quotes(sorted[k]);
            printf("declare -x %s\n", formatted);
            k++;
         }
      }
   }
   else
   {
      // TODO probleme avec les valeurs de variable vide
      while (args[i])
      {
         j = 0;
         while (env[j])
         {
            if (ft_strncmp(env[j][0], args[i][0], (ft_strlen(args[i][0]))) == 0)
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
   free_tab3(args);
   free_tab3(env);
   return (envp);
}


