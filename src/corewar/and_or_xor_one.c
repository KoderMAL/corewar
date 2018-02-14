/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or_xor_one.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lramirez <lramirez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 19:19:49 by lramirez          #+#    #+#             */
/*   Updated: 2018/02/14 16:08:55 by lramirez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			get_reg_one(t_vm *vm, t_thread *pc, char code)
{
	int		r;
	t_param	param;

	r = recup_param(vm, pc->location % MEM_SIZE, 1);
	if (r > REG_NUMBER || r < 1)
		return (and_or_xor_exit(pc));
	param.first = pc->r[r];
	if (check_params(vm->map[pc->location], 2) == DIR_CODE)
		pc->location = get_dir_two(vm, (pc->location + 2), &param.second,
			&param.third) + (pc->location + 6) % MEM_SIZE;
	else if (check_params(vm->map[pc->location], 2) == IND_CODE)
		pc->location = get_ind_two(vm, (pc->location + 2), &param.second,
			&param.third) + (pc->location + 4) % MEM_SIZE;
	else if (check_params(vm->map[pc->location], 2) == REG_CODE)
	{
		if (get_reg_two(vm, (pc->location + 2), &param.second,
			&param.third) == -1)
			return (and_or_xor_exit(pc));
		param.second = pc->r[param.second];
		pc->location = (pc->location + 3) % MEM_SIZE;
	}
	else
		return (and_or_xor_exit(pc));
	return (result_in_reg(pc, param, code));
}

int			get_ind_one(t_vm *vm, t_thread *pc, char code)
{
	int		i;
	t_param	param;

	i = recup_param(vm, (pc->location + 1) % MEM_SIZE, 2);
	param.first = (i < 0) ? vm->map[(pc->location - 1 + (i % -IDX_MOD)) %
		MEM_SIZE] : vm->map[(pc->location - 1 + (i % IDX_MOD)) % MEM_SIZE];
	if (check_params(vm->map[pc->location], 2) == DIR_CODE)
		pc->location = get_dir_two(vm, (pc->location + 3), &param.second,
			&param.third) + (pc->location + 7) % MEM_SIZE;
	else if (check_params(vm->map[pc->location], 2) == IND_CODE)
		pc->location = get_ind_two(vm, (pc->location + 3), &param.second,
			&param.third) + (pc->location + 5) % MEM_SIZE;
	else if (check_params(vm->map[pc->location], 2) == REG_CODE)
	{
		if (get_reg_two(vm, (pc->location + 3), &param.second,
			&param.third) == -1)
			return (and_or_xor_exit(pc));
		param.second = pc->r[param.second];
		pc->location = (pc->location + 4) % MEM_SIZE;
	}
	else
		return (and_or_xor_exit(pc));
	return (result_in_reg(pc, param, code));
}

int			get_dir_one(t_vm *vm, t_thread *pc, char code)
{
	t_param	param;

	param.first = recup_param(vm, (pc->location + 1) % MEM_SIZE, 4);
	if (check_params(vm->map[pc->location], 2) == DIR_CODE)
		pc->location = get_dir_two(vm, (pc->location + 5), &param.second,
			&param.third) + (pc->location + 9) % MEM_SIZE;
	else if (check_params(vm->map[pc->location], 2) == IND_CODE)
		pc->location = get_ind_two(vm, (pc->location + 5), &param.second,
			&param.third) + (pc->location + 7) % MEM_SIZE;
	else if (check_params(vm->map[pc->location], 2) == REG_CODE)
	{
		if (get_reg_two(vm, (pc->location + 5), &param.second,
			&param.third) == -1)
			return (and_or_xor_exit(pc));
		param.second = pc->r[param.second];
		pc->location = (pc->location + 6) % MEM_SIZE;
	}
	else
		return (and_or_xor_exit(pc));
	return (result_in_reg(pc, param, code));
}

int			and_or_xor_exit(t_thread *pc)
{
	pc->carry = 0;
	pc->cycles -= 6;
	pc->location = (pc->location + 1) % MEM_SIZE;
	return (0);
}
