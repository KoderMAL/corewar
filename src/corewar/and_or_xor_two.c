/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or_xor_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lramirez <lramirez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 20:40:56 by lramirez          #+#    #+#             */
/*   Updated: 2018/02/14 14:48:43 by lramirez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		get_dir_two(t_vm *vm, int location, int *param_2, int *reg)
{
	*param_2 = recup_param(vm, location % MEM_SIZE, 4);
	*reg = recup_param(vm, (location + 4) % MEM_SIZE, 1);
	return (0);
}

int		get_ind_two(t_vm *vm, int location, int *param_2, int *reg)
{
	int		i;

	i = recup_param(vm, location % MEM_SIZE, 2);
	if (i < 0)
		*param_2 = vm->map[(location - 1 + (i % -IDX_MOD)) % MEM_SIZE];
	else
		*param_2 = vm->map[(location - 1 + (i % IDX_MOD)) % MEM_SIZE];
	*reg = recup_param(vm, (location + 3) % MEM_SIZE, 1);
	return (0);
}

int		get_reg_two(t_vm *vm, int location, int *param_2, int *reg)
{
	int		r;

	r = recup_param(vm, location % MEM_SIZE, 1);
	if (r > REG_NUMBER || r < 1)
		return (-1);
	*param_2 = r;
	*reg = recup_param(vm, (location + 1) % MEM_SIZE, 1);
	return (0);
}

int		result_in_reg(t_thread *pc, t_param param, char code)
{
	if (param.third > REG_NUMBER || param.third < 1)
		return (and_or_xor_exit(pc));
	if (code == 0)
		pc->r[param.third] = param.first & param.second;
	else if (code == 1)
		pc->r[param.third] = param.first | param.second;
	else if (code == 2)
		pc->r[param.third] = param.first ^ param.second;
	pc->carry = 1;
	pc->cycles -= 6;
	return (1);
}
