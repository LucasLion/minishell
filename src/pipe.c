/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:22:46 by amouly            #+#    #+#             */
/*   Updated: 2023/03/28 16:33:53 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void    child_first_pipe(t_pipe *pipe_info, int **fd, char **envp)
{
    if (pipe_info->fd_input != 0)
    {    
        dup2(pipe_info->fd_input, STDIN_FILENO);
        close (pipe_info->fd_input);
    }
    close_fd_everyhing_but_one(fd,pipe_info->nbr_of_pipes,pipe_info->i,1);
    dup2(fd[pipe_info->i][1], pipe_info->fd_output);
    exec_command(pipe_info->cmd, pipe_info->tab_arg, &envp);
    close(fd[pipe_info->i][1]);       
}

void    child_last_pipe(t_pipe *pipe_info, int **fd, char **envp)
{
    if (pipe_info->fd_output != 1)
    {    
        dup2(pipe_info->fd_output,STDOUT_FILENO);
        close (pipe_info->fd_output);
    }
    close_fd_everyhing_but_one(fd,pipe_info->nbr_of_pipes,pipe_info->i-1,0);
    dup2(fd[pipe_info->i -1][0], pipe_info->fd_input);
    exec_command(pipe_info->cmd, pipe_info->tab_arg, &envp);
    close(fd[pipe_info->i - 1][0]);
}

void    child_middle_pipe(t_pipe *pipe_info, int **fd, char **envp)
{
    if (pipe_info->fd_output != 1)
        dup2(pipe_info->fd_output,STDOUT_FILENO);
    if (pipe_info->fd_input != 0)
        dup2(pipe_info->fd_input, STDIN_FILENO);
    close_fd_everyhing_but_two(fd,pipe_info->nbr_of_pipes,pipe_info->i-1,pipe_info->i);
    dup2(fd[pipe_info->i -1][0], pipe_info->fd_input);
    dup2(fd[pipe_info->i][1], pipe_info->fd_output);
    exec_command(pipe_info->cmd, pipe_info->tab_arg, &envp);
    close(fd[pipe_info->i][1]);
    close(fd[pipe_info->i - 1][0]);
}

int child_process(t_pipe *pipe_info, int **fd, char **envp)
{
    if (pipe_info->i == 0)
    {
        child_first_pipe(pipe_info, fd, envp);
        exit (0);
    }
    if (pipe_info->i == pipe_info->nbr_of_commands - 1 )
    {
        child_last_pipe(pipe_info, fd, envp);
        exit (0);
    }
    else
    {
        child_middle_pipe(pipe_info, fd, envp);
        exit (0);
    }
    return (0);
}


int managing_pipe(t_core *minishell, t_pipe *pipe_info, int **fd)
{
    t_command *temp = minishell->list_of_command;

    pipe_info->i = 0;
    int pid[pipe_info->nbr_of_commands];
    while (pipe_info->i <= pipe_info->nbr_of_pipes)
    {
        pipe_info->cmd = copy_string(temp->command->string, minishell->envp, minishell->last_status);
        pipe_info->tab_arg = list_to_tab(temp, minishell->envp, minishell->last_status);
        init_fd(temp, pipe_info);
        pid[pipe_info->i] = fork();
        // HANDLE ERROR
        if (pid[pipe_info->i] < 0)
            printf("error\n");
        else if(pid[pipe_info->i] == 0)
            child_process(pipe_info, fd, minishell->envp);
        if (pipe_info->i < pipe_info->nbr_of_commands)
            temp = temp->next; 
        pipe_info->i++;  
    }
    close_fd_everyhing(fd,pipe_info->nbr_of_pipes);
    wait_all_pid(pid,pipe_info->nbr_of_commands);
    return (0);
}


