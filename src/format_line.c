/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:50:37 by amouly            #+#    #+#             */
/*   Updated: 2023/03/11 13:34:40 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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

char    *format_line(char *line)
{
    t_char *list;
    char *line_formated;
    
    if (verif_line(line))
        return (NULL);
    list = NULL;
    fill_list(line, &list);
    if (!format_list(list))
        return (NULL);
    //free la list
    line_formated = list_to_string(list);
    //free la list
    return (line_formated);
}


void print_input_after_formating(char *line_input)
{
    char *line_formated;
    
    line_formated = format_line(line_input);
    printf("%s\n", line_formated);
    printf("------------------------------\n");
    split_and_print(line_formated);
}
