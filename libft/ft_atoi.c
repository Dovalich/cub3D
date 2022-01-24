/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 09:28:22 by twagner           #+#    #+#             */
/*   Updated: 2021/05/21 09:52:14 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int		sign;
	double	result;

	sign = 1;
	result = 0;
	while (ft_isspace(*str))
		++str;
	if (*str == '+' || *str == '-')
	{
		sign = sign + (43 - *str);
		++str;
	}
	while (ft_isdigit(*str))
	{
		result = (result * 10) + (*str - 48);
		++str;
	}
	if (sign == 1 && result > LONG_MAX)
		result = -1;
	else if (sign == -1 && (result * -1) < LONG_MIN)
		result = 0;
	else
		result *= sign;
	return ((int)result);
}
