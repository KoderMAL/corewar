/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lramirez <lramirez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 13:20:49 by lramirez          #+#    #+#             */
/*   Updated: 2018/02/24 22:09:17 by lramirez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int				get_code(unsigned char byte, int number)
{
	int		code;

	code = (byte >> (8 - number * 2)) & 3;
	if (code == DIR_CODE)
		return (T_DIR);
	if (code == IND_CODE)
		return (T_IND);
	if (code == REG_CODE)
		return (T_REG);
	return (0);
}

int				get_param(t_thread *pc, int param_code, int *param, int *shift)
{
	*param = 0;
	if (param_code == T_REG)
	{
		*param = get_bytes(pc, *shift, 1);
		if (*param < 1 || *param > REG_NUMBER)
			return (0);
		*shift += 1;
	}
	else if (param_code == T_IND || param_code == 0)
	{
		*param = get_bytes(pc, *shift, 2);
		*shift += 2;
	}
	else if (param_code == T_DIR)
	{
		*param = get_bytes(pc, *shift, 4);
		*shift += 4;
	}
	else
		return (0);
	return (1);
}

int				get_params(t_thread *pc, const t_op *op)
{
	int	param;
	int	param_code;
	int err;
	int	shift;

	err = 0;
	pc->cycles -= op->n_cycles;
	param = 0;
	pc->shift = 0;
	if (op->has_pcode)
		pc->bytecode = get_byte_at(pc, 1);
	pc->shift += 1 + op->has_pcode;
	shift = pc->shift;
	if (op->has_pcode)
	{
		while (param < 4)
		{
			pc->params_type[param] = 0;
			param_code = get_code(pc->bytecode, param + 1);
			if ((param_code & op->arg_type[param]) == 0 && param < op->n_arg)
			{
				err = 1;
				//param++;
				//continue ;
			}
			if (param_code == T_REG)
				pc->shift++;
			else if (param_code == T_IND)
				pc->shift += 2;
			else if (param_code == T_DIR)
			{
				if (op->has_idx)
					pc->shift += 2;
				else
					pc->shift += 4;
			}
			pc->params_type[param] = param_code;
			param++;
		}
	}
	else
	{
		param_code = op->arg_type[0];
		if (param_code == T_REG)
			pc->shift++;
		else if (param_code == T_IND)
			pc->shift += 2;
		else if (param_code == T_DIR)
		{
			if (op->has_idx)
				pc->shift += 2;
			else
				pc->shift += 4;
		}
		pc->params_type[0] = param_code;
	}
	if (err)
		return(0);
	param = 0;
	while (param < op->n_arg)
	{
		param_code = pc->params_type[param];
		if (param_code == T_DIR && op->has_idx)
			param_code = T_IND;
		get_param(pc, param_code, &(pc->params[param]), &shift);
		param++;
	}
	return (1);
}
