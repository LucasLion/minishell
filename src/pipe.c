/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:22:46 by amouly            #+#    #+#             */
/*   Updated: 2023/03/28 14:19:55 by amouly           ###   ########.fr       */
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
    // HANDLE EXITS
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


int managing_fork(t_core *minishell, t_pipe *pipe_info, int **fd)
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

void    wait_proof(t_core *minishell)
{
    int status;
    wait(&status);
    if (WIFEXITED(status))
        minishell->last_status = WEXITSTATUS(status) % 255;
}

void execute_one_command(t_core *minishell, t_pipe *pipe_info)
{
    pipe_info->cmd = copy_string(minishell->list_of_command->command->string, minishell->envp, minishell->last_status); 
    pipe_info->tab_arg = list_to_tab(minishell->list_of_command, minishell->envp, minishell->last_status);
    if (init_fd(minishell->list_of_command, pipe_info) != 0)
        return ; 
    if (is_builtin(pipe_info->cmd) == NULL)
        redir_execve(minishell, pipe_info);
    if ( ft_strncmp(pipe_info->cmd, "echo",5) == 0)
        redir_builtin(minishell, pipe_info);
    else
        exec_builtin(pipe_info->cmd, pipe_info->tab_arg, &(minishell->envp), &minishell->last_status);
}


int managing_pipe(t_core *minishell)
{
    t_pipe pipe_info;
    t_command *list;
    
    list = minishell->list_of_command;
    pipe_info.nbr_of_pipes = 0;
    pipe_info.nbr_of_commands = length_list_command(list, &pipe_info.nbr_of_pipes);
    if (pipe_info.nbr_of_commands == 1)
        execute_one_command(minishell, &pipe_info);
    else 
    {
        int **fd;
        // HANDLE MALLOC ERROR
        fd = malloc(sizeof (int *) * pipe_info.nbr_of_pipes);
        fd = create_pipes(pipe_info.nbr_of_pipes, fd);
        managing_fork(minishell, &pipe_info, fd);
    }
    return (0);
}
