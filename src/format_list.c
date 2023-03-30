/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:50:37 by amouly            #+#    #+#             */
/*   Updated: 2023/03/30 13:40:43 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


int add_space_before (t_char *node)
{
    if (node->previous!= NULL)
    {
        if (!insert_space_node(node->previous, node))
            return (0);
    }
    return (1);
}

int only_space_left(t_char *node)
{
    t_char *temp;

    temp = node;
    if (temp == NULL)
        return (1);
    while (temp)
    {
        if (temp->character != ' ' && temp->character != '\t' )
            return (0);
        temp = temp->next;
    }
    return (1);
    
}


int format_pipe(t_char *node)
{
    if (node->character == '|') 
    {
        if (only_space_left(node->next))
        {
            printf("Syntax error, don't finish with a pipe\n");
               return (0);
        }
        if (node->next->character == '|')
        {
            printf("Syntax error, more than one pipe together\n");
                return (0);
        }
        if (!insert_space_node(node, node->next))
            return (0);
    } 
    return (1);
}

int format_chevron_inf(t_char *node)
{
    if (node->character == '<' && node->next != NULL) 
    {
        if (node->next->character == '<')
        {
            if  (node->next->next != NULL 
                && node->next->next->character == '<')
            {
                printf("Syntax error, more than 2 chevrons\n");
                return (0) ;
            }
            else 
            {
                if (!insert_space_node(node->next, node->next->next))
                    return (0);
                else
                    return (2);
            }
        }
        else 
        {
            if (!insert_space_node(node, node->next))
                return (0);
        }        
    }
    return (1);
}

int format_chevron_sup(t_char *node)
{
    if (node->character == '>' && node->next != NULL) 
    {
        if (node->next->character == '>')
        {
            if  (node->next->next != NULL 
                && node->next->next->character == '>')
            {
                printf("Syntax error, more than 2 chevrons\n");
                return (0) ;
            }
            else 
            {
                if (!insert_space_node(node->next, node->next->next))
                    return (0);
                else
                    return (2);
            }
        }
        else 
        {
            if (!insert_space_node(node, node->next))
                return (0);
        }        
    }
    return (1);
}

int format_list(t_char *list)
{
    t_char  *temp;
    int     flag;

    temp = list;
    flag = 0;
    while(temp)
    {  
        flag = put_flag(temp->character, flag);
        if (flag == 0 && (temp->character == '|' ||
            temp->character == '>' || temp->character == '<'))
        {
            if (!add_space_before(temp) || !format_pipe(temp) || 
            !format_chevron_inf(temp) || !format_chevron_sup (temp))
                return (0);
            if (format_chevron_inf(temp) == 2)
                temp = temp->next;
            if (format_chevron_sup(temp) == 2)
                temp = temp->next;
        }
        temp = temp->next;
    }
    return (1);
}
