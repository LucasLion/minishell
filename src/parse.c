/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:03:31 by event             #+#    #+#             */
/*   Updated: 2023/03/10 14:46:21 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*int count_nb_of_pipes(char **tab, t_number **list)
{
    int i;
    int nb_of_pipes;
    t_number **temp;
    
    temp = list;
    i = 0;
    nb_of_pipes = 0;
    while(tab[i])
    {
        if (tab[i][0] == '|' && tab[i][1] == '\0')
        {
            nb_of_pipes++;
            fill_list_int(i, temp);   
        }   
        i++;
    }
    return (nb_of_pipes);
}*/

int count_nb_of_pipes(char **tab)
{
    int i;
    int nb_of_pipes;
    
    i = 0;
    nb_of_pipes = 0;
    while(tab[i])
    {
        if (tab[i][0] == '|' && tab[i][1] == '\0')
            nb_of_pipes++;    
        i++;
    }
    return (nb_of_pipes);
}


void handle_chevrons(char **tab, int index)
{
    if (tab[index][0] == '<')
    {
        if (tab[index][1] == '<')
            printf("Il y a un delimiteur qui est : %s\n", tab[index + 1]);
        else
            printf("Input redirected from file : %s\n", tab[index + 1]);
    }
    else
    {
        if (tab[index][1] == '>')
            printf("Output redirected and APPENDED to file : %s\n", tab[index + 1]);
        else
            printf("Output redirected to file : %s\n", tab[index + 1]);
    }
}


void find_command_until_pipe(char **tab, int *i, int *cmd, int *arg)
{
    if (tab[*i][0] == '<' || tab[*i][0] == '>')
    {
        handle_chevrons(tab, *i);
        (*i)++;
    }
    else 
    {
        if (*cmd == 0)
        {
            printf("la commande est : %s\n", tab[*i]);
            *cmd = 1;
        }
        else 
            printf("arg ou option num %d : %s\n", (*arg)++, tab[*i]); 
    }
}


void    parse_input(char *input)
{
    char    **tab;
    int     i;
    int     pipe;
    int     cmd;
    int     arg;
    
    i = 0;
    pipe = 0;
    tab = ft_split_ms(format_line(input));

    
    while(tab[i])
    {
        cmd = 0;
        arg = 1;
        while(tab[i] && (tab[i][0] != '|' || tab[i][1] != '\0'))
        {
            find_command_until_pipe(tab, &i, &cmd, &arg);
            i++;
        }
        if (tab[i] && (tab[i][0] == '|' && tab[i][1] == '\0'))
        {    
            printf("Pipe num %d\n", ++pipe);
            i++;
        }
    }
}

