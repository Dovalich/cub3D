/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 14:40:09 by twagner           #+#    #+#             */
/*   Updated: 2021/05/21 14:40:13 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_nb_len(int n)
{
	int	len;

	len = 1;
	if (n < 0)
		++len;
	while (n > 9 || n < -9)
	{
		n /= 10;
		++len;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*res;
	long	nb;
	int		len;

	len = ft_nb_len(n);
	res = (char *)malloc(sizeof(*res) * (len + 1));
	if (!res)
		return (NULL);
	nb = (long)n;
	if (nb < 0)
	{
		nb *= -1;
		res[0] = '-';
	}
	else
		res[0] = '0';
	res[len] = '\0';
	while (--len >= 0 && nb != 0)
	{
		res[len] = (nb % 10) + 48;
		nb /= 10;
	}
	return (res);
}
