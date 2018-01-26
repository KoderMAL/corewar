/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhadley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 15:06:19 by dhadley           #+#    #+#             */
/*   Updated: 2018/01/26 15:10:13 by dhadley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	check_params(unsigned char byte, int number)
{
	int shift;

	shift = 8 - (number * 2);
	if (((byte >> shift) & DIR_CODE) == DIR_CODE)
		return (DIR_CODE);
	if (((byte >> shift) & IND_CODE) == IND_CODE)
		return (IND_CODE);
	if (((byte >> shift) & REG_CODE) == REG_CODE)
		return (REG_CODE);
	return (0);	
}
