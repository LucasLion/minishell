/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:23:30 by amouly            #+#    #+#             */
/*   Updated: 2023/03/22 08:59:46 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int handle_del(t_string *list, t_pipe *pipe_info)
{
    (void) (pipe_info);
    char *input;
    int fd_ret;
    
    fd_ret = 0;
    input = readline(">");
    //close(fd_del[0])
    while (ft_strncmp(list->string, input, ft_strlen(input) + 1) != 0)
    {
        fd_ret = open("heredoc", O_RDWR | O_CREAT | O_APPEND);
        write(fd_ret, input, ft_strlen(input));
        input = readline(">");
    }    
    //exit(0);
    //}
    return (fd_ret);
}


int find_input(t_string *input, t_pipe *pipe_info)
{
    t_string *temp;
    int fd;
    
    temp = input;
    while (temp)
    {
        if (temp->append_or_heredoc == 1)
            fd = handle_del(temp, pipe_info);
        else
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
        if (temp->append_or_heredoc == 1)
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
        pipe_info->fd_input = find_input(list->input, pipe_info);
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
