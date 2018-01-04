/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 18:02:16 by alalaoui          #+#    #+#             */
/*   Updated: 2017/12/20 17:50:11 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"
#include <string.h>

/*
**return an empty string if there is only spaces
*/

char			*ft_strtrim(char const *s)
{
	char		*cut;
	size_t		start;
	size_t		len;

	if (!s)
		return (NULL);
	start = 0;
	len = ft_strlen(s) - 1;
	while ((s[start] == '\n' || s[start] == ' '
				|| s[start] == '\t') && s[start])
		start++;
	if (s[start] == '\0')
		return ("");
	while (s[len] == '\n' || s[len] == ' ' || s[len] == '\t')
		len--;
	if (!(cut = ft_strsub(s, start, (len - start + 1))))
		return (NULL);
	return (cut);
}
