/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlageard <vlageard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 19:42:01 by vlageard          #+#    #+#             */
/*   Updated: 2022/11/14 12:17:59 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*newnew(void *content, void (*del)(void *))
{
	t_list	*element;

	element = (malloc(sizeof(t_list)));
	if (element == 0)
	{
		del(content);
		return (0);
	}
	element->content = content;
	element->next = 0;
	return (element);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*new;

	head = 0;
	if (!lst || !f)
		return (0);
	while (lst)
	{
		new = newnew(f(lst->content), del);
		if (new == NULL)
		{
			ft_lstclear(&new, del);
			break ;
		}
		ft_lstadd_back(&head, new);
		lst = lst->next;
	}
	return (head);
}
