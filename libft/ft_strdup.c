/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 10:00:20 by twagner           #+#    #+#             */
/*   Updated: 2021/10/30 13:47:07 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dup;

	if (!s1)
		return (NULL);
	dup = (char *)malloc(sizeof(*dup) * (ft_strlen(s1) + 1));
	if (!dup)
		return (NULL);
	return (ft_strcpy(dup, s1));
}
