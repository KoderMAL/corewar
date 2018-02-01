/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhadley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 15:23:39 by dhadley           #+#    #+#             */
/*   Updated: 2018/01/29 17:53:19 by dhadley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
Cette instruction prend 2 paramètres. Elle store (REG_SIZE OCTET) la valeur du
premier argument (toujours un registre) dans le second.

st r4,34 store la valeur de r4 à l’adresse ( PC + (34 % IDX_MOD))
	st r3,r8 copie r3 dans r8
	This op does not modify the carry

	p1 = T_REG
	p2 = T_REG | T_IND
*/

//need to decrease cycles

int	op_st(t_vm *vm, t_thread *PC)
{
	int	param1;
	int	param2;
	int	tmp;

	//assuming the PC->location should be on the opcode
	if (check_params(vm->map[(PC->location + 1) % MEM_SIZE], 1) == REG_CODE)
	{
		tmp = recup_param(vm, (PC->location + 2) % MEM_SIZE, 1);
		if (tmp < 1 || tmp > REG_NUMBER)
			return (0);
		param1 = PC->r[tmp];
		if (check_params(vm->map[(PC->location + 1) % MEM_SIZE], 2) == REG_CODE)
		{
			tmp = recup_param(vm, (PC->location + 1 + 2) % MEM_SIZE, 1);
			if (tmp < 1 || tmp > REG_NUMBER)
				return (0);
			PC->r[tmp] = param1;
			PC->location = (PC->location + 1 + 2 + 1) % MEM_SIZE;
			return (1);
		}
		else if (check_params(vm->map[(PC->location + 1) % MEM_SIZE], 2) == IND_CODE)
		{
			tmp = recup_param(vm, (PC->location + 1 + 2), 2);
			if (param1 < 0)
			{
// undeclared identifier	param1 = ~(-value);
				param1++;
			}
			vm->map[(PC->location + (tmp % IDX_MOD)) % MEM_SIZE] = (param1 >> 24);
			vm->map[(PC->location + 1 + (tmp % IDX_MOD)) % MEM_SIZE] = ((param1 >> 16) & 255);
			vm->map[(PC->location + 2 + (tmp % IDX_MOD)) % MEM_SIZE] = ((param1 >> 8) & 255);
			vm->map[(PC->location + 3 + (tmp % IDX_MOD)) % MEM_SIZE] = (param1 & 255);
			PC->location = (PC->location + 1 + 2 + 2) % IDX_MOD;
			return (1);
		}
		else
			return (0);
	}
	else
		return (0);
}
