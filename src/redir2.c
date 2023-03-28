/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:23:30 by amouly            #+#    #+#             */
/*   Updated: 2023/03/28 16:41:24 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
        exit(ms_error(pipe_info->cmd, NULL, minishell->last_status));
    }
    wait_proof(minishell);
}