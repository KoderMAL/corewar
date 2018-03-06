/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <alalaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 15:51:12 by alalaoui          #+#    #+#             */
/*   Updated: 2018/03/06 17:54:58 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/ft.h"
#include "vm.h"

static int	print_op2(t_vm *vm, t_thread *pc, int i)
{
	int		param;
	int		param_type;

	param = pc->params[i];
	param_type = pc->params_type[i];
	print_str(vm, " ", 0);
	if (vm->zaz_mode && pc->op->opcode == O_AND && param_type == T_IND)
	{
		print_nbr(vm, get_bytes(pc, param % IDX_MOD, 4), 0);
		return (1);
	}
	else if (vm->zaz_mode && pc->op->opcode == O_STI && param_type == T_IND)
	{
		print_nbr(vm, get(pc, i, false), 0);
		return (1);
	}
	return (0);
}

static void	print_op_start(t_vm *vm, t_thread *pc)
{
	print_instruction_start(vm, pc);
	print_str(vm, pc->op->name, 0);
}

void		print_op(t_vm *vm, t_thread *pc, int print_value)
{
	int			i;
	int			param;
	t_arg_type	param_type;

	i = -1;
	print_op_start(vm, pc);
	while (++i < pc->op->n_arg)
	{
		param = pc->params[i];
		param_type = pc->params_type[i];
		if (print_op2(vm, pc, i))
			;
		else if (vm->zaz_mode && pc->op->opcode == O_ST && i == 1 &&
					param_type == T_REG)
			print_nbr(vm, param, 0);
		else if (param_type == T_REG)
		{
			(print_value & (1 << i)) ? print_nbr(vm, pc->r[param], 0) :
				print_reg(vm, param, 0);
		}
		else if (param_type == T_IND && !(print_value & (1 << i)))
			print_nbr(vm, get_bytes(pc, param, 4), 0);
		else
			print_nbr(vm, param, 0);
	}
}

void		print_adv(t_vm *vm, t_thread *pc)
{
	int	i;

	if (pc->shift == 0)
		return ;
	print_str(vm, "ADV ", 0);
	print_nbr(vm, pc->shift, 0);
	print_str(vm, " (0x", 0);
	print_byte(vm, pc->location / 256, 0);
	print_byte(vm, pc->location % 256, 0);
	print_str(vm, " -> 0x", 0);
	print_byte(vm, (pc->location + pc->shift) / 256, 0);
	print_byte(vm, (pc->location + pc->shift) % 256, 0);
	print_str(vm, ") ", 0);
	i = 0;
	while (i < pc->shift)
	{
		print_byte(vm, get_byte_at(pc, i), 0);
		print_str(vm, " ", 0);
		i++;
	}
	print_str(vm, "", 1);
}
