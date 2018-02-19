/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lramirez <lramirez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 21:11:29 by lramirez          #+#    #+#             */
/*   Updated: 2018/02/19 11:04:51 by lramirez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"
# include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	unsigned char	*ptr;
	size_t			i;

	if (!(ptr = (unsigned char *)malloc(sizeof(unsigned char) * size)))
		return (NULL);
	i = 0;
	while (i < size)
	{
		ptr[i] = (unsigned char)0;
		i++;
	}
	return (ptr);
}
