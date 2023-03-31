/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:22:46 by amouly            #+#    #+#             */
/*   Updated: 2023/03/31 16:54:10 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	child_first_pipe(t_pipe *pipe_info, int **fd, char **envp)
{
	if (pipe_info->fd_input != 0)
	{
		dup2(pipe_info->fd_input, STDIN_FILENO);
		close(pipe_info->fd_input);
	}
	if (pipe_info->fd_output != 1)
		dup2(pipe_info->fd_output, STDOUT_FILENO);
	else
		dup2(fd[pipe_info->i][1], pipe_info->fd_output);
	close_fd_everyhing_but_one(fd, pipe_info->nbr_of_pipes, pipe_info->i, 1);
	exec_command(pipe_info->cmd, pipe_info->tab_arg, &envp);
	close(fd[pipe_info->i][1]);
}

void	child_last_pipe(t_pipe *pipe_info, int **fd, char **envp)
{
	if (pipe_info->fd_output != 1)
	{
		dup2(pipe_info->fd_output, STDOUT_FILENO);
		close(pipe_info->fd_output);
	}
	if (pipe_info->fd_input != 0)
		dup2(pipe_info->fd_input, STDIN_FILENO);
	else
		dup2(fd[pipe_info->i - 1][0], pipe_info->fd_input);
	close_fd_everyhing_but_one(fd, pipe_info->nbr_of_pipes, pipe_info->i - 1,
		0);
	exec_command(pipe_info->cmd, pipe_info->tab_arg, &envp);
	close(fd[pipe_info->i - 1][0]);
}

void	child_middle_pipe(t_pipe *pipe_info, int **fd, char **envp)
{
	if (pipe_info->fd_output != 1)
		dup2(pipe_info->fd_output, STDOUT_FILENO);
	if (pipe_info->fd_input != 0)
		dup2(pipe_info->fd_input, STDIN_FILENO);
	close_fd_everyhing_but_two(fd, pipe_info->nbr_of_pipes, pipe_info->i - 1,
		pipe_info->i);
	dup2(fd[pipe_info->i - 1][0], pipe_info->fd_input);
	dup2(fd[pipe_info->i][1], pipe_info->fd_output);
	exec_command(pipe_info->cmd, pipe_info->tab_arg, &envp);
	close(fd[pipe_info->i][1]);
	close(fd[pipe_info->i - 1][0]);
}

int	child_process(t_pipe *pipe_info, int **fd, char **envp)
{
	if (pipe_info->i == 0)
	{
		child_first_pipe(pipe_info, fd, envp);
		exit(0);
	}
	if (pipe_info->i == pipe_info->nbr_of_commands - 1)
	{
		child_last_pipe(pipe_info, fd, envp);
		exit(0);
	}
	else
	{
		child_middle_pipe(pipe_info, fd, envp);
		exit(0);
	}
	return (0);
}

int	managing_pipe(t_core *m, t_pipe *pi, int **fd)
{
	t_command	*t;
	int			*pid;

	pid = ft_calloc(pi->nbr_of_commands, sizeof(int));
	t = m->list_of_command;
	while (pi->i <= pi->nbr_of_pipes)
	{
		pi->cmd = copy_string(t->command->string, m->envp,
				m->last_status);
		pi->tab_arg = list_to_tab(t, m->envp, m->last_status);
		init_fd(m, pi, t);
		pid[pi->i] = fork();
		if (pid[pi->i] < 0)
			printf("error de fork\n");
		else if (pid[pi->i] == 0)
			child_process(pi, fd, m->envp);
		free(pi->cmd);
		free_tab2(pi->tab_arg);
		if (pi->i < pi->nbr_of_commands)
			t = t->next;
		pi->i++;
	}
	close_fd_everyhing(fd, pi->nbr_of_pipes);
	wait_all_pid(pid, pi->nbr_of_commands, m);
	return (0);
}
