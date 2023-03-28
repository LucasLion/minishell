/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:23:30 by amouly            #+#    #+#             */
/*   Updated: 2023/03/28 14:23:01 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
    else
        // HANDLE ERROR
        return 0;
    close (fd[1]);
    waitpid(pid, NULL, 0);
    return (fd[0]);
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
        {
            fd = open(temp->string, O_RDONLY);
            //exit (-1);
        }
        //if (fd == -1 gerer erreur) 
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

int init_fd(t_command *list, t_pipe *pipe_info)
{
    if (list->input == NULL)
        pipe_info->fd_input = STDIN_FILENO ;
    else
    {
        pipe_info->fd_input = find_input(list->input, pipe_info);
        if (pipe_info->fd_input == -1)
        {
            //write_error(NULL, list->input->string, errno);
            ms_error(list->input->string, NULL, errno);
            return (1);
        }    
    }
    if (list->output == NULL)
        pipe_info->fd_output = STDOUT_FILENO;
    else
    {
        pipe_info->fd_output = find_output(list->output);
        //if (fd_output == -1)
        // gerer l'erreur  
    }
    return (0);
}

void redir_execve(t_core *minishell, t_pipe *pipe_info)
{
    int pid;
    pid = fork();
    if (pid == 0)
    {
        if (pipe_info->fd_input != 0)
        {    
            dup2(pipe_info->fd_input, STDIN_FILENO);
            close (pipe_info->fd_input);
        }
        if (pipe_info->fd_output != 1)
        {
            dup2(pipe_info->fd_output, STDOUT_FILENO);
            close (pipe_info->fd_output);
        } 
        exec_command(pipe_info->cmd, pipe_info->tab_arg, &(minishell->envp));
    }
    wait_proof(minishell);
}

void redir_builtin(t_core *minishell, t_pipe *pipe_info)
{
    int pid;
    pid = fork();
    if (pid == 0)
    {
        if (pipe_info->fd_input != 0)
        {    
            dup2(pipe_info->fd_input, STDIN_FILENO);
            close (pipe_info->fd_input);
        }
        if (pipe_info->fd_output != 1)
        {
            dup2(pipe_info->fd_output, STDOUT_FILENO);
            close (pipe_info->fd_output);
        } 
        exec_builtin(pipe_info->cmd, pipe_info->tab_arg, &(minishell->envp), &minishell->last_status);
    }
    wait_proof(minishell);
}
