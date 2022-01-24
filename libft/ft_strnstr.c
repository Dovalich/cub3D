/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 08:58:35 by twagner           #+#    #+#             */
/*   Updated: 2022/01/09 09:42:41 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = -1;
	if (*needle == '\0')
		return ((char *)haystack);
	if (!haystack)
		return (NULL);
	while (++i < len && haystack[i])
	{
		j = 0;
		while (haystack[i + j] == needle[j] && i + j < len)
		{
			if (needle[++j] == '\0')
				return ((char *)haystack + i);
		}
	}
	return (NULL);
}
