/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 08:54:28 by twagner           #+#    #+#             */
/*   Updated: 2021/05/21 08:58:17 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	s_len;
	size_t	d_len;
	size_t	i;
	size_t	result;

	i = 0;
	s_len = ft_strlen(src);
	d_len = ft_strlen(dst);
	if (dstsize >= d_len)
		result = s_len + d_len;
	else
		result = s_len + dstsize;
	if (dstsize > d_len)
	{
		while (src[i] && d_len < dstsize - 1)
		{
			dst[d_len] = src[i];
			++d_len;
			++i;
		}
	}
	dst[d_len] = '\0';
	return (result);
}
