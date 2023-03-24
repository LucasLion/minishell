/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:23:30 by amouly            #+#    #+#             */
/*   Updated: 2023/03/24 10:47:47 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int handle_del(t_string *list, t_pipe *pipe_info)
{
    (void) (pipe_info);
    char *input;
    int fd[2];
    int pid;
    
    pipe (fd);
    pid = fork();
    //if (pid < 0) erreur
    if (pid == 0)
    {
        close (fd[0]);
        input = readline(">");
        while (ft_strncmp(list->string, input, ft_strlen(input) + 1) != 0)
        {
            write(fd[1], input, ft_strlen(input));
            write(fd[1], "\n", 1);
            input = readline(">");
        }
        close (fd[1]);
        exit (0);
    }
    close (fd[1]);
    waitpid(pid, NULL, 0);
    return (fd[0]);
}

void handle_del_one(t_string *list)
{
    char *input;
    //int fd_ret;
    
    //fd_ret = 0;
    input = readline(">");
    //close(fd_del[0])
    while (ft_strncmp(list->string, input, ft_strlen(input) + 1) != 0)
    {
        //fd_ret = open("heredoc", O_RDWR | O_CREAT | O_APPEND);
        //write(fd_ret, input, ft_strlen(input));
        input = readline(">");
    }    
    //exit(0);
    //}
    //return (fd_ret);
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
        //if (fd == -1 gerer erreur) 
        temp = temp->next;
    }
    return (fd);
}
int find_input_one(t_string *input)
{
    t_string *temp;
    int fd;
    
    temp = input;
    while (temp)
    {
        if (temp->append_or_heredoc == 1)
            handle_del_one(temp);
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
            fd = open(temp->string, O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
        else
            fd = open(temp->string, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
        temp = temp->next;
    }
    return (fd);
}


void    init_fd(t_command *list, t_pipe *pipe_info)
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

void    init_fd_one(t_command *list, int *fd_input, int *fd_output)
{
    if (list->input == NULL)
        *fd_input = STDIN_FILENO ;
    else
    {
        *fd_input = find_input_one(list->input);
        //if (fd_input == -1)
        // gerer l'erreur    
    }
    if (list->output == NULL)
        *fd_output = STDOUT_FILENO;
     else
    {
       *fd_output = find_output(list->output);
        //if (fd_output == -1)
        // gerer l'erreur  
    }
}
