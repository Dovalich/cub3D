/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 09:53:34 by twagner           #+#    #+#             */
/*   Updated: 2021/05/21 09:59:52 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*tab;
	size_t	i;

	i = -1;
	tab = (void *)malloc(count * size);
	if (!tab)
		return (NULL);
	while (++i < (count * size))
		*((unsigned char *)tab + i) = 0;
	return (tab);
}
