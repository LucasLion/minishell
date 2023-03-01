/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:25:17 by llion             #+#    #+#             */
/*   Updated: 2023/03/01 11:47:25 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

void	print_tab(char **tab, int i)
{
	int	counter;

	counter = 0;
	while (tab[counter])
		counter++;

	while (i < counter - 1)
		printf("%s " , tab[i++]);
	printf("%s", tab[i]);
}

void	echo(char *str)
{
	char	**tab;
	int		i;

	i = 0;
	tab = ft_split(str, ' ');
	if (ft_strncmp(tab[0], "-n", 2))
	{
		print_tab(tab, 0);
		printf("\n");
	}
	else
	{
		print_tab(tab, 1);
	}
	free_tab(tab);
	// TODO 
	// probleme avec la concatenation des espaces dans une string
}

int main(int argc, char **argv, char **envp)
{
	char	*line;
	
	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		line = readline("Minishell > ");
		add_history(line);
		
		if (!ft_strncmp(line, "echo", 4))
			echo(line + 5);
	}
	return (0);
}
