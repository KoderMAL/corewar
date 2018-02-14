/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti_reg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhadley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 16:38:42 by dhadley           #+#    #+#             */
/*   Updated: 2018/02/13 18:53:26 by dhadley          ###   ########.fr       */
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
*/

static void	print_in_mem(t_vm *vm, t_thread *pc, int tmp, int reg)
{
	int i;

	if (tmp < 0)
		i = tmp % -IDX_MOD;
	else
		i = tmp % IDX_MOD;
	vm->map[(pc->location + i) % MEM_SIZE] = (reg >> 24);
	vm->map[(pc->location + 1 + i) % MEM_SIZE] =
		((reg >> 16) & 255);
	vm->map[(pc->location + 2 + i) % MEM_SIZE] =
		((reg >> 8) & 255);
	vm->map[(pc->location + 3 + i) % MEM_SIZE] = (reg & 255);

}

static int	third_reg(t_vm *vm, t_thread *pc, int reg, int param1)
{
	int	param2;
	int	tmp;

	tmp = recup_param(vm, (pc->location + 1 + 1 + 1 + 1) % MEM_SIZE, 1);
	if (tmp < 1 || tmp > REG_SIZE)
		return (op_exit(pc, 25, false));
	param2 = pc->r[tmp];
	tmp = param1 + param2;
	if (reg < 0)
	{
		reg = ~(-reg);
		reg++;
	}
	print_in_mem(vm, pc, tmp, reg);
	return (op_success(pc, 25, 1 + 1 + 1 + 1 + 1, false));
}

static int	third_dir(t_vm *vm, t_thread *pc, int reg, int param1)
{
	int	param2;
	int	tmp;

	param2 = recup_param(vm, (pc->location + 1 + 1 + 1 + 1) % MEM_SIZE, 2);
	tmp = param1 + param2;
	if (reg < 0)
	{
		reg = ~(-reg);
		reg++;
	}
	print_in_mem(vm, pc, tmp, reg);
	return (op_success(pc, 25, 1 + 1 + 1 + 1 + 2, false));
}

int			op_sti_reg(t_vm *vm, t_thread *pc)
{
	int	reg;
	int param1;
	int tmp;

	tmp = recup_param(vm, (pc->location + 2) % MEM_SIZE, 1);
	if (tmp < 1 || tmp > REG_NUMBER)
		return (op_exit(pc, 25, false));
	reg = pc->r[tmp];
	tmp = recup_param(vm, (pc->location + 1 + 1 + 1) % MEM_SIZE, 1);
	if (tmp < 1 || tmp > REG_NUMBER)
		return (op_exit(pc, 25, false));
	param1 = pc->r[tmp];
	if (check_params(vm->map[(pc->location + 1) % MEM_SIZE], 3)
			== DIR_CODE)
		return (third_dir(vm, pc, reg, param1));
	else if (check_params(vm->map[(pc->location + 1) % MEM_SIZE], 3)
			== REG_CODE)
		return (third_reg(vm, pc, reg, param1));
	return (op_exit(pc, 25, false));
}
