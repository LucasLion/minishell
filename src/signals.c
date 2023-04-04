/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:24:52 by llion             #+#    #+#             */
/*   Updated: 2023/04/04 13:10:17 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sigint(int sig)
{
	pid_t	pid;

	pid = waitpid(-1, NULL, WNOHANG);
	if (pid < 0)
	{
		write(1, "\n", 1);
		if (g_global.catch == 1)
		{
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
			g_global.status = 1;
		}
		if (g_global.catch == 0)
		{
			g_global.status = 130;
		}
	}
	else if (g_global.catch == 0 && sig == SIGINT)
	{
		write(1, "\n", 1);
		g_global.status = 130;
	}
}

void	signals(void)
{
	signal(SIGINT, sigint);
	signal(SIGQUIT, SIG_IGN);
}
