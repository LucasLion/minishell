/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:23:30 by amouly            #+#    #+#             */
/*   Updated: 2023/03/30 14:21:46 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int init_fd(t_core *minishell, t_pipe *pipe_info)
{
    t_command *list = minishell->list_of_command;
    if (list == NULL || list->input == NULL)
        pipe_info->fd_input = STDIN_FILENO ;
    else
    {
        pipe_info->fd_input = find_input(list->input, minishell);
        if (pipe_info->fd_input == -1)
        {
            ms_error(list->input->string, NULL, errno);
            return (1);
        }    
    }
    if (list == NULL || list->output == NULL)
        pipe_info->fd_output = STDOUT_FILENO;
    else
    {
        pipe_info->fd_output = find_output(list->output, minishell);
         if (pipe_info->fd_output == -1)
        {
            ms_error(list->output->string, NULL, errno);
            return (1);
        }  
    }
    return (0);
}

void    wait_proof(t_core *minishell, int pid)
{
    int status;
    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        minishell->last_status = WEXITSTATUS(status) % 255;
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
