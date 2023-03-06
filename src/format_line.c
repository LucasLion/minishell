/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:50:37 by amouly            #+#    #+#             */
/*   Updated: 2023/03/06 18:13:47 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// TO DO : le pre formatage fonctionne. Probleme avec les << et >>
// Avec || cela met des espaces partout et separe donc les doubles chevrons.
// avec && ca garde bien les double chevrons maais aussi les triples et ca garde le texte apres et avant

void format_list(t_char *list)
{
    t_char  *temp;
    t_char  *head;
    int     flag;

    temp = list;
    head = list;
    flag = 0;
    while(temp)
    {  
        flag = put_flag(temp->character, flag);
        if (flag  == 0 && temp->previous != NULL && temp->next != NULL) 
        { 
            if (temp->character == '|' && 
                (temp->previous->character != ' ' || temp->next->character != ' '))
            {
                insert_space(temp);
                temp = head;
            }      
            else if (temp->character == '<' &&
                (temp->previous->character != ' ' || temp->next->character != ' ') &&
                (temp->previous->character != '<' && temp->next->character != '<')) 
            //  (temp->previous->character != '<' || temp->next->character != '<')) 
            {
                insert_space(temp);
                temp = head;
            }     
            else if  (temp->character == '>' && 
                (temp->previous->character != ' ' || temp->next->character != ' ') &&
                (temp->previous->character != '>' && temp->next->character != '>')) 
            //  (temp->previous->character != '>' || temp->next->character != '>'))       
            {
                insert_space(temp);
                temp = head;
            }
            else 
                temp = temp->next;
        }
        else
            temp = temp->next; 
    }
}

int length_list(t_char *list)
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




char    *list_to_string(t_char *list)
{
    int len;
    char *ret;
    int i;
    t_char *temp;

    temp = list;
    len = length_list(list);
    i = 0;
    ret = malloc(sizeof(char) * (len + 1));
    if (ret == NULL)
        return (NULL); 
    while (i < len)
    {
        ret[i] = temp->character;
        i++;
        temp = temp->next;
    }
    ret[i] = '\0';
    return (ret);
}

void format_line(char *line_input)
{
    t_char *list;
    char *line_formated;
    
    if (verif_line(line_input))
        return ;
    list = NULL;
    fill_list(line_input, &list);
    format_list(list);
    line_formated = list_to_string(list);
    printf("%s\n", line_formated);
    printf("------------------------------\n");
    split_and_print(line_formated);
}
