/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_trimed_right.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noufel <noufel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 11:15:11 by noufel            #+#    #+#             */
/*   Updated: 2022/01/24 11:28:42 by noufel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"

char	*ft_get_trimed_right(char *str)
{
	int		i;
	int		len;
	char	*trimed;

	len = ft_strlen(str);
	while (len > 0)
	{
		if (str[len - 1] != ' ')
			break ;
		--len;
	}
	if (len == 0)
		return (NULL);
	trimed = malloc(sizeof(*trimed) * len + 1);
	i = 0;
	while (i < len)
	{
		trimed[i] = str[i];
		++i;
	}
	trimed[i] = '\0';
	return (trimed);
}
