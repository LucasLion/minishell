/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:22:46 by amouly            #+#    #+#             */
/*   Updated: 2023/03/30 15:51:53 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int **create_pipes(int nb_of_pipes, int **fd)
{
    int i;
    
    i = 0;
    while (i < nb_of_pipes)
    {
        fd[i] = malloc(sizeof(int) * 2);
        // HANDLE ERROR
        if (pipe(fd[i]) < 0)
            return NULL;
        i++;
        //error + handle les pipes crees
    }
    return (fd);
}

void close_fd_everyhing(int **fd, int nbr_of_pipes)
{
    int i;

    i = 0;
    while (i < nbr_of_pipes)
    {
        close (fd[i][0]);
        close (fd[i][1]);
        free (fd[i]);
        i++;
    }
}

void close_fd_everyhing_but_one(int **fd, int nbr_of_pipes, int a, int b)
{
    int i;

    i = 0;
    while (i < nbr_of_pipes)
    {
        if (fd[a][b] != fd [i][0])
            close (fd[i][0]);
        if (fd[a][b] != fd [i][1])
            close (fd[i][1]);
        i++;
    }
}

void close_fd_everyhing_but_two(int **fd, int nbr_of_pipes, int read, int write)
{
    int i;

    i = 0;
    while (i < nbr_of_pipes)
    {
        if (fd[read][0] != fd [i][0])
            close (fd[i][0]);
        if (fd[write][1] != fd [i][1])
            close (fd[i][1]);
        i++;
    }
}

void wait_all_pid(int *pid, int nbr_of_command, t_core *minishell)
{
    int i;
    t_command *temp;
    char    *cmd;
    
    i = 0;
    temp = minishell->list_of_command;
    minishell->last_status = 0;
    while(i < nbr_of_command)
    {
        cmd = copy_string(temp->command->string, minishell->envp, minishell->last_status);
        wait_proof(minishell, pid[i]);
        ms_error(cmd, NULL, minishell->last_status);
        free (cmd);
        temp = temp->next;
        i++;
    }
}

