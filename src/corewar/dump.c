/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 12:00:20 by alalaoui          #+#    #+#             */
/*   Updated: 2018/02/23 21:06:36 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/ft.h"
#include "vm.h"

void		print_op(t_vm *vm, t_thread *pc, int print_as_direct)
{
	int			i;
	int			param;
	t_arg_type	param_type;

	print_instruction_start(vm, pc);
	print_str(vm, pc->op->name, 0);
	i = 0;
	while (i < pc->op->n_arg)
	{
		print_str(vm, " ", 0);
		param = pc->params[i];
		param_type = pc->params_type[i];
		if (param_type == T_REG)
			print_reg(vm, param, 0);
		else if (param_type == T_IND && !print_as_direct)
			print_nbr(vm, get_bytes(pc, param, 4), 0);
		else
			print_nbr(vm, param, 0);
		i++;
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

static void	write_hex(t_vm *vm, unsigned char byte)
{
	static const char	digits[16] = "0123456789abcdef";

	openfile_write_char(&(vm->stdout), digits[byte / 16]);
	openfile_write_char(&(vm->stdout), digits[byte % 16]);
}

void		write_map(t_vm *vm)
{
	unsigned char	byte;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < MEM_SIZE / 64)
	{
		openfile_write_str(&(vm->stdout), "0x", 0);
		write_hex(vm, (i * 64) / 256);
		write_hex(vm, (i * 64) % 256);
		openfile_write_str(&(vm->stdout), " : ", 0);
		j = 0;
		while (j < 64)
		{
			byte = vm->map[64 * i + j];
			write_hex(vm, byte);
			openfile_write_char(&(vm->stdout), ' ');
			j++;
		}
		openfile_write_char(&(vm->stdout), '\n');
		i++;
	}
}

void		dump(t_vm *vm)
{
	if ((vm->cycle_to_dump != -1 && vm->game_cycle == vm->cycle_to_dump)
		|| (vm->dump_every > 0 && vm->game_cycle % vm->dump_every == 0))
	{
		write_map(vm);
		if (vm->game_cycle == vm->cycle_to_dump)
			vm_clean(vm);
	}
}
