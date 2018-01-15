/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 20:52:44 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/11 14:12:41 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

/*
** On initialise une memoire result pour garder l'adresse du premier element
*/

char		*ft_strcpy(char *dst, const char *src)
{
	char	*result;

	result = dst;
	while (*src != '\0')
		*dst++ = *src++;
	*dst = '\0';
	return (result);
}
