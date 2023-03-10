/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_try.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:03:31 by event             #+#    #+#             */
/*   Updated: 2023/03/10 16:16:28 by amouly           ###   ########.fr       */
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
}

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
}*/


void try_handle_chevrons(char **tab, int index, t_command *list)
{
    int fd;

    fd = 0;
    if (tab[index][0] == '<')
    {
        if (tab[index][1] == '<')
        {
            fill_list_string(tab[index + 1], &(list->delimiters));  
            list->delimiter = 1;
        } 
        else
            { //input redirige
                fd = open(tab[index + 1], O_RDONLY);
                list->fd_input = fd;
            }   
            // printf("Input redirected from file : %s\n", tab[index + 1]);
    }
    else
    {
        if (tab[index][1] == '>')
        //printf("Output redirected and APPENDED to file : %s\n", tab[index + 1]);
        //output redirige avec append
        {
            fd = open(tab[index + 1], O_WRONLY, O_APPEND);
            list->fd_output = fd;
        }
            
        else
        //printf("Output redirected to file : %s\n", tab[index + 1]);
        //output redirige
        {
            fd = open(tab[index + 1], O_WRONLY, O_TRUNC);
            list->fd_output = fd;
        }
    }
}


void try_find_command_until_pipe(char **tab, int *i, int *cmd,t_command *list)
{
    int j;
    
    j = 0;
    if (tab[*i][0] == '<' || tab[*i][0] == '>')
    {
        try_handle_chevrons(tab, *i, list);
        (*i)++;
    }
    else 
    {
        if (*cmd == 0)
        // la commande
        {
            list->command = malloc(sizeof(char) * (ft_strlen(tab[*i]) + 1));
            //clean si null
            while (tab[*i][j])
            {
                tab[*i][j] = list->command[j];
                j++;
            }
            list->command[j] = '\0';
            *cmd = 1;
        }
        else 
        // arg ou option
            fill_list_string(tab[*i], &(list->options_and_args)); 
    }
}


/*void    parse_input(char *input)
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
}*/


void    parse_try_input(char *input)
{
    char    **tab;
    int     i;
    int     cmd;
    int     count;
    t_command   *list_of_command;
    
    
    i = 0;
    tab = ft_split_ms(format_line(input));
    count = 0;
    list_of_command = NULL;
    
    while(tab[i])
    {
        
        cmd = 0;
        count ++;
        t_command   *new;
        new = malloc(sizeof(t_command));
            // faire si c'est nul
        while(tab[i] && (tab[i][0] != '|' || tab[i][1] != '\0'))
        {
            try_find_command_until_pipe(tab, &i, &cmd, new);
            i++;
        }
        if (tab[i] && (tab[i][0] == '|' && tab[i][1] == '\0'))
        {    
            list_of_command->pipe_after = 1;
            i++;
        }
        list_of_command->order = count;
        list_of_command->next = NULL;
        if (!lstadd_back_list_command(&list_of_command, new ))
            return ;
    // cleaan la liste si il y a un souci
    }
}