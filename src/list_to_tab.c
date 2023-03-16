/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 09:45:36 by amouly            #+#    #+#             */
/*   Updated: 2023/03/16 10:22:05 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *copy_string_to_tab(char *string_list, char **envp)
{
    int flag;
    char   *ret;
    char    *temp;
    int i;

    i = 0;
    while(string_list[i])
    {    
        flag = put_flag(string_list[i], flag);
        //if (flag != 2 && string_list[i] == '$')
            //find_and_add environnement
        if (flag == 1 && string_list[i] == '"')
        {
            i++;
            continue;
        }
        else if (flag == 2 && string_list[i] == '\'')
        {
            i++;
            continue;
        }
        else
        {
            temp = sizeof(char);
            temp = string_list[i];
        }
        
    }
}



char **list_to_tab_argv(t_string *list, char **envp)
{
    int len;
    char **ret;
    int i;
    t_string *temp;

    if (list->next == NULL)
        return NULL;
    temp = list->next;
    len = length_list(list);
    i = 0;
    ret = malloc(sizeof(char *) * (len));
    if (ret == NULL)
        return (NULL); 
    while (i < len - 1)
    {
        ret[i] = temp->string;
        i++;
        temp = temp->next;
    }
    ret[i] = 0;
    return (ret);
}

char    *list_to_command(t_string *list)
{
    
}
