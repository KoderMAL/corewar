/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lramirez <lramirez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 15:06:19 by dhadley           #+#    #+#             */
/*   Updated: 2018/01/29 14:25:25 by dhadley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	check_params(unsigned char byte, int number)
{
	int shift;

	shift = 8 - (number * 2);
	if (((byte >> shift) & 3) == DIR_CODE)
		return (DIR_CODE);
	if (((byte >> shift) & 3) == IND_CODE)
		return (IND_CODE);
	if (((byte >> shift) & 3) == REG_CODE)
		return (REG_CODE);
	return (0);	
}

int		recup_param(t_vm *vm, int location, int size)
{
	// nombres négatifs ?!
	if (size == 1)
		return (vm->map[location]);
	else if (size == 2)
		return (vm->map[location] << 8 | vm->map[(location + 1) % MEM_SIZE]);
	else if (size == 4)
		return (vm->map[location] << 24 | vm->map[(location + 1) % MEM_SIZE] << 16 | vm->map[(location + 2) % MEM_SIZE] << 8 | vm->map[(location + 3) % MEM_SIZE]);
	else
		return (-1);
}
