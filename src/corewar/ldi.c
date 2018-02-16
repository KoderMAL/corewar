/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 11:22:42 by dhadley           #+#    #+#             */
/*   Updated: 2018/02/15 13:25:01 by dhadley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Cette opération modifie le carry. ldi 3,%4,r1 lit IND_SIZE octets
** a l’adresse :
** (pc + (3 % IDX_MOD)) ajoute 4 à cette valeur. On nommera S cette somme.
** On lit REG_SIZE octet à l’adresse (pc + (S % IDX_MOD)) que l’on
** copie dans r1.
** Les paramètres 1 et 2 sont des index.
**
** need to take off cycles
** need to modify carry
*/

static int	second_reg(t_vm *vm, t_thread *pc, int tmp, int param1)
{
	int sum;
	int param2;
	int	i;

	tmp = recup_param(vm, (pc->location + 1 + 3) % MEM_SIZE, 1);
	if (tmp > REG_NUMBER || tmp < 1)
		return (op_exit(pc, 25, false));
	param2 = pc->r[tmp];
	sum = param1 + param2;
	if (sum < 0)
		i = pc->location + (sum % -IDX_MOD);
	else
		i = pc->location + (sum % IDX_MOD);
	tmp = recup_param(vm, i % MEM_SIZE, REG_SIZE);
	if (check_params(vm->map[(pc->location + 1) % MEM_SIZE], 3) == REG_CODE)
	{
		param1 = recup_param(vm, (pc->location + 1 + 3 + 1) % MEM_SIZE, 1);
		if (param1 > REG_NUMBER || param1 < 1)
			return (op_exit(pc, 25, false));
		pc->r[param1] = tmp;
		return (op_success(pc, 25, 1 + 2 + 1 + 1, false));
	}
	else
		return (0);
}

static int	second_dir(t_vm *vm, t_thread *pc, int tmp, int param1)
{
	int sum;
	int param2;
	int	i;

	param2 = recup_param(vm, (pc->location + 1 + 3) % MEM_SIZE, IND_SIZE);
	sum = param1 + param2;
	if (sum < 0)
		i = pc->location + (sum % -IDX_MOD);
	else
		i = pc->location + (sum % IDX_MOD);
	tmp = recup_param(vm, i % MEM_SIZE, REG_SIZE);
	if (check_params(vm->map[(pc->location + 1) % MEM_SIZE], 3) == REG_CODE)
	{
		param1 = recup_param(vm, (pc->location + 1 + 3 + 2) % MEM_SIZE, 1);
		if (param1 > REG_NUMBER || param1 < 1)
			return (op_exit(pc, 25, false));
		pc->r[param1] = tmp;
		return (op_success(pc, 25, 1 + 3 + 2 + 1, false));
	}
	else
		return (op_exit(pc, 25, false));
}

int			op_ldi(t_thread *pc)
{
	int	param1;
	int	tmp;
	int	i;
	t_vm *vm;

	vm = pc->vm;
	if (check_params(vm->map[(pc->location + 1) % MEM_SIZE], 1) == IND_CODE)
	{
		tmp = recup_param(vm, (pc->location + 2) % MEM_SIZE, IND_SIZE);
		if (tmp < 0)
			i = pc->location + (tmp % -IDX_MOD);
		else
			i = pc->location + (tmp % IDX_MOD);
		param1 = recup_param(vm, i % MEM_SIZE, IND_SIZE);
		if (check_params(vm->map[(pc->location + 1) % MEM_SIZE], 2) == DIR_CODE)
			return (second_dir(vm, pc, tmp, param1));
		else if (check_params(vm->map[(pc->location + 1) % MEM_SIZE], 2)
				== REG_CODE)
			return (second_reg(vm, pc, tmp, param1));
	}
	else if (check_params(vm->map[(pc->location + 1) % MEM_SIZE], 1)
			== DIR_CODE)
		return (op_ldi_dir(pc));
	else if (check_params(vm->map[(pc->location + 1) % MEM_SIZE], 1)
			== REG_CODE)
		return (op_ldi_reg(pc));
	return (op_exit(pc, 25, false));
}
