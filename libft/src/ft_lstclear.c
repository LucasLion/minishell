/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 19:25:55 by llion             #+#    #+#             */
/*   Updated: 2022/11/14 11:47:18 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (lst && del)
	{
		if (*lst)
		{
			while (*lst != NULL)
			{
				tmp = (*lst)->next;
				ft_lstdelone(*lst, del);
				*lst = tmp;
			}
		}
	}
}
