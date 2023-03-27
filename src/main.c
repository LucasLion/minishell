/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:55:57 by llion             #+#    #+#             */
/*   Updated: 2023/03/27 14:33:05 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

#define RO "\033[0;31m"
#define G "\033[0;32m"
#define Y "\033[0;33m"
#define B "\033[0;34m"
#define P "\033[0;35m"
#define C "\033[0;36m"
#define N "\033[0m"

int main(int argc, char **argv, char **env) 
{
	(void)argv;
	char		*input;
	t_command	*list_of_command;
	char		**envp;
	
    // HANDLE ERROR
	if (argc != 1)
        return (0);
	envp = copy_tab(env);
	while (1)
	{
		list_of_command = NULL;
		input = readline(C"M"G"i"Y"n"B"i"P"s"C"h"RO"e"G"l"Y"l"B" $ " N);
        add_history(input);
        parse_input(input, &list_of_command);
		managing_pipe(list_of_command, &envp);
        clean_list_command(&list_of_command);	
	}	
}

