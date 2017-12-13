/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 15:38:32 by alalaoui          #+#    #+#             */
/*   Updated: 2017/10/23 17:44:39 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdlib.h>

static size_t	ft_words(char const *s, char c)
{
	size_t		i;
	size_t		words;
	int			flag;

	flag = 0;
	words = 0;
	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] != c && flag == 0)
		{
			words++;
			flag = 1;
		}
		if (s[i] == c && flag == 1)
			flag = 0;
		i++;
	}
	return (words);
}

static size_t	ft_strlenc(char const *s, char c)
{
	size_t		len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

int				ft_split_len(char **split)
{
	int			len;

	len = 0;
	while (split[len])
		len++;
	return (len);
}

char			**ft_strsplit(char const *s, char c)
{
	char		**fresh;
	size_t		i;
	size_t		len;

	i = 0;
	len = 0;
	if (!s || !(fresh = (char **)malloc(sizeof(char*) * (ft_words(s, c) + 1))))
		return (NULL);
	fresh[ft_words(s, c)] = 0;
	while (*s)
	{
		while (*s != '\0' && *s == c)
			s++;
		if (*s != '\0' && *s != c)
		{
			len = ft_strlenc(s, c);
			fresh[i] = ft_strsub(s, 0, len);
			i++;
		}
		while (*s != '\0' && *s != c)
			s++;
	}
	return (fresh);
}
