/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:23:30 by amouly            #+#    #+#             */
/*   Updated: 2023/03/29 17:24:57 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int init_fd(t_command *list, t_pipe *pipe_info)
{
    if (list && list->input == NULL)
    {
        pipe_info->fd_input = STDIN_FILENO ;
    }
    else
    {
        pipe_info->fd_input = find_input(list->input, pipe_info);
        if (pipe_info->fd_input == -1)
        {
            ms_error(list->input->string, NULL, errno);
            return (1);
        }    
    }
    if (list && list->output == NULL)
        pipe_info->fd_output = STDOUT_FILENO;
    else
    {
        pipe_info->fd_output = find_output(list->output);
         if (pipe_info->fd_output == -1)
        {
            ms_error(list->output->string, NULL, errno);
            return (1);
        }  
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
        if (pipe_info->cmd)
            exec_command(pipe_info->cmd, pipe_info->tab_arg, &(minishell->envp));
    }
    wait_proof(minishell, pid);
    ms_error(pipe_info->cmd, NULL, minishell->last_status);
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
    wait_proof(minishell, pid);
}
