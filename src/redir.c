/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:23:30 by amouly            #+#    #+#             */
/*   Updated: 2023/03/31 16:26:08 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_del(char *str)
{
	char	*input;
	int		fd[2];
	int		pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		input = readline(">");
		while (ft_strncmp(str, input, ft_strlen(input) + 1) != 0)
		{
			write(fd[1], input, ft_strlen(input));
			write(fd[1], "\n", 1);
			input = readline(">");
		}
		close(fd[1]);
		exit(0);
	}
	close(fd[1]);
	waitpid(pid, NULL, 0);
	return (fd[0]);
}

int	ambiguous_redirect(char *str, t_core *minishell)
{
	int	i;
	int	fd;

	fd = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
		{
			errno = -2;
			minishell->last_status = 1;
			return (-1);
		}
		i++;
	}
	return (fd);
}

int	find_input(t_string *input, t_core *m)
{
	t_string	*temp;
	char		*new_str;
	int			fd;

	temp = input;
	while (temp)
	{
		new_str = copy_string(temp->string, m->envp, m->last_status);
		fd = ambiguous_redirect(new_str, m);
		if (fd == -1)
			return (fd);
		else if (temp->append_or_heredoc == 1)
			fd = handle_del(new_str);
		else
			fd = open(new_str, O_RDONLY);
		if (fd == -1)
		{
			m->redir = ft_strdup(new_str);
			free(new_str);
			return (fd);
		}
		temp = temp->next;
		free(new_str);
	}
	return (fd);
}

int	find_output(t_string *output, t_core *m)
{
	t_string	*temp;
	int			fd;
	char		*new_str;

	temp = output;
	while (temp)
	{
		new_str = copy_string(temp->string, m->envp, m->last_status);
		fd = ambiguous_redirect(new_str, m);
		if (fd == -1)
			return (fd);
		else if (temp->append_or_heredoc == 1)
			fd = open(new_str, O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
		else
			fd = open(new_str, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
		if (fd == -1)
		{
			m->redir = ft_strdup(new_str);
			free(new_str);
			return (fd);
		}
		temp = temp->next;
		free(new_str);
	}
	return (fd);
}
