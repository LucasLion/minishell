/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:03:31 by event             #+#    #+#             */
/*   Updated: 2023/03/11 14:45:32 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_chevrons(char **tab, int index, t_command *new)
{
    if (tab[index][0] == '<')
    {
        if (tab[index][1] == '<')
        {
            fill_list_string(tab[index + 1], &(new->delimiters));  
            new->delimiter = 1;
        } 
        else
        {
            fill_list_string(tab[index + 1], &(new->input));
            new->redir_input = 1;
        }   
    }
    else
    {
        if (tab[index][1] == '>')
            fill_list_string_append(tab[index + 1], &(new->output));
        else
            fill_list_string(tab[index + 1], &(new->output));
        new->redir_output = 1;
    }
}

void find_command_until_pipe(char **tab, int *i,t_command *new)
{
    int j;
    
    j = 0;
    if (tab[*i][0] == '<' || tab[*i][0] == '>')
    {
        handle_chevrons(tab, *i, new);
        (*i)++;
    }
    else
        fill_list_string(tab[*i], &(new->command));
}


int fill_list_command(char **tab, int *i, t_command **list, int *count)
{
    t_command   *new;

    new = malloc(sizeof(t_command));
    if (new == NULL)
        return (0);
    init_struct_command(new);
    while(tab[*i] && (tab[*i][0] != '|' || tab[*i][1] != '\0'))
        {
            find_command_until_pipe(tab, i, new);
            (*i)++;
        }
        if (tab[*i] && (tab[*i][0] == '|' && tab[*i][1] == '\0'))
        {    
            new->pipe_after = 1;
            (*i)++;
        }
    new->order = *count;
    new->next = NULL;
    if (!lstadd_back_list_command(list, new ))
        return (0);
    return (1);
}

void    parse_input(char *input)
{
    char    **tab;
    int     i;
    int     count;
    t_command   *list_of_command;
    
    i = 0;
    tab = ft_split_ms(format_line(input));
    count = 0;
    list_of_command = NULL;
    while(tab[i])
    {
        count++;
        fill_list_command(tab, &i, &list_of_command, &count);
    }
    print_list_command_from_head(list_of_command);
}
