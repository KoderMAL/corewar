/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 13:20:49 by lramirez          #+#    #+#             */
/*   Updated: 2018/02/21 17:08:39 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int				get_code(unsigned char byte, int number)
{
	int		code;

	code = (byte >> (8 - number * 2)) & 3;
	if (code == DIR_CODE)
		return T_DIR;
	if (code == IND_CODE)
		return T_IND;
	if (code == REG_CODE)
		return T_REG;
	return (0);
}

int            get_param(t_thread *pc, int param_code)
{
	int	param;
	
	param = 0;
	if (param_code == T_REG)
	{
		param = get_bytes(pc, pc->shift, 1);
		if (param < 1 || param > REG_NUMBER)
			return (0);
		pc->shift += 1;
	}
	else if (param_code == T_IND || param_code == 0)
	{
		param = get_bytes(pc, pc->shift, 2);
		pc->shift += 2;
	}
	else if (param_code == T_DIR)
	{
		param = get_bytes(pc, pc->shift, 4);
		pc->shift += 4;
	}
	return (param);
}

int            get_params(t_thread *pc, const t_op *op)
{
	int        param;
	int        param_code;
	
	pc->cycles -= op->n_cycles;
	param = 0;
	pc->shift = 0;
	if (op->has_pcode)
		pc->bytecode = get_byte_at(pc, 1);
	pc->shift += 1 + op->has_pcode;
	while (param < op->n_arg)
	{
		param_code =  op->has_pcode ? get_code(pc->bytecode, param + 1) : 0;
		if ((param_code & op->arg_type[param]) == 0 ||
			!(pc->params[param] = get_param(pc, param_code)))
			return (0);
		pc->params_type[param] = param_code;
		param++;
	}
	return (1);
}
