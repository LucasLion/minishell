/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:23:30 by amouly            #+#    #+#             */
/*   Updated: 2023/03/21 14:47:25 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int find_input(t_string *input)
{
    t_string *temp;
    int fd;
    
    temp = input;
    
    while (temp)
    {
        fd = open(temp->string, O_RDONLY);
        temp = temp->next;
    }
    return (fd);
}

int find_output(t_string *output)
{
    t_string *temp;
    int fd;
    
    temp = output;
    while (temp)
    {
        if (temp->append == 1)
            fd = open(temp->string, O_WRONLY | O_CREAT | O_APPEND);
        else
            fd = open(temp->string, O_WRONLY | O_CREAT | O_TRUNC);
        temp = temp->next;
    }
    return (fd);
}

void    init_fd(t_pipe *pipe_info, t_command *list)
{
    
    if (list->input == NULL)
        pipe_info->fd_input = STDIN_FILENO ;
    else
    {
        pipe_info->fd_input = find_input(list->input);
        //if (fd_input == -1)
        // gerer l'erreur    
    }
    if (list->output == NULL)
        pipe_info->fd_output = STDOUT_FILENO;
     else
    {
        pipe_info->fd_output = find_output(list->output);
        //if (fd_output == -1)
        // gerer l'erreur  
    }
}
