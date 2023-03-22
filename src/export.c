/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:12:49 by llion             #+#    #+#             */
/*   Updated: 2023/03/22 10:11:19 by llion            ###   ########.fr       */
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

/*
char  *add_double_quotes(char *str)
{
   int   i;
   int   j;
   char  *ret;

   i = 0;
   j = 0;
   printf("str: %s\n", str);
   ret = ft_calloc(ft_strlen(str) + 3, sizeof(char));
   while (str[i] && str[i] != '=')
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
*/

void  display_export(char **envp)
{
   int   i;
   char  **sorted;
   //char  *formatted;

   i = 0;
   sorted = sort_tab(envp, tab_len(envp));
   while (sorted[i])
   {
      if (sorted[i][1] == '=' && sorted[i][0] == '_')
         i++;
      else
      {
         //formatted = add_double_quotes(sorted[i]);
         printf("declare -x %s\n", sorted[i]);
         //free(formatted);
         i++;
      }
   }
}

char *extract_var(char *arg)
{
   int   i;
   int   end;
   char  *var;

   i = 0;
   end = 0;
   while (arg[end] && arg[end] != '=')
      end++;
   var = ft_calloc(end + 1, sizeof(char));
   while (arg[i] && arg[i] != '=')
   {
      var[i] = arg[i];
      i++;
   }
   var[i] = '\0';
   return (var);
}

char *extract_val(char *arg)
{
   int   i;
   int   j;
   char  *var;

   i = 0;
   j = 0;
   while (arg[i] != '\0' && arg[i] != '=')
      i++;
   var = ft_calloc(ft_strlen(arg) - i + 1, sizeof(char));
   i++;
   if (arg[i] == '\0')
      return (NULL);
   while (arg[i])
   {
      var[j] = arg[i];
      i++;
      j++;
   }
   var[j] = '\0';
   return (var);
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
   }
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
   var_arg = extract_var(arg);
   val_arg = extract_val(arg);
   env_size = tab_len(envp);
   nenvp = ft_calloc((env_size + 2), sizeof(char *));
   while (i < env_size)
   {
      nenvp[i] = ft_strdup(envp[i]);
      i++;
   }
   if (val_arg == NULL)
   {
      line_size = (int)ft_strlen(var_arg) + 1;
      nenvp[i] = ft_calloc(line_size + 1, sizeof(char)); 
      ft_strlcat(nenvp[i], var_arg, ft_strlen(var_arg) + 1); 
   }
   else
   {
      line_size = (int)ft_strlen(var_arg) + (int)ft_strlen(val_arg) + 2;
      nenvp[i] = ft_calloc(line_size + 1, sizeof(char)); 
      ft_strlcat(nenvp[i], var_arg, ft_strlen(var_arg) + 1); 
      ft_strlcat(nenvp[i], "=", ft_strlen(var_arg) + 2); 
      ft_strlcat(nenvp[i], val_arg, ft_strlen(var_arg) + ft_strlen(val_arg) + 2); 
   }
   nenvp[env_size + 1] = 0;
   free_tab2(envp);
   free(var_arg);
   free(val_arg);
   return (nenvp);
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
   env_size = tab_len(envp);
   nenvp = ft_calloc((env_size + 2), sizeof(char *));
   while (i < env_size && ft_strncmp(extract_var(envp[i]), var_arg, ft_strlen(var_arg)) <= 0)
   {
      nenvp[i] = ft_strdup(envp[i]);
      i++;
   }
   // TODO la variable se rajoute mais ecrase la suivante et la taille du tableau n'augmente pas
   nenvp[i] = ft_calloc(ft_strlen(var_arg) + ft_strlen(extract_var(envp[i])) + 2, sizeof(char));
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

char   **ms_export(char **argv, char **envp, int env_len)
{
   (void)env_len;
   int   flag;
   int   i;

   i = 1; 
   flag = 0;
   if (tab_len(argv) == 1)
      display_export(envp);
   else
   {
      while (argv[i])
      {
         flag = check_if_variable(argv[i], envp);
         if (flag == 0)
            envp = add_new_variable(argv[i], envp);
         else
            envp = edit_variable(argv[i], envp);
         i++;
      }
      flag = 0;
      i++;
   }
   return (envp);
}
