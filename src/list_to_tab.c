/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 09:45:36 by amouly            #+#    #+#             */
/*   Updated: 2023/03/18 11:23:22 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int length_list_string(t_string *list)
{
    int i;

    i = 0;
	if (list)
	{
		i++;
		while (list->next != NULL)
		{
			list = list->next;
			i++;
		}
		return (i);
	}
	else
		return (0);
}

int size_var(char *string_list, int *i)
{
    int count;

    count = 0;
    while (string_list[*i] && string_list[*i] != ' ' 
        && string_list[*i] != '$' && string_list[*i] != '\'' 
        && string_list[*i] != '"' )
    {
        count++;
        (*i)++;
    }
    return(count);
}



int count_size_env(char *string_list, int *i, char **envp)
{
    int count;
    int debut;
    int b;

    
    (*i)++;
    debut = (*i);
    count = size_var(string_list, i);
    b = 0;
    while(envp[b])
    {
        if (!ft_strncmp(envp[b], &string_list[debut], (size_t) count) && envp[b][count] == '=')
        {
            return ((int)(ft_strlen(envp[b] + count + 1)));
        }
        b++;
    }
    return (0) ;
    
}

void copy_env_var(char *string_list, int *i, char **envp, char *ret, int *j)
{
    int count;
    int debut;
    int b;

    (*i)++;
    debut = (*i);
    count = size_var(string_list, i);
    b = 0;
    while(envp[b])
    {
        if (!ft_strncmp(envp[b], &string_list[debut], (size_t) count) && envp[b][count] == '=')
        {
           count ++;
           while (envp[b][count])
           {
                ret[*j] = envp[b][count];
                (*j)++;
                count++;
           }
        }
        b++;
    }
}


int count_char(char *string_list, char **envp)
{
    int flag;
    int flag1;
    int count;
    int i;
    
    i = 0;
    flag = 0;
    count = 0;
    while(string_list[i])
    {    
        flag1 = put_flag(string_list[i], flag);
        if (string_list[i] == '$' && flag1 != 2)
        { 
            if (string_list[i+1] == '\0' || string_list[i+1] == ' ' || string_list[i+1] == '$')
            {
                count++;
                i++;
            } 
            else
                count += count_size_env(string_list, &i, envp);
        }
        else if (string_list[i] == '"' && (flag1 == 1 || (flag1 == 0 && flag == 1) ))
            i++;
        else if (string_list[i] == '\'' && (flag1 == 2 || (flag1 == 0 && flag == 2) ))
            i++;
        else
        {
            count++;
            i++;
        }
        flag = flag1;
    }
    return (count);
}

char *copy_string(char *string_list, char **envp)
{
    int flag;
    int flag1;
    char   *ret;
    int i;
    int j;
    
    i = 0;
    j = 0;
    flag = 0;
    ret = ft_calloc(count_char(string_list, envp) + 1, sizeof(char));
    while(string_list[i])
    {    
        flag1 = put_flag(string_list[i], flag);
        if (string_list[i] == '$' && flag1 != 2 && string_list[i+1] != '\0' 
            && string_list[i+1] != ' ' && string_list[i+1] != '$' )
                copy_env_var(string_list, &i, envp, ret, &j);
        else if (string_list[i] == '"' && (flag1 == 1 || (flag1 == 0 && flag == 1)))
            i++;
        else if (string_list[i] == '\'' && (flag1 == 2 || (flag1 == 0 && flag == 2)))
            i++;
        else
        {
            ret[j] = string_list[i];
            i++;
            j++;
        }
        flag = flag1;
    }
    return (ret);
}



char **list_to_tab(t_string *list, char **envp)
{
    int len;
    char **ret;
    int i;
    t_string *temp;

    //if (list->next == NULL)
    //    return NULL;
    temp = list;
    len = length_list_string(list);
    i = 0;
    ret = malloc(sizeof(char *) * (len + 1));
    if (ret == NULL)
        return (NULL); 
    while (i < len)
    {
        ret[i] = copy_string(temp->string, envp);
        i++;
        temp = temp->next;
    }
    ret[i] = 0;
    return (ret);
}
