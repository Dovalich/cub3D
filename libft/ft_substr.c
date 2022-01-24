/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 10:15:28 by twagner           #+#    #+#             */
/*   Updated: 2021/05/21 11:16:18 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;
	size_t	slen;
	size_t	rlen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
		rlen = 0;
	else if (start + len > slen)
		rlen = slen - start;
	else
		rlen = len;
	res = (char *)malloc(sizeof(*res) * (rlen + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (s[start + i] && i < rlen)
	{
		res[i] = s[start + i];
		++i;
	}
	res[i] = '\0';
	return (res);
}
