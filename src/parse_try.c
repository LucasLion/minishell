/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_try.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:03:31 by event             #+#    #+#             */
/*   Updated: 2023/03/11 12:07:20 by amouly           ###   ########.fr       */
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


void try_handle_chevrons(char **tab, int index, t_command *new)
{
    int fd;

    fd = 0;
    if (tab[index][0] == '<')
    {
        if (tab[index][1] == '<')
        {
            fill_list_string(tab[index + 1], &(new->delimiters));  
            new->delimiter = 1;
        } 
        else
            { //input redirige
                fill_list_string(tab[index + 1], &(new->input));
                new->redir_input = 1;
            }   
            // printf("Input redirected from file : %s\n", tab[index + 1]);
    }
    else
    {
        if (tab[index][1] == '>')
        //printf("Output redirected and APPENDED to file : %s\n", tab[index + 1]);
        //output redirige avec append
        {
            fill_list_string_append(tab[index + 1], &(new->output));
            new->redir_output = 1;
        }
            
        else
        //printf("Output redirected to file : %s\n", tab[index + 1]);
        //output redirige
        {
            fill_list_string(tab[index + 1], &(new->output));
            new->redir_output = 1;
        }
    }
}


void try_find_command_until_pipe(char **tab, int *i, int *cmd,t_command *new)
{
    int j;
    
    j = 0;
    if (tab[*i][0] == '<' || tab[*i][0] == '>')
    {
        try_handle_chevrons(tab, *i, new);
        (*i)++;
    }
    else 
    {
        if (*cmd == 0)
        // la commande
        {
            new->command = malloc(sizeof(char) * (ft_strlen(tab[*i]) + 1));
            //clean si null
            printf("Voici la commande : %s\n", tab[*i]);
            printf("et le nombre de lettre de la cmd : %zu\n", ft_strlen(tab[*i]));
            while (tab[*i][j])
            {
                tab[*i][j] = new->command[j];
                j++;
            }
            new->command[j] = '\0';
            printf("commande dans le node : %s", new->command);
            *cmd = 1;
        }
        else 
        // arg ou option
        {
            fill_list_string(tab[*i], &(new->options_and_args)); 
            new->option_arg = 1;
        }
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
int fill_list_command(char **tab, int *i, t_command **list, int *count)
{
    int         cmd;
    t_command   *new;

    cmd = 0;
    new = malloc(sizeof(t_command));
    if (new == NULL)
        return (0);
    init_struct_command(new);
    while(tab[*i] && (tab[*i][0] != '|' || tab[*i][1] != '\0'))
        {
            try_find_command_until_pipe(tab, i, &cmd, new);
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






void    parse_try_input(char *input)
{
    char    **tab;
    int     i;
    int     count;
    t_command   *list_of_command;
    //t_string *list_of_srting;
    
    
    i = 0;
    tab = ft_split_ms(format_line(input));
    count = 0;
    list_of_command = NULL;
    //list_of_srting = NULL;
    //init_struct_command(list_of_command);
    while(tab[i])
    {
        count++;
        fill_list_command(tab, &i, &list_of_command, &count);
        //fill_list_string_append(tab[i], &list_of_srting);
        //i++;
    }
    print_list_command_from_head(list_of_command);
   // print_list_string_from_head(list_of_srting);
}