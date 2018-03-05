/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <alalaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:38:04 by alalaoui          #+#    #+#             */
/*   Updated: 2018/03/05 17:26:07 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		get_params_util(t_thread *pc, const t_op *op,
									int param_code, int param)
{
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
}

static int		pc_assign(t_thread *pc, const t_op *op)
{
	pc->cycles -= op->n_cycles;
	pc->shift = 0;
	if (op->has_pcode)
		pc->bytecode = get_byte_at(pc, 1);
	pc->shift += 1 + op->has_pcode;
	return (pc->shift);
}

int				get_params_type(t_thread *pc, const t_op *op)
{
	int	param;
	int	param_code;
	int err;
	int	shift;

	err = 0;
	param = -1;
	shift = pc_assign(pc, op);
	if (op->has_pcode)
	{
		while (++param < op->n_arg)
		{
			pc->params_type[param] = 0;
			param_code = get_code(pc->bytecode, param + 1);
			if ((param_code & op->arg_type[param]) == 0 && param < op->n_arg)
				err = 1;
			get_params_util(pc, op, param_code, param);
		}
	}
	else
	{
		param_code = op->arg_type[0];
		get_params_util(pc, op, param_code, ++param);
	}
	return (!err);
}
