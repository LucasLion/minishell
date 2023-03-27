/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 09:45:36 by amouly            #+#    #+#             */
/*   Updated: 2023/03/27 18:42:20 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
    // HANDLE ERROR
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



int count_size_env(char *string_list, int *i, char **envp, int status)
{
    int count;
    int debut;
    int b;

    
    (*i)++;
    if (string_list[*i] == '?')
        return (ft_strlen(ft_itoa(status)));
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
    // HANDLE ERROR
    return (0) ;
    
}
// A MODIFIER

void last_error(char *ret, int *j, int status)
{
    char *err_itoa;
    //int len;
    int b;
    
    err_itoa = ft_itoa(status);
    //len = ft_strlen(err_itoa);
    b = 0;
    while(err_itoa[b])
    {
        ret[*j] = err_itoa[b];
        (*j)++;
        b++;
    }
    
}

void copy_env_var(char *string_list, char **envp, int status, t_copy_string *cs)
{
    int count;
    int debut;
    int b;

    (cs->i)++;
    if (string_list[cs->i] == '?')
    {
        last_error(cs->ret, &(cs->j), status);
        (cs->i)++;
    }
    else
    {
        debut = (cs->i);
        count = size_var(string_list, &(cs->i));
        b = 0;
        while(envp[b])
        {
            if (!ft_strncmp(envp[b], &string_list[debut], (size_t) count) && envp[b][count] == '=')
            {
            count ++;
            while (envp[b][count])
            {
                    cs->ret[cs->j] = envp[b][count];
                    (cs->j)++;
                    count++;
            }
            }
            b++;
        }
    }
}


int count_char(char *string_list, char **envp, int status)
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
            if (string_list[i + 1] == '\0' || string_list[i + 1] == ' ' || string_list[i + 1] == '$')
            {
                count++;
                i++;
            } 
            else
                count += count_size_env(string_list, &i, envp, status);
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


char *copy_string(char *string_list, char **envp, int status)
{
    t_copy_string cs;
    
    //i = 0;
    //j = 0;
    //flag = 0;
    //ret = ft_calloc(count_char(string_list, envp) + 1, sizeof(char));
    //if (ret == NULL)
    //    return (NULL);
    //while(string_list[i])
    cs.i = 0;
    cs.j = 0;
    cs.flag = 0;
    cs.ret = ft_calloc(count_char(string_list, envp, status) + 1, sizeof(char));
    while(string_list[cs.i])
    {    
        cs.flag1 = put_flag(string_list[cs.i], cs.flag);
        if (string_list[cs.i] == '$' && cs.flag1 != 2 && string_list[cs.i+1] != '\0' 
            && string_list[cs.i+1] != ' ' && string_list[cs.i+1] != '$' )
                    copy_env_var(string_list, envp, status, &cs );
        else if (string_list[cs.i] == '"' && (cs.flag1 == 1 || (cs.flag1 == 0 && cs.flag == 1)))
            cs.i++;
        else if (string_list[cs.i] == '\'' && (cs.flag1 == 2 || (cs.flag1 == 0 && cs.flag == 2)))
            cs.i++;
        else
        {
            cs.ret[cs.j] = string_list[cs.i];
            cs.i++;
            cs.j++;
        }
        cs.flag = cs.flag1;
    }
    return (cs.ret);
}



char **list_to_tab(t_command *list, char **envp, int status )
{
    int len;
    char **ret;
    int i;
    t_string *tmp;

    tmp = list;
    len = length_list_string(list);
    //temp = list->command;
    //len = length_list_string(temp);
    i = 0;
    ret = malloc(sizeof(char *) * (len + 1));
    // HANDLE ERROR
    if (ret == NULL)
        return (NULL); 
    while (i < len)
    {
        ret[i] = copy_string(tmp->string, envp);
        //ret[i] = copy_string(temp->string, envp, status);
        i++;
        tmp = tmp->next;
    }
    ret[i] = 0;
    return (ret);
}
