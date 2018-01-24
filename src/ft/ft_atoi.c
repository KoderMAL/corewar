/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 11:55:54 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/23 14:55:09 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

int				ft_atoi(char *str)
{
	int			neg;
	int			convert;

	convert = 0;
	neg = 0;
	while (ft_isspace(*str))
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
