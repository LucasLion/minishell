/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main-lucas.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:55:57 by llion             #+#    #+#             */
/*   Updated: 2023/03/15 15:41:20 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <sys/types.h>

int	ms_exit()
{
    pid_t pid;
    int x = 1;

    pid = fork();

    if (pid == 0)
	{
        // Code exécuté par le processus enfant
        printf("Je suis le processus enfant. x = %d\n", ++x);
        exit(0);
    } else if (pid > 0)
	{
        // Code exécuté par le processus parent
        printf("Je suis le processus parent. x = %d\n", --x);
    } else
	{
        // La fonction fork a échoué
        fprintf(stderr, "La fonction fork a échoué\n");
        return 1;
    }

    return 0;
}

int main(int argc, char **argv, char **envp) 
{
	(void)argc;
	(void)argv;
	(void)envp;
	//char	*line;
	//t_command *list;

	//list = NULL;
	//while (1)
	//{
	//	line = readline("Minishell$ ");
	//	add_history(line);
	//	exec_command(line, list);
	//}
	ms_exit();
}
