/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 14:39:27 by lramirez          #+#    #+#             */
/*   Updated: 2018/02/08 12:25:29 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** op_or détermine le type du premier paramètre (T_DIR, T_IND ou T_REG).
** Execute la fonction correspondante.
** Chaque fonction récupère les paramètres un à un selon leur type.
** Déplace le PC à la fin du dernier paramètre récupéré.
** Place le résultat de [param_1 | param_2] dans param_3.
** Met le carry à 1 et décrémente le process de 6 cycles (coût d'un or).
*/

int		op_or_exit(t_thread *pc)
{
	pc->carry = 0;
	pc->cycles -= 6;
	pc->location = (pc->location + 1) % MEM_SIZE;
	return (0);
}

int		op_or_reg(t_vm *vm, t_thread *pc)
{
	int		param_1;
	int		param_2;
	int		reg;

	if ((reg = recup_param(vm, (pc->location + 1) % MEM_SIZE, 1)) > REG_NUMBER)
		return (op_or_exit(pc));
	param_1 = pc->r[reg];
	if (check_params(vm->map[pc->location], 2) == DIR_CODE)
	{
		param_2 = recup_param(vm, (pc->location + 2) % MEM_SIZE, 4);
		reg = recup_param(vm, (pc->location + 6) % MEM_SIZE, 1);
		pc->location = (pc->location + 7) % MEM_SIZE;
	}
	else if (check_params(vm->map[pc->location], 2) == IND_CODE)
	{
		param_2 = vm->map[(pc->location - 1 + (recup_param(vm, (pc->location + 2) % MEM_SIZE, 2) % IDX_MOD)) % MEM_SIZE];
		reg = recup_param(vm, (pc->location + 4) % MEM_SIZE, 1);
		pc->location = (pc->location + 5) % MEM_SIZE;
	}
	else if (check_params(vm->map[pc->location], 2) == REG_CODE)
	{
		if ((reg = recup_param(vm, (pc->location + 2) % MEM_SIZE, 1)) > REG_NUMBER)
			return (op_or_exit(pc));
		param_2 = pc->r[reg];
		reg = recup_param(vm, (pc->location + 3) % MEM_SIZE, 1);
		pc->location = (pc->location + 4) % MEM_SIZE;
	}
	else
		return (op_or_exit(pc));
	if (reg > REG_NUMBER)
		return (op_or_exit(pc));
	pc->r[reg] = param_1 | param_2;
	pc->carry = 1;
	pc->cycles -= 6;
	return (1);
}

int		op_or_ind(t_vm *vm, t_thread *pc)
{
	int		param_1;
	int		param_2;
	int		reg;

	param_1 = vm->map[(pc->location - 1 + (recup_param(vm, (pc->location + 1) % MEM_SIZE, 2) % IDX_MOD)) % MEM_SIZE];
	if (check_params(vm->map[pc->location], 2) == DIR_CODE)
	{
		param_2 = recup_param(vm, (pc->location + 3) % MEM_SIZE, 4);
		reg = recup_param(vm, (pc->location + 7) % MEM_SIZE, 1);
		pc->location = (pc->location + 8) % MEM_SIZE;
	}
	else if (check_params(vm->map[pc->location], 2) == IND_CODE)
	{
		param_2 = vm->map[(pc->location - 1 + (recup_param(vm, (pc->location + 3) % MEM_SIZE, 2) % IDX_MOD)) % MEM_SIZE];
		reg = recup_param(vm, (pc->location + 5) % MEM_SIZE, 1);
		pc->location = (pc->location + 6) % MEM_SIZE;
	}
	else if (check_params(vm->map[pc->location], 2) == REG_CODE)
	{
		if ((reg = recup_param(vm, (pc->location + 3) % MEM_SIZE, 1)) > REG_NUMBER)
			return (op_or_exit(pc));
		param_2 = pc->r[reg];
		reg = recup_param(vm, (pc->location + 4) % MEM_SIZE, 1);
		pc->location = (pc->location + 5) % MEM_SIZE;
	}
	else
		return (op_or_exit(pc));
	if (reg > REG_NUMBER)
		return (op_or_exit(pc));
	pc->r[reg] = param_1 | param_2;
	pc->carry = 1;
	pc->cycles -= 6;
	return (1);
}

int		op_or_dir(t_vm *vm, t_thread *pc)
{
	int		param_1;
	int		param_2;
	int		reg;

	param_1 = recup_param(vm, (pc->location + 1) % MEM_SIZE, 4);
	if (check_params(vm->map[pc->location], 2) == DIR_CODE)
	{
		param_2 = recup_param(vm, (pc->location + 5) % MEM_SIZE, 4);
		reg = recup_param(vm, (pc->location + 9) % MEM_SIZE, 1);
		pc->location = (pc->location + 10) % MEM_SIZE;
	}
	else if (check_params(vm->map[pc->location], 2) == IND_CODE)
	{
		param_2 = vm->map[(pc->location - 1 + (recup_param(vm, (pc->location + 2) % MEM_SIZE, 2) % IDX_MOD)) % MEM_SIZE];
		reg = recup_param(vm, (pc->location + 7) % MEM_SIZE, 1);
		pc->location = (pc->location + 8) % MEM_SIZE;
	}
	else if (check_params(vm->map[pc->location], 2) == REG_CODE)
	{
		if ((reg = recup_param(vm, (pc->location + 5) % MEM_SIZE, 1)) > REG_NUMBER)
			return (op_or_exit(pc));
		param_2 = pc->r[reg];
		reg = recup_param(vm, (pc->location + 6) % MEM_SIZE, 1);
		pc->location = (pc->location + 7) % MEM_SIZE;
	}
	else
		return (op_or_exit(pc));
	if (reg > REG_NUMBER)
		return (op_or_exit(pc));
	pc->r[reg] = param_1 | param_2;
	pc->carry = 1;
	pc->cycles -= 6;
	return (1);
}

int		op_or(t_vm *vm, t_thread *pc)
{
	int	param_type;

	param_type = check_params(vm->map[pc->location], 1);
	pc->location = (pc->location + 1) % MEM_SIZE;
	if (param_type == DIR_CODE)
		return (op_or_dir(vm, pc));
	else if (param_type == IND_CODE)
		return (op_or_ind(vm, pc));
	else if (param_type == REG_CODE)
		return (op_or_reg(vm, pc));
	else
		return (op_or_exit(pc));
}
