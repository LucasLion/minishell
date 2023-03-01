/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:25:17 by llion             #+#    #+#             */
/*   Updated: 2023/03/01 17:28:07 by llion            ###   ########.fr       */
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

int		quotes_nbr(char *str)
{
	int	i;
	int	count1;
	int	count2;

	i = 0;
	count1 = 0;
	count2 = 0;
	while (str[i])
	{
		if (str[i] == '"')
			count1++;
		else if (str[i] == '\'')
			count2++;
		i++;
	}
	if (count1 % 2 == 0 && count2 % 2 == 0)
		return (1);
	else
		return (0);
}


int	command_len(char *str)
{
	int	i;
	int	cmd_len;

	i = 0;
	cmd_len = 0;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && str[i] != ' ' && str[i] != '"' && str[i] != '\'')
	{
		i++;
		cmd_len++;
	}
	return (cmd_len);
}

char	*find_command(char *str)
{
	int			i;
	char		*cmd;

	if (!quotes_nbr(str))
	{
		printf("Erreur de quotes");
		return (NULL);
	}
	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	cmd = malloc(sizeof(char) * (command_len(str) + 1));
	if (cmd == NULL)
		return (NULL);
	ft_strlcpy(cmd, &str[i], command_len(str) + 1);
	printf("cmd_len: %d\n", command_len(str));
	return (cmd);
}

char	**find_args(char *str)
{
	int		i;
	char	**tab;
	
	i = 0;
	tab = NULL;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && str[i] != ' ' && str[i] != '"' && str[i] != '\'')
		i++;
	return (tab);	
}

int main(int argc, char **argv, char **envp)
{
	char	*line;
	char	*cmd;
	
	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		line = readline("Minishell > ");
		add_history(line);
		cmd = find_command(line);
		printf("cmd: %s\n", cmd);
		free(cmd);
	}
	return (0);
}
