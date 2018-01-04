/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 11:55:54 by alalaoui          #+#    #+#             */
/*   Updated: 2017/04/27 16:27:14 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_tnrvfs(int c)
{
	if (c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f'
			|| c == ' ')
		return (1);
	return (0);
}

int				ft_atoi(char *str)
{
	int			neg;
	int			convert;

	convert = 0;
	neg = 0;
	while (ft_tnrvfs(*str))
		str++;
	if (*str == '-')
	{
		neg = 1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (ft_isdigit(*str) && *str != '\0')
	{
		convert = convert * 10 + (*str - '0');
		str++;
	}
	if (neg == 1)
		return (-convert);
	return (convert);
}
