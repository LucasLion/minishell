/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:22:46 by amouly            #+#    #+#             */
/*   Updated: 2023/03/28 16:27:30 by amouly           ###   ########.fr       */
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

void wait_all_pid(int *pid, int nbr_of_command)
{
    int i;

    i = 0;
    while(i < nbr_of_command)
    {
        waitpid(pid[i], NULL, 0);
        i++;
    }
}

