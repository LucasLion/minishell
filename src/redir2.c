/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:23:30 by amouly            #+#    #+#             */
/*   Updated: 2023/04/04 11:48:43 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	init_fd(t_core *minishell, t_pipe *pipe_info, t_command *list)
{
	if (list == NULL || list->input == NULL)
		pipe_info->fd_input = STDIN_FILENO;
	else
	{
		pipe_info->fd_input = find_input(list->input, minishell);
		if (pipe_info->fd_input == -1)
		{
			ms_error(minishell->redir, NULL, errno);
			free(minishell->redir);
			minishell->last_status = 1;
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

void	redir_execve(t_core *minishell, t_pipe *pipe_info)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		if (pipe_info->fd_input != 0)
		{
			dup2(pipe_info->fd_input, STDIN_FILENO);
			close(pipe_info->fd_input);
		}
		if (pipe_info->fd_output != 1)
		{
			dup2(pipe_info->fd_output, STDOUT_FILENO);
			close(pipe_info->fd_output);
		}
		if (pipe_info->cmd)
			minishell->last_status = exec_command(pipe_info->cmd,
					pipe_info->tab_arg, &(minishell->envp));
	}
	wait_proof(minishell, pid);
	if (minishell->last_status == 127)
		ms_error(pipe_info->cmd, NULL, 127);
	return ;
}

void	redir_builtin(t_core *minishell, t_pipe *pipe_info)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		if (pipe_info->fd_input != 0)
		{
			dup2(pipe_info->fd_input, STDIN_FILENO);
			close(pipe_info->fd_input);
		}
		if (pipe_info->fd_output != 1)
		{
			dup2(pipe_info->fd_output, STDOUT_FILENO);
			close(pipe_info->fd_output);
		}
		exec_builtin(pipe_info->cmd, pipe_info->tab_arg, minishell);
		exit(ms_error(pipe_info->cmd, NULL, minishell->last_status));
	}
	wait_proof(minishell, pid);
}
