/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 18:06:57 by alalaoui          #+#    #+#             */
/*   Updated: 2018/02/08 16:46:35 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft/ft.h"
#include "vm.h"

int			err2(t_vm *vm, char *err_msg)
{
	vm->err = 1;
	vm->err_msg = err_msg;
	return (vm->err);
}

void		err2_display(t_vm *vm)
{
	if (vm->err == 0)
		return ;
	openfile_write_str(&(vm->stderr), "Error: ", 0);
	openfile_write_str(&(vm->stderr), vm->err_msg, 1);
}
