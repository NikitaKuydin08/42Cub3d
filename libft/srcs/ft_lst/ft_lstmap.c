/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:46:17 by nkuydin           #+#    #+#             */
/*   Updated: 2025/09/06 21:50:57 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*node;
	t_list	*list;

	if (!lst)
		return (0);
	list = NULL;
	while (lst != 0)
	{
		node = ft_lstnew((*f)(lst->content));
		if (!node)
		{
			ft_lstclear(&lst, del);
			return (0);
		}
		ft_lstadd_back(&list, node);
		lst = lst->next;
	}
	return (list);
}
