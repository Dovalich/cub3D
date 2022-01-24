/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 11:24:04 by twagner           #+#    #+#             */
/*   Updated: 2021/05/21 12:01:39 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	size_t	s1_len;

	if (!s1 || !set)
		return (NULL);
	while (ft_strchr(set, *s1) && *s1)
		++s1;
	s1_len = ft_strlen(s1);
	while (ft_strchr(set, s1[s1_len - 1]) && s1_len)
		--s1_len;
	res = (char *)malloc(sizeof(*res) * (s1_len + 1));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1, s1_len + 1);
	return (res);
}
