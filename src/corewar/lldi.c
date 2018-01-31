/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhadley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 15:17:04 by dhadley           #+#    #+#             */
/*   Updated: 2018/01/29 15:21:59 by dhadley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
Comme ldi sans le %IDX_MOD Cette opération modifie le carry.
ldi = Cette opération modifie le carry. ldi 3,%4,r1 lit IND_SIZE octets a l’adresse :
(PC + (3 % IDX_MOD)) ajoute 4 à cette valeur. On nommera S cette somme. 
On lit REG_SIZE octet à l’adresse (PC + (S % IDX_MOD)) que l’on copie dans r1. 
Les paramètres 1 et 2 sont des index.
*/

//need to take off cycles
//need to modify carry

int	op_lldi(t_vm *vm, t_thread *PC)
{
	int	param1;
	int param2;
	int	sum;
	int	tmp;

	//assuming that the PX->location should be on the opcode
	if (check_params(vm->map[(PC->location + 1) % MEM_SIZE], 1) == IND_CODE)
	{
		tmp = recup_param(vm, (PC->location + 2) % MEM_SIZE, IND_SIZE);
		param1 = recup_param(vm, (PC->location + tmp) % MEM_SIZE, IND_SIZE);
		if (check_params(vm->map[(PC->location + 1) % MEM_SIZE], 2) == DIR_CODE)
		{
			param2 = recup_param(vm, (PC->location + 1 + 3) % MEM_SIZE, IND_SIZE);
			sum = param1 + param2;
			tmp = recup_param(vm, (PC->location + sum) % MEM_SIZE, REG_SIZE);
			if (check_params(vm->map[(PC->location + 1) % MEM_SIZE], 3) == REG_CODE)
			{
				param1 = recup_param(vm, (PC->location + 1 + 3 + 2) % MEM_SIZE, 1);
				if (param1 > REG_NUMBER || param1 < 1)
					return (0);
				PC->r[param1] = tmp;
				PC->location = (PC->location + 1 + 3 + 2 + 1) % MEM_SIZE;
				return (1);
			}
			else
				return (0);
		}
		else if (check_params(vm->map[(PC->location + 1) % MEM_SIZE], 2) == REG_CODE)
		{
			tmp = recup_param(vm, (PC->location + 1 + 3) % MEM_SIZE, 1);
			if (tmp > REG_NUMBER || tmp < 1)
				return (0);
			param2 = PC->r[tmp];
			sum = param1 + param2;
			tmp = recup_param(vm, (PC->location + sum) % MEM_SIZE, REG_SIZE);
			if (check_params(vm->map[(PC->location + 1) % MEM_SIZE], 3) == REG_CODE)
			{
				param1 = recup_param(vm, (PC->location + 1 + 3 + 1) % MEM_SIZE, 1);
				if (param1 > REG_NUMBER || param1 < 1)
					return (0);
				PC->r[param1] = tmp;
				PC->location = (PC->location + 1 + 3 + 1 + 1) % MEM_SIZE;
				return (1);
			}
			else
				return (0);
		}
	}
	else if (check_params(vm->map[(PC->location + 1) % MEM_SIZE], 1) == DIR_CODE)
	{
		param1 = recup_param(vm, (PC->location + 2) % MEM_SIZE, IND_SIZE);
		if (check_params(vm->map[(PC->location + 1) % MEM_SIZE], 2) == DIR_CODE)
		{
			param2 = recup_param(vm, (PC->location + 1 + 3) % MEM_SIZE, IND_SIZE);
			sum = param1 + param2;
			tmp = recup_param(vm, (PC->location + sum) % MEM_SIZE, REG_SIZE);
			if (check_params(vm->map[(PC->location + 1) % MEM_SIZE], 3) == REG_CODE)
			{
				param1 = recup_param(vm, (PC->location + 1 + 3 + 2) % MEM_SIZE, 1);
				if (param1 > REG_NUMBER || param1 < 1)
					return (0);
				PC->r[param1] = tmp;
				PC->location = (PC->location + 1 + 3 + 2 + 1) % MEM_SIZE;
				return (1);
			}
			else
				return (0);
		}
		else if (check_params(vm->map[(PC->location + 1) % MEM_SIZE], 2) == REG_CODE)
		{
			tmp = recup_param(vm, (PC->location + 1 + 3) % MEM_SIZE, 1);
			if (tmp > REG_NUMBER || tmp < 1)
				return (0);
			param2 = PC->r[tmp];
			sum = param1 + param2;
			tmp = recup_param(vm, (PC->location + sum) % MEM_SIZE, REG_SIZE);
			if (check_params(vm->map[(PC->location + 1) % MEM_SIZE], 3) == REG_CODE)
			{
				param1 = recup_param(vm, (PC->location + 1 + 3 + 1) % MEM_SIZE, 1);
				if (param1 > REG_NUMBER || param1 < 1)
					return (0);
				PC->r[param1] = tmp;
				PC->location = (PC->location + 1 + 3 + 1 + 1) % MEM_SIZE;
				return (1);
			}
			else
				return (0);
		}
	}
	else if (check_params(vm->map[(PC->location + 1) % MEM_SIZE], 1) == REG_CODE)
	{
		tmp = recup_param(vm, (PC->location + 2) % MEM_SIZE, 1);
		if (tmp > REG_NUMBER || tmp < 1)
			return (0);
		param1 = PC->r[tmp];
		if (check_params(vm->map[(PC->location + 1) % MEM_SIZE], 2) == DIR_CODE)
		{
			param2 = recup_param(vm, (PC->location + 1 + 2) % MEM_SIZE, IND_SIZE);
			sum = param1 + param2;
			tmp = recup_param(vm, (PC->location + sum) % MEM_SIZE, REG_SIZE);
			if (check_params(vm->map[(PC->location + 1) % MEM_SIZE], 3) == REG_CODE)
			{
				param1 = recup_param(vm, (PC->location + 1 + 2 + 2) % MEM_SIZE, 1);
				if (param1 > REG_NUMBER || param1 < 1)
					return (0);
				PC->r[param1] = tmp;
				PC->location = (PC->location + 1 + 2 + 2 + 1) % MEM_SIZE;
				return (1);
			}
			else
				return (0);
		}
		else if (check_params(vm->map[(PC->location + 1) % MEM_SIZE], 2) == REG_CODE)
		{
			tmp = recup_param(vm, (PC->location + 1 + 2) % MEM_SIZE, 1);
			if (tmp > REG_NUMBER || tmp < 1)
				return (0);
			param2 = PC->r[tmp];
			sum = param1 + param2;
			tmp = recup_param(vm, (PC->location + sum) % MEM_SIZE, REG_SIZE);
			if (check_params(vm->map[(PC->location + 1) % MEM_SIZE], 3) == REG_CODE)
			{
				param1 = recup_param(vm, (PC->location + 1 + 2 + 1) % MEM_SIZE, 1);
				if (param1 > REG_NUMBER || param1 < 1)
					return (0);
				PC->r[param1] = tmp;
				PC->location = (PC->location + 1 + 2 + 1 + 1) % MEM_SIZE;
				return (1);
			}
			else
				return (0);
		}
	}
	else
		return (0);
}
