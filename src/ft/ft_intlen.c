/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lramirez <lramirez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 23:40:25 by lramirez          #+#    #+#             */
/*   Updated: 2018/02/17 15:05:24 by lramirez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

size_t	ft_intlen(unsigned int n)
{
	if (n > 9)
		return (1 + ft_intlen(n / 10));
	return (1);
}
