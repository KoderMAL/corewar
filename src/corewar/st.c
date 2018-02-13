/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 15:23:39 by dhadley           #+#    #+#             */
/*   Updated: 2018/02/13 16:26:49 by dhadley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Cette instruction prend 2 paramètres. Elle store (REG_SIZE OCTET)
** la valeur du
** premier argument (toujours un registre) dans le second.
**
** st r4,34 store la valeur de r4 à l’adresse ( pc + (34 % IDX_MOD))
** st r3,r8 copie r3 dans r8
** This op does not modify the carry
*/

static int	op_st_reg(t_vm *vm, t_thread *pc, int param1)
{
	int	tmp;

	tmp = recup_param(vm, (pc->location + 1 + 2) % MEM_SIZE, 1);
	if (tmp < 1 || tmp > REG_NUMBER)
		return (op_exit(pc, 5, false));
	pc->r[tmp] = param1;
	return (op_success(pc, 5, 1 + 2 + 1, false));
}

static int	op_st_ind(t_vm *vm, t_thread *pc, int param1)
{
	int	tmp;
	int	i;

	printf("passing st\n");
	tmp = recup_param(vm, (pc->location + 1 + 2), 2);
	printf("where tmp = %d\n", tmp);
	if (param1 < 0)
	{
		param1 = ~(-param1);
		param1++;
	}
	if (tmp < 0)
		i = pc->location + (tmp % -IDX_MOD);
	else
		i = pc->location + (tmp % IDX_MOD);
	vm->map[i % MEM_SIZE] = (param1 >> 24);
	vm->map[(i + 1) % MEM_SIZE] = ((param1 >> 16) & 255);
	vm->map[(i + 2) % MEM_SIZE] = ((param1 >> 8) & 255);
	vm->map[(i + 3) % MEM_SIZE] = (param1 & 255);
	return (op_success(pc, 5, 1 + 2 + 2, false));
}

int			op_st(t_vm *vm, t_thread *pc)
{
	int	param1;
	int	tmp;
	int	param_type;

	if (check_params(vm->map[(pc->location + 1) % MEM_SIZE], 1) == REG_CODE)
	{
		tmp = recup_param(vm, (pc->location + 2) % MEM_SIZE, 1);
		if (tmp < 1 || tmp > REG_NUMBER)
			return (op_exit(pc, 5, false));
		param1 = pc->r[tmp];
		param_type = check_params(vm->map[(pc->location + 1) % MEM_SIZE], 2);
		if (param_type == REG_CODE)
			return (op_st_reg(vm, pc, param1));
		else if (param_type == IND_CODE)
			return (op_st_ind(vm, pc, param1));
	}
	return (op_exit(pc, 5, false));
}
