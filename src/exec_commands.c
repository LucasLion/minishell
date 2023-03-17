/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:25:45 by llion             #+#    #+#             */
/*   Updated: 2023/03/15 15:32:20 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_command(char *input, t_command *list)
{
	parse_input_loc(input, list);

	//if (list->command)
	//	printf("%s\n", list->command->string);
}
