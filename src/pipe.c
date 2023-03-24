/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:22:46 by amouly            #+#    #+#             */
/*   Updated: 2023/03/24 14:27:59 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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


int managing_fork(t_command *list, t_pipe *pipe_info, int **fd, char **envp )
{
    t_command *temp = list;

    pipe_info->i = 0;
    int pid[pipe_info->nbr_of_commands];
    while (pipe_info->i <= pipe_info->nbr_of_pipes)
    {
        pipe_info->cmd = copy_string(temp->command->string, envp);
        pipe_info->tab_arg = list_to_tab(temp->command, envp);
        init_fd(temp, pipe_info);
        pid[pipe_info->i] = fork();
        if (pid[pipe_info->i] < 0)
            printf("error\n");
        else if(pid[pipe_info->i] == 0)
            child_process(pipe_info, fd, envp);
        if (pipe_info->i < pipe_info->nbr_of_commands)
            temp = temp->next; 
        pipe_info->i++;  
    }
    close_fd_everyhing(fd,pipe_info->nbr_of_pipes);
    wait_all_pid(pid,pipe_info->nbr_of_commands);
    return (0);
}

void execute_one_command(t_command *list, t_pipe *pipe_info, char ***envp)
{
    (void) pipe_info;

    pipe_info->cmd = copy_string(list->command->string, *envp); 
    pipe_info->tab_arg = list_to_tab(list->command, *envp); 
    init_fd(list, pipe_info);
    if (is_builtin(pipe_info->cmd) == NULL || ft_strncmp(is_builtin(pipe_info->cmd), "echo",5) == 0)
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
            exec_command(pipe_info->cmd, pipe_info->tab_arg, envp);
            exit (0);
        }
        waitpid(pid, NULL, 0);
    }
    else
        exec_builtin(is_builtin(pipe_info->cmd), pipe_info->tab_arg, envp);
    return ;
}


int managing_pipe(t_command *list , char ***envp)
{
    t_pipe pipe_info;
    int i;

    i = 0;
    pipe_info.nbr_of_pipes = 0;
    pipe_info.nbr_of_commands = length_list_command(list, &pipe_info.nbr_of_pipes);
    if (pipe_info.nbr_of_commands == 1)
        execute_one_command(list, &pipe_info, envp);
    else 
    {
        int **fd;
        fd = malloc(sizeof (int *) * pipe_info.nbr_of_pipes);
        fd = create_pipes(pipe_info.nbr_of_pipes, fd);
        managing_fork(list, &pipe_info, fd, *envp);
    }
    return (0);
}
