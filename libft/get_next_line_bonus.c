/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:56:46 by llion             #+#    #+#             */
/*   Updated: 2023/02/01 17:20:48 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static t_gnl_list	*tank[4096];
	char				*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
	{
		free_tank(tank[fd], 1);
		tank[fd] = NULL;
		return (NULL);
	}
	line = NULL;
	read_and_fill_tank(&(tank[fd]), fd);
	if (tank[fd] == NULL)
		return (NULL);
	line = extract_and_fill_line(tank[fd]);
	clean_tank(&(tank[fd]));
	if (!line)
	{
		free(tank[fd]->content);
		free(tank[fd]);
		tank[fd] = NULL;
	}
	return (line);
}

void	read_and_fill_tank(t_gnl_list **tank, int fd)
{
	char	*buff;
	int		lu;

	while (!find_new_line(*tank))
	{
		buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buff == NULL)
			return ;
		lu = read(fd, buff, BUFFER_SIZE);
		if (lu <= 0)
		{
			free(buff);
			return ;
		}
		if (lu == -1)
		{
			free_tank(*tank, 0);
			free(*tank);
			*tank = NULL;
			return ;
		}
		buff[lu] = '\0';
		ft_lst_add_back(tank, lu, buff);
		free(buff);
	}
}

char	*extract_and_fill_line(t_gnl_list *tank)
{		
	int		i;
	int		j;
	char	*line;

	i = 0;
	malloc_line(tank, &line);
	if (line == NULL)
		return (NULL);
	while (tank)
	{
		j = 0;
		while (tank->content[j] != '\0' && tank->content[j] != '\n')
			line[i++] = tank->content[j++];
		if (tank->content[j] == '\n')
			line[i++] = '\n';
		tank = tank->next;
	}
	line[i] = '\0';
	if (i == 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

void	malloc_line(t_gnl_list *tank, char **line)
{
	int	i;
	int	len;

	len = 0;
	while (tank)
	{
		i = 0;
		while (tank->content[i])
		{
			if (tank->content[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		tank = tank->next;
	}
	*line = malloc(sizeof(char) * (len + 1));
}

void	clean_tank(t_gnl_list **tank)
{
	t_gnl_list	*last;
	t_gnl_list	*clean_node;
	int			i;
	int			j;

	clean_node = malloc(sizeof(t_list));
	if (tank == NULL || clean_node == NULL)
		return ;
	clean_node->next = NULL;
	last = ft_lstlast_gnl(*tank);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content && last->content[i] == '\n')
		i++;
	clean_node->content = malloc(sizeof(char) * (len(last->content) - i + 1));
	if (clean_node->content == NULL)
		return ;
	j = 0;
	while (last->content[i])
		clean_node->content[j++] = last->content[i++];
	clean_node->content[j] = '\0';
	free_tank(*tank, 0);
	*tank = clean_node;
}
