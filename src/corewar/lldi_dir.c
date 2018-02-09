/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhadley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 15:59:48 by dhadley           #+#    #+#             */
/*   Updated: 2018/02/09 16:10:33 by dhadley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
 ** Comme ldi sans le %IDX_MOD Cette opération modifie le carry.
 ** ldi = Cette opération modifie le carry. ldi 3,%4,r1 lit IND_SIZE
 ** octets a l’adresse :
 ** (pc + (3 % IDX_MOD)) ajoute 4 à cette valeur. On nommera S cette somme.
 ** On lit REG_SIZE octet à l’adresse (pc + (S % IDX_MOD))
 ** que l’on copie dans r1.
 ** Les paramètres 1 et 2 sont des index.
 **
 ** need to take off cycles
 ** need to modify carry
 */

static int	second_reg(t_vm *vm, t_thread *pc, int param1)
{
	int param2;
	int tmp;
	int sum;

	tmp = recup_param(vm, (pc->location + 1 + 3) % MEM_SIZE, 1);
	if (tmp > REG_NUMBER || tmp < 1)
		return (0);
	param2 = pc->r[tmp];
	sum = param1 + param2;
	tmp = recup_param(vm, (pc->location + sum) % MEM_SIZE, REG_SIZE);
	if (check_params(vm->map[(pc->location + 1) % MEM_SIZE], 3) == REG_CODE)
	{
		param1 = recup_param(vm, (pc->location + 1 + 3 + 1) % MEM_SIZE, 1);
		if (param1 > REG_NUMBER || param1 < 1)
			return (0);
		pc->r[param1] = tmp;
		pc->location = (pc->location + 1 + 3 + 1 + 1) % MEM_SIZE;
		return (1);
	}
	else
		return (0);
}

static int	second_dir(t_vm *vm, t_thread *pc, int param1)
{
	int param2;
	int tmp;
	int sum;

	param2 = recup_param(vm, (pc->location + 1 + 3) % MEM_SIZE, IND_SIZE);
	sum = param1 + param2;
	tmp = recup_param(vm, (pc->location + sum) % MEM_SIZE, REG_SIZE);
	if (check_params(vm->map[(pc->location + 1) % MEM_SIZE], 3) == REG_CODE)
	{
		param1 = recup_param(vm, (pc->location + 1 + 3 + 2) % MEM_SIZE, 1);
		if (param1 > REG_NUMBER || param1 < 1)
			return (0);
		pc->r[param1] = tmp;
		pc->location = (pc->location + 1 + 3 + 2 + 1) % MEM_SIZE;
		return (1);
	}
	else
		return (0);
}

int	op_lldi_dir(t_vm *vm, t_thread *pc)
{
	int	param1;

	param1 = recup_param(vm, (pc->location + 2) % MEM_SIZE, IND_SIZE);
	if (check_params(vm->map[(pc->location + 1) % MEM_SIZE], 2) == DIR_CODE)
	{
		return (second_dir(vm, pc, param1));
	}
	else if (check_params(vm->map[(pc->location + 1) % MEM_SIZE], 2) == REG_CODE)
	{
		return (second_reg(vm, pc, param1));
	}
	return (0);
}