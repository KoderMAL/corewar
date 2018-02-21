/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 11:37:33 by stoupin           #+#    #+#             */
/*   Updated: 2018/02/21 16:31:10 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	print_instruction_start(t_vm *vm, t_thread *pc)
{
	if (vm->verbose == 0)
		return ;
	openfile_write_str(&(vm->stdout), "P    ", 0);
	openfile_write_nbr(&(vm->stdout), pc->number, 0);
	openfile_write_str(&(vm->stdout), " | ", 0);
}

void	print_instruction_continue(t_vm *vm, t_thread *pc)
{
	int	thread_number;

	if (vm->verbose == 0)
		return ;
	thread_number = pc->number;
	openfile_write_str(&(vm->stdout), "     ", 0);
	while (thread_number >= 10)
	{
		openfile_write_char(&(vm->stdout), ' ');
		thread_number /= 10;
	}
	openfile_write_str(&(vm->stdout), "  | ", 0);
}

void	print_str(t_vm *vm, char *s, int endl)
{
	if (vm->verbose == 0)
		return ;
	openfile_write_str(&(vm->stdout), s, endl);
}

void	print_nbr(t_vm *vm, int i, int endl)
{
	if (vm->verbose == 0)
		return ;
	openfile_write_nbr(&(vm->stdout), i, endl);
}

void	print_reg(t_vm *vm, int i, int endl)
{
	if (vm->verbose == 0)
		return ;
	openfile_write_char(&(vm->stdout), 'r');
	openfile_write_nbr(&(vm->stdout), i, endl);
}
