/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:04:24 by llion             #+#    #+#             */
/*   Updated: 2022/11/10 18:50:58 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *newly)
{
	t_list	*current_lst;

	if (*lst == 0)
		*lst = newly;
	else
	{
		current_lst = ft_lstlast(*lst);
		current_lst->next = newly;
	}
}
