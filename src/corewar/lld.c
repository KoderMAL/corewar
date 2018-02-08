/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 11:04:33 by dhadley           #+#    #+#             */
/*   Updated: 2018/02/08 12:55:21 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** comme ld sans le %IDX_MOD Cette opération modifie le carry.
** ld = Cette instruction prend 2 paramètres, le deuxième est forcément un
** registre (pas le pc).
** Elle load la valeur du premier paramètre dans le registre. Cette opération
** modifie le carry.
** ld 34,r3 charge les REG_SIZE octets à partir de l’adresse
** (pc + (34 % IDX_MOD)) dans le registre r3.
**
** need to modify the carry
** need to take off cycles from the pc cycle to die
*/

#include "vm.h"

static int	op_lld_dir(t_vm *vm, t_thread *pc)
{
	int	param1;
	int param2;

	param1 = recup_param(vm, (pc->location + 2) % MEM_SIZE, 4);
	param2 = recup_param(vm, (pc->location + 2 + 4) % MEM_SIZE, 1);
	if (param2 > REG_NUMBER || param2 < 1)
		param2 = 0;
	pc->r[param2] = param1;
	pc->location = (pc->location + 1 + 1 + 4 + 1) % MEM_SIZE;
	return (1);
}

static int	op_lld_ind(t_vm *vm, t_thread *pc)
{
	int	param1;
	int param2;
	int tmp_ind;

	tmp_ind = recup_param(vm, (pc->location + 2) % MEM_SIZE, 2);
	param1 = recup_param(vm, (pc->location + tmp_ind) % MEM_SIZE, REG_SIZE);
	param2 = recup_param(vm, (pc->location + 2 + 2) % MEM_SIZE, 1);
	if (param2 > REG_NUMBER || param2 < 1)
		param2 = 0;
	pc->r[param2] = param1;
	pc->location = (pc->location + 1 + 1 + 2 + 1) % MEM_SIZE;
	return (1);
}

int			op_lld(t_vm *vm, t_thread *pc)
{
	int	param_type;

	param_type = check_params(vm->map[(pc->location + 1) % MEM_SIZE], 1);
	if (param_type == DIR_CODE)
		return (op_lld_dir(vm, pc));
	else if (param_type == IND_CODE)
		return (op_lld_ind(vm, pc));
	return (1);
}
