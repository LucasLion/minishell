/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:24:52 by llion             #+#    #+#             */
/*   Updated: 2023/04/01 17:40:33 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*void	sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}*/

void	sigint(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    if (errno == EINTR)
    {
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
    else
    {
        kill(getpid(), SIGQUIT);
    }
}

void	signals(void)
{
	signal(SIGINT, sigint);
	signal(SIGQUIT, SIG_IGN);
}
