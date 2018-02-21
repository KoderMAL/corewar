/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lramirez <lramirez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 23:32:45 by lramirez          #+#    #+#             */
/*   Updated: 2018/02/17 15:09:49 by lramirez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	ft_abs(int n)
{
	unsigned int nb;

	if (n < 0)
	{
		nb = (unsigned int)-n;
		return (nb);
	}
	return (n);
}