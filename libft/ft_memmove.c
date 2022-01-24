/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 14:41:55 by twagner           #+#    #+#             */
/*   Updated: 2021/05/23 15:21:59 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	i = -1;
	if (!dst && !src && len)
		return (NULL);
	if ((unsigned long)dst > (unsigned long)src)
	{
		while (len-- > 0)
			*((unsigned char *)dst + len) = *((unsigned char *)src + len);
	}
	else
	{
		while (++i < len)
			*((unsigned char *)dst + i) = *((unsigned char *)src + i);
	}
	return (dst);
}
