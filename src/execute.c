/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:22:46 by amouly            #+#    #+#             */
/*   Updated: 2023/03/29 12:08:05 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void execute_one_command(t_core *minishell, t_pipe *pipe_info)
{
    pipe_info->cmd = copy_string(minishell->list_of_command->command->string, minishell->envp, minishell->last_status); 
    pipe_info->tab_arg = list_to_tab(minishell->list_of_command, minishell->envp, minishell->last_status);
    if (init_fd(minishell->list_of_command, pipe_info) != 0)
        return ; 
    if (is_builtin(pipe_info->cmd) == NULL)
        redir_execve(minishell, pipe_info);
    else if ( ft_strncmp(pipe_info->cmd, "echo",5) == 0)
        redir_builtin(minishell, pipe_info);
    else
        exec_builtin(pipe_info->cmd, pipe_info->tab_arg, &(minishell->envp), &minishell->last_status);
}


int execute(t_core *minishell)
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
        managing_pipe(minishell, &pipe_info, fd);
    }
    return (0);
}
