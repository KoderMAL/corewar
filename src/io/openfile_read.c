/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openfile_read.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 17:28:06 by stoupin           #+#    #+#             */
/*   Updated: 2018/02/13 10:37:20 by dhadley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "openfile.h"

int	openfile_read_buf(t_openfile *of, void *dest, int len, int reverse)
{
	int		i;
	int		ret;
	char	*c_dest;
	char	c;

	if (dest == NULL)
		return (1);
	c_dest = (char*)dest;
	i = 0;
	while (i < len)
	{
		ret = openfile_read_char(of, &c);
		if (reverse)
			c_dest[len - i - 1] = c;
		else
			c_dest[i] = c;
		if (ret < 0)
			return (ret);
		if (ret == 0)
			break ;
		i++;
	}
	return (i);
}

int	openfile_skip(t_openfile *of, int len)
{
	int		i;
	int		ret;
	char	dummy;

	i = 0;
	while (i < len)
	{
		ret = openfile_read_char(of, &dummy);
		if (ret < 0)
			return (ret);
		if (ret == 0)
			break ;
		i++;
	}
	return (i);
}
