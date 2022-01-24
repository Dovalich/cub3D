/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 14:29:40 by twagner           #+#    #+#             */
/*   Updated: 2021/11/13 15:36:44 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	char	*new;

	if (!ptr || size == 0)
	{
		if (size == 0)
			size = 1;
		new = (char *)malloc(sizeof(*new) * size);
		if (!new)
		{
			free(ptr);
			return (NULL);
		}
		return (new);
	}
	new = (char *)malloc(sizeof(*new) * size);
	if (!new)
	{
		free(ptr);
		return (NULL);
	}
	new = ft_strcpy(new, ptr);
	free(ptr);
	return (new);
}
