/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:23:30 by amouly            #+#    #+#             */
/*   Updated: 2023/03/21 17:27:32 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int handle_del(t_string *list)
{
    //int fd_del[2];
    char *input;
    //int pid_del;
    //pid_del = fork();
    //ERREUR SI FORK <0
    //if (pid_del == 0)
    // {
    input = readline(">");
    //close(fd_del[0])
    while (ft_strncmp(list->string, input, ft_strlen(input) + 1) != 0)
        input = readline(">");    
    //exit(0);
    //}
    return (0);
}


int find_input(t_string *input)
{
    t_string *temp;
    int fd;
    
    temp = input;
    while (temp)
    {
        if (temp->append_or_heredoc == 1)
            handle_del(temp);
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
