/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 14:21:07 by llion             #+#    #+#             */
/*   Updated: 2023/03/07 16:17:29 by llion            ###   ########.fr       */
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
      ret[i][0] = split[0];
      ret[i][1] = split[1];
      free_tab2(split);
      printf("1: %s\n2: %s\n", ret[i][0], ret[i][1]);
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
   printf("len: %d\n", len);
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
      //TODO copier la string du split d'une facon plus juste, ici on ne copie que le pointeur
      ret[i][0] = split[0];
      ret[i][1] = split[1];
      free_tab2(split);
      //printf("1: %s\n2: %s\n", ret[i][0], ret[i][1]);
      i++;
   }
   // TODO results in undefined value;
   ret[i] = NULL;
   return (ret);

}

int   ms_export(char ***args, char ***env, char **envp)
{
   (void)envp;
   int   i;
   int   j;

   i = 0;
   while (args[i])
   {
      j = 0;
      while (env[j])
      {
         //printf("-%s-  -%s-\n", env[j][0], args[i][0]);
         // TODO ne marche que quand ca marche pas
         if (env[j][0] == args[i][0])
            printf("coucou\n");
         j++;
      }
      i++;
   }

   return (0);
}

