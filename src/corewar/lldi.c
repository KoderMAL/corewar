/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 15:17:04 by dhadley           #+#    #+#             */
/*   Updated: 2018/02/13 12:59:56 by dhadley          ###   ########.fr       */
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
 */

static int	second_reg(t_vm *vm, t_thread *pc, int param1, int tmp)
{
	int	param2;
	int	sum;

	tmp = recup_param(vm, (pc->location + 1 + 3) % MEM_SIZE, 1);
	if (tmp > REG_NUMBER || tmp < 1)
		return (op_exit(pc, 50, true));
	param2 = pc->r[tmp];
	sum = param1 + param2;
	tmp = recup_param(vm, (pc->location + sum) % MEM_SIZE, REG_SIZE);
	if (check_params(vm->map[(pc->location + 1) % MEM_SIZE], 3) == REG_CODE)
	{
		param1 = recup_param(vm, (pc->location + 1 + 3 + 1) % MEM_SIZE, 1);
		if (param1 > REG_NUMBER || param1 < 1)
			return (op_exit(pc, 50, true));
		pc->r[param1] = tmp;
		return (op_success(pc, 50, 1 + 3 + 1 + 1, true));
	}
	return (op_exit(pc, 50, true));
}

static int	second_dir(t_vm *vm, t_thread *pc, int param1, int tmp)
{
	int sum;
	int param2;

	param2 = recup_param(vm, (pc->location + 1 + 3) % MEM_SIZE, IND_SIZE);
	sum = param1 + param2;
	tmp = recup_param(vm, (pc->location + sum) % MEM_SIZE, REG_SIZE);
	if (check_params(vm->map[(pc->location + 1) % MEM_SIZE], 3) == REG_CODE)
	{
		param1 = recup_param(vm, (pc->location + 1 + 3 + 2) % MEM_SIZE, 1);
		if (param1 > REG_NUMBER || param1 < 1)
			return (op_exit(pc, 50, true));
		pc->r[param1] = tmp;
		return (op_success(pc, 50, 1 + 3 + 2 + 1, true));
	}
	return (op_exit(pc, 50, true));
}

int			op_lldi(t_vm *vm, t_thread *pc)
{
	int	param1;
	int	tmp;

	if (check_params(vm->map[(pc->location + 1) % MEM_SIZE], 1) == IND_CODE)
	{
		tmp = recup_param(vm, (pc->location + 2) % MEM_SIZE, IND_SIZE);
		param1 = recup_param(vm, (pc->location + tmp) % MEM_SIZE, IND_SIZE);
		if (check_params(vm->map[(pc->location + 1) % MEM_SIZE], 2) == DIR_CODE)
			return (second_dir(vm, pc, param1, tmp));
		else if (check_params(vm->map[(pc->location + 1) % MEM_SIZE], 2)
				== REG_CODE)
			return (second_reg(vm, pc, param1, tmp));
	}
	else if (check_params(vm->map[(pc->location + 1) % MEM_SIZE], 1)
			== DIR_CODE)
		return (op_lldi_dir(vm, pc));
	else if (check_params(vm->map[(pc->location + 1) % MEM_SIZE], 1)
			== REG_CODE)
		return (op_lldi_reg(vm, pc));
	return (op_exit(pc, 50, true));
}
