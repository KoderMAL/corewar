/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 16:50:31 by dhadley           #+#    #+#             */
/*   Updated: 2018/02/16 15:55:43 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Cette instruction prend 2 paramètres, le deuxième est forcément un
** registre (pas le pc).
** Elle load la valeur du premier paramètre dans le registre.
** Cette opération modifie le carry.
** ld 34,r3 charge les REG_SIZE octets à partir de l’adresse
** (pc + (34 % IDX_MOD)) dans le registre r3.
*/

static int	op_ld_dir(t_vm *vm, t_thread *pc)
{
	int	param1;
	int param2;

	param1 = recup_param(vm, (pc->location + 2) % MEM_SIZE, 4);
	param2 = recup_param(vm, (pc->location + 2 + 4) % MEM_SIZE, 1);
	print_nbr(vm, param1, 0);
	print_str(vm, " ", 0);
	print_reg(vm, param2, 1);
	if (param2 > REG_NUMBER || param2 < 1)
		return (op_exit(pc, 5, true));
	pc->r[param2] = param1;
	return (op_success(pc, 5, 2 + 4 + 1, true));
}

static int	op_ld_ind(t_vm *vm, t_thread *pc)
{
	int	param1;
	int param2;
	int tmp_ind;
	int	i;

	tmp_ind = recup_param(vm, (pc->location + 2) % MEM_SIZE, 2);
	if (tmp_ind < 0)
		i = pc->location + (tmp_ind % -IDX_MOD);
	else
		i = pc->location + (tmp_ind % IDX_MOD);
	param1 = recup_param(vm, i % MEM_SIZE, REG_SIZE);
	param2 = recup_param(vm, (pc->location + 2 + 2) % MEM_SIZE, 1);
	print_nbr(vm, param1, 0);
	print_str(vm, " ", 0);
	print_reg(vm, param2, 1);
	if (param2 > REG_NUMBER || param2 < 1)
		return (op_exit(pc, 5, true));
	pc->r[param2] = param1;
	return (op_success(pc, 5, 2 + 2 + 1, true));
}

void		op_ld(t_thread *pc)
{
	int	param_type;
	t_vm *vm;

	vm = pc->vm;
	print_instruction_start(vm, pc);
	print_str(vm, "ld ", 0);
	param_type = check_params(vm->map[(pc->location + 1) % MEM_SIZE], 1);
	/*if (param_type == DIR_CODE)
		return (op_ld_dir(vm, pc));
	else if (param_type == IND_CODE)
		return (op_ld_ind(vm, pc));
	return (op_exit(pc, 5, true));*/
}
