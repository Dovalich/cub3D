/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 07:36:05 by twagner           #+#    #+#             */
/*   Updated: 2021/05/22 07:36:07 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*new_lst;

	if (!lst)
		return (NULL);
	new_lst = NULL;
	while (lst)
	{
		if ((*f))
			new = ft_lstnew((*f)(lst->content));
		else
			new = ft_lstnew(lst->content);
		if (!new)
			return (NULL);
		ft_lstadd_back(&new_lst, new);
		lst = lst->next;
	}
	ft_lstclear(&lst, del);
	return (new_lst);
}
