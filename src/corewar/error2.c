/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <alalaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 18:06:57 by alalaoui          #+#    #+#             */
/*   Updated: 2018/02/16 14:57:09 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft/ft.h"
#include "vm.h"

int		err2(t_vm *vm, char *err_msg)
{
	vm->err = 1;
	vm->err_msg = err_msg;
	return (vm->err);
}

void	err2_display(t_vm *vm)
{
	if (vm->err == 0)
		return ;
	openfile_write_str(&(vm->stderr), "Error: ", 0);
	openfile_write_str(&(vm->stderr), vm->err_msg, 1);
}

void	announce_war(t_vm *vm, int i)
{
	openfile_write_str(&(vm->stdout), "* Player ", 0);
	openfile_write_nbr(&(vm->stdout), i + 1, 0);
	openfile_write_str(&(vm->stdout), ", weighing ", 0);
	openfile_write_nbr(&(vm->stdout), vm->champs[i].size_bytecode, 0);
	openfile_write_str(&(vm->stdout), " bytes, \"", 0);
	openfile_write_str(&(vm->stdout), vm->champs[i].name, 0);
	openfile_write_str(&(vm->stdout), "\" (\"", 0);
	openfile_write_str(&(vm->stdout), vm->champs[i].comment, 0);
	openfile_write_str(&(vm->stdout), "\") !", 1);
	champion_to_vm(vm, i);
}
