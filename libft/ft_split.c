/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 12:02:01 by twagner           #+#    #+#             */
/*   Updated: 2021/05/21 12:36:07 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"

static size_t	ft_nb_words(char const *s, char c)
{
	size_t	res;

	res = 0;
	if (*s == '\0')
		return (0);
	if (c == '\0')
		return (++res);
	while (ft_strchr(s, c))
	{
		if (ft_strchr(s, c) - s > 0)
			++res;
		s = ft_strchr(s, c) + 1;
	}
	if (ft_strlen(s))
		++res;
	return (res);
}

static	char	*ft_free_words(char **res, size_t nb)
{
	size_t	i;

	i = 0;
	while (i < nb)
	{
		free(res[i]);
		++i;
	}
	return (NULL);
}

static	char	*ft_word_dup(char **tab, size_t i, const char *str, char sep)
{
	char	*word;

	word = ft_substr(str, 0, ft_strchr(str, sep) - str);
	if (!(word))
		return (ft_free_words(tab, i));
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	i;
	size_t	nb_words;

	if (!s)
		return (NULL);
	nb_words = ft_nb_words(s, c);
	res = (char **)malloc(sizeof(*res) * (nb_words + 1));
	if (!res)
		return (NULL);
	res[nb_words] = NULL;
	i = -1;
	while (++i < nb_words)
	{
		while (ft_strchr(s, c) - s == 0)
			++s;
		res[i] = ft_word_dup(res, i, s, c);
		if (!res[i])
		{
			free(res);
			return (NULL);
		}
		s = ft_strchr(s, c) + 1;
	}
	return (res);
}
