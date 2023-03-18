/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:22:46 by amouly            #+#    #+#             */
/*   Updated: 2023/03/18 15:04:18 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
typedef struct s_pipe
{
	int			nbr_of_pipes;
	int			reading_index;
    int			writing_index;
	char		*cmd_1;
	char		**tab_argv_1;
	char		*cmd_2;
	char		**tab_argv_2;
	char		**envp;
	
}					t_pipe;
*/

int **create_pipes(int nb_of_pipes, int **fd)
{
    int i;
    
    i = 0;
    while (i < nb_of_pipes)
    {
        fd[i] = malloc(sizeof(int) * 2);
        if (pipe(fd[i]) < 0)
            return NULL;
        i++;
        //error + handle les pipes crees
    }
    return (fd);
}

void close_fd_everyhing_but(int **fd, t_pipe *info)
{
    int i;

    i = 0;
    while (i < info->nbr_of_pipes)
    {
        if (i != info->reading_index)
            close (fd[i][0]);
        if (i != info->writing_index)
            close (fd[i][1]);
        i++;
    }
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

int create_forks(int **fd, t_pipe *pipe_info)
{
    int pid1;
    int pid2;
    
    pid1 = fork();
    if (pid1 == -1)
        return (0);
    //error
    if (pid1 == 0)
    {
        close_fd_everyhing_but(fd, pipe_info);
        close (fd[pipe_info->reading_index][0]);  
        dup2(fd[pipe_info->writing_index][1], STDOUT_FILENO);
        exec_command(pipe_info->cmd_1, pipe_info->tab_argv_1, pipe_info->envp);
        close (fd[pipe_info->writing_index][1]);
        exit (0);
    }
    pid2 = fork();
    if (pid2 == -1)
        return (0);
    //error
    if (pid2 == 0)
    {
        close_fd_everyhing_but(fd, pipe_info);
        close (fd[pipe_info->writing_index][1]);
        dup2(fd[pipe_info->reading_index][0], STDIN_FILENO);
        exec_command(pipe_info->cmd_2, pipe_info->tab_argv_2, pipe_info->envp);
        close (fd[pipe_info->reading_index][0]);  
        exit (0);
    }
    close_fd_everyhing(fd, pipe_info->nbr_of_pipes);
    waitpid(pid1,NULL,0);
    waitpid(pid2,NULL,0);
    return (0);
}

int managing_forks(int **fd, int nb_of_pipes, t_command *list, char **envp )
{
    int i;
    t_pipe pipe_info;
    t_command *temp = list;

    pipe_info.nbr_of_pipes = nb_of_pipes;
    pipe_info.envp = envp;    
    i = 0;
    while (i < nb_of_pipes)
    {
        pipe_info.reading_index = i - 1;
        pipe_info.writing_index = i; 
        if (i == 0)
            pipe_info.reading_index = nb_of_pipes - 1;
        pipe_info.tab_argv_1 = list_to_tab(temp->command, envp);
        pipe_info.cmd_1 = copy_string(temp->command->string, envp);
        temp= temp->next;
        if (temp != NULL)
        {
            pipe_info.tab_argv_2 = list_to_tab(temp->command, envp);
            pipe_info.cmd_2 = copy_string(temp->command->string, envp);
        }
        create_forks(fd, &pipe_info);
        i++;   
    }
    return (0);
}


int managing_pipes(t_command *list , char **envp)
{
    int nb_of_command;
    int nb_of_pipes;
    
    nb_of_pipes = 0;
    nb_of_command = length_list_command(list, &nb_of_pipes);
    int **fd;
    fd = malloc(sizeof (int *) * nb_of_pipes);
    fd = create_pipes(nb_of_pipes, fd);
    //if (fd == NULL)
       // return (-1);
    managing_forks(fd, nb_of_pipes, list, envp);
    return (0);
}