/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhadley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 15:56:44 by dhadley           #+#    #+#             */
/*   Updated: 2018/01/15 12:03:17 by dhadley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memset(void *b, int c, int len)
{
	int				i;
	unsigned char	*string;
	unsigned char	value;

	value = (unsigned char)c;
	string = (unsigned char*)b;
	i = 0;
	while (i < len)
	{
		string[i] = value;
		i++;
	}
	return (b);
}
