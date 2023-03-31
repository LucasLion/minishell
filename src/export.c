/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:12:49 by llion             #+#    #+#             */
/*   Updated: 2023/03/31 15:46:09 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int  parse_arg(char *a, int *status)
{
   int   i;

   i = 0;
   if ((a[0] >= 'a' && a[0] <= 'z') || (a[0] >= 'A' && a[0] <= 'Z') 
         || a[0] == '_')
   {
      while (a[i] && a[i] != '=')
      {
         if (a[i] != ' ')
            i++;
         else
         {
            *status = 1;
            return (ms_error(a, NULL, -5));
         }
      }
      if (a[i] == '=' && i == 0)
      {
         *status = 1;
         return (ms_error(a, NULL, -5));
      }
      else
         return (1);
   }
   else
   {
      *status = 1;
      return (ms_error(a, NULL, -5));
   }
}

char **sort_tab(char **tab, int size)
{
    int i;
	int	j;
	int	min;
    char *tmp;
    char **sorted_tab;

	i = 0;
    
   for (int i = 0; tab[i]; i++)
      printf("%d: %s\n", i, tab[i]);
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
        sorted_tab[i++] = sorted_tab[min];
        sorted_tab[min] = tmp;
    }
    return (sorted_tab);
}

char  *add_double_quotes(char *str)
{
   int   i;
   int   j;
   char  *ret;

   i = 0;
   j = 0;
   ret = ft_calloc(ft_strlen(str) + 3, sizeof(char));
   while (str[i] && str[i] != '=')
      ret[j++] = str[i++];
   if (str[i] == '=')
   {
      i++;
      ret[j++] = '=';
      ret[j++] = '"';
      while (str[i])
         ret[j++] = str[i++];
      ret[j] = '"';
   }
   return (ret);
}

void  display_export(char **envp)
{
   int   i;
   char  **sorted;
   char  *formatted;

   i = 0;
   sorted = sort_tab(envp, ft_tablen(envp));
   for (int i = 0; envp[i]; i++)
      printf("%d: %s\n", i, envp[i]);
   while (sorted[i])
   {
      if (sorted[i][1] == '=' && sorted[i][0] == '_')
         i++;
      else
      {
         formatted = add_double_quotes(sorted[i]);
         printf("declare -x %s\n", formatted);
         free(formatted);
         i++;
      }
   }
}

char *var(char *arg)
{
   int   i;
   int   end;
   char  *var;

   i = 0;
   end = 0;
   while (arg[end] && arg[end] != '=')
      end++;
   if (end == 0 && arg[end] == '=')
      return (NULL);
   var = ft_calloc(end + 1, sizeof(char));
   if (var == NULL)
      return (NULL);
   while (arg[i] && arg[i] != '=')
   {
      var[i] = arg[i];
      i++;
   }
   var[i] = '\0';
   return (var);
}

