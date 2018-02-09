/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti_reg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhadley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 16:38:42 by dhadley           #+#    #+#             */
/*   Updated: 2018/02/09 16:58:11 by dhadley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
 ** sti r2,%4,%5 sti copie REG_SIZE octet de r2 a l’adresse (4 + 5)
 ** Les paramètres 2 et 3 sont des index.
 ** Si les paramètres 2 ou 3 sont des registres, on utilisera leur
 ** contenu comme un index.
 **
 ** p1 = T_REG
 ** p2 = T_REG | T_DIR | T_IND
 ** p3 = T_DIR | T_REG
 **
 ** this function does not modify the carry
 */

//need to remove cycles

static int	third_reg(t_vm *vm, t_thread *pc, int reg, int tmp, int param1)
{
	int param2;

	tmp = recup_param(vm, (pc->location + 1 + 1 + 1 + 1) % MEM_SIZE, 1);
	if (tmp < 1 || tmp > REG_SIZE)
		return (0);
	param2 = pc->r[tmp];
	tmp = param1 + param2;
	if (reg < 0)
	{
		reg = ~(-reg);
		reg++;
	}
	vm->map[(pc->location + (tmp % IDX_MOD)) % MEM_SIZE] = (reg >> 24);
	vm->map[(pc->location + 1 + (tmp % IDX_MOD)) % MEM_SIZE] = ((reg >> 16) & 255);
	vm->map[(pc->location + 2 + (tmp % IDX_MOD)) % MEM_SIZE] = ((reg >> 8) & 255);
	vm->map[(pc->location + 3 + (tmp % IDX_MOD)) % MEM_SIZE] = (reg & 255);
	pc->location = (pc->location + 1 + 1 + 1 + 1 + 1) % MEM_SIZE;
	return (1);
}

static int	third_dir(t_vm *vm, t_thread *pc, int reg, int tmp, int param1)
{
	int param2;

	param2 = recup_param(vm, (pc->location + 1 + 1 + 1 + 1) % MEM_SIZE, 2);
	tmp = param1 + param2;
	if (reg < 0)
	{
		reg = ~(-reg);
		reg++;
	}
	vm->map[(pc->location + (tmp % IDX_MOD)) % MEM_SIZE] = (reg >> 24);
	vm->map[(pc->location + 1 + (tmp % IDX_MOD)) % MEM_SIZE] = ((reg >> 16) & 255);
	vm->map[(pc->location + 2 + (tmp % IDX_MOD)) % MEM_SIZE] = ((reg >> 8) & 255);
	vm->map[(pc->location + 3 + (tmp % IDX_MOD)) % MEM_SIZE] = (reg & 255);
	pc->location = (pc->location + 1 + 1 + 1 + 1 + 2) % MEM_SIZE;
	return (1);
}

int	op_sti_reg(t_vm *vm, t_thread *pc)
{
	int	reg;
	int param1;
	int tmp;

	tmp = recup_param(vm, (pc->location + 2) % MEM_SIZE, 1);
	if (tmp < 1 || tmp > REG_NUMBER)
		return (0);
	reg = pc->r[tmp];
	tmp = recup_param(vm, (pc->location + 1 + 1 + 1) % MEM_SIZE, 1);
	if (tmp < 1 || tmp > REG_NUMBER)
		return (0);
	param1 = pc->r[tmp];
	if (check_params(vm->map[(pc->location + 1) % MEM_SIZE], 3) == DIR_CODE)
	{
		return (third_dir(vm, pc, reg, tmp, param1));
	}
	else if (check_params(vm->map[(pc->location + 1) % MEM_SIZE], 3) == REG_CODE)
	{
		return (third_reg(vm, pc, reg, tmp, param1));
	}
	else
		return (0);
}
