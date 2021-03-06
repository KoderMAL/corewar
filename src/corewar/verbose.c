/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <alalaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 11:37:33 by stoupin           #+#    #+#             */
/*   Updated: 2018/03/05 15:40:33 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	print_instruction_continue(t_vm *vm)
{
	if (vm->verbose == 0)
		return ;
	openfile_write_str(&(vm->stdout), "\n       | ", 0);
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

void	print_byte(t_vm *vm, unsigned char byte, int endl)
{
	static const char	*digits = "0123456789abcdef";

	if (vm->verbose == 0)
		return ;
	openfile_write_char(&(vm->stdout), digits[byte / 16]);
	openfile_write_char(&(vm->stdout), digits[byte % 16]);
	if (endl)
		openfile_write_char(&(vm->stdout), '\n');
}
