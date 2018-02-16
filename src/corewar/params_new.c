/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lramirez <lramirez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 13:20:49 by lramirez          #+#    #+#             */
/*   Updated: 2018/02/16 16:04:07 by lramirez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int				shift_loc(t_thread *pc, int amount)
{
	return ((pc->location + amount) % MEM_SIZE);
}

int				get_byte_at(t_thread *pc, int amount, bool indent)
{
	if (indent)
		return (pc->vm->map[shift_loc(pc, pc->indent + amount)]);
	else
		return (pc->vm->map[shift_loc(pc, amount)]);
}

int				get_code(unsigned char byte, int number)
{
	int		code;

	code = (byte >> (8 - number * 2)) & 3;
	if (code == DIR_CODE || code == IND_CODE || code == REG_CODE)
		return (code);
	return (0);
}

int				get_bytes(t_thread *pc, int bytes)
{
	int		param;

	param = 0;
	if (bytes == 1)
		param = get_byte_at(pc, 0, true);
	else if (bytes == 2)
	{
		param = get_byte_at(pc, 0, true) << 8 | get_byte_at(pc, 1, true);
		if (param > 0x7FFF)
			param = (param | 0xFFFF0000);
	}
	else if (bytes == 4)
	{
		param = get_byte_at(pc, 0, true) << 24 | get_byte_at(pc, 1, true) << 16 |
			get_byte_at(pc, 2, true) << 8 | get_byte_at(pc, 3, true);
		param = (param < 0) ? shift_loc(pc, (param % -IDX_MOD)) :
		shift_loc(pc, (param % IDX_MOD));
	}
	pc->indent += bytes;
	return (param);
}

int            get_param(t_thread *pc, int param_code)
{
	int        param;
	
	param = 0;
	if (param_code == 1)
	{
		param = get_bytes(pc, 1);
		if (param < 1 || param > REG_NUMBER)
			return (0);
		pc->indent += 1;
	}
	else if (param_code == 2 || param_code == 0)
		param = get_bytes(pc, 2);
	else if (param_code == 3)
		param = get_bytes(pc, 4);
	return (param);
}

int            get_params(t_thread *pc, t_op *op)
{
	int        param;
	int        param_code;
	
	pc->cycles -= op->n_cycles;
	param = 0;
	if (op->has_pcode)
	{
		pc->indent = 2;
		pc->bytecode = get_byte_at(pc, 1, false);
	}
	else
		pc->indent = 1;
	while (param < op->n_arg)
	{
		param_code =  op->has_pcode ? get_code(pc->bytecode, param + 1) : 0;
		if (param_code != op->arg_type[param] ||
			!(pc->params[param] = get_param(pc, param_code)))
			return (0);
		pc->params_type[param] = param_code;
		param++;
	}
	return (1);
}
