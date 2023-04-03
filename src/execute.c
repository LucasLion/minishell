/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:22:46 by amouly            #+#    #+#             */
/*   Updated: 2023/04/03 18:10:57 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_pipe_info(t_pipe *p, t_command *list)
{
	p->nbr_of_pipes = 0;
	p->nbr_of_commands = length_list_command(list,
			&(p->nbr_of_pipes));
	p->i = 0;
	p->cmd = 0;
	p->tab_arg = NULL;
	p->fd_input = 0;
	p->fd_output = 1;
}

int	execute_one_command(t_core *m, t_pipe *pipe_info)
{
	if (m->list_of_command->command
		&& m->list_of_command->command->string)
		pipe_info->cmd = copy_string(m->list_of_command->command->string,
				m->envp, m->last_status);
	if (m->list_of_command->command)
		pipe_info->tab_arg = list_to_tab(m->list_of_command,
				m->envp, m->last_status);
	if (init_fd(m, pipe_info, m->list_of_command) != 0)
		return (0);
	if (pipe_info->cmd)
	{
		if (is_builtin(pipe_info->cmd) == NULL)
			redir_execve(m, pipe_info);
		else if (ft_strncmp(pipe_info->cmd, "echo", 5) == 0)
			redir_builtin(m, pipe_info);
		else
			exec_builtin(pipe_info->cmd, pipe_info->tab_arg, m);
		return (1);
	}
	return (0);
}

int	execute(t_core *minishell)
{
	t_pipe		pipe_info;
	t_command	*list;
	int			**fd;

	fd = NULL;
	list = minishell->list_of_command;
	init_pipe_info(&pipe_info, list);
	if (pipe_info.nbr_of_commands == 1)
	{
		if (execute_one_command(minishell, &pipe_info))
		{
			free(pipe_info.cmd);
			free_tab2(pipe_info.tab_arg);
		}
	}
	else
	{
		fd = malloc(sizeof(int *) * pipe_info.nbr_of_pipes);
		fd = create_pipes(pipe_info.nbr_of_pipes, fd);
		managing_pipe(minishell, &pipe_info, fd);
		free(fd);
	}
	return (0);
}

int	is_absolute(char *cmd)
{
	if (cmd && cmd[0] == '/')
	{
		if (access(cmd, X_OK) == 0)
			return (1);
		return (0);
	}
	return (0);
}
