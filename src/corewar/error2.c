/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 18:06:57 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/29 10:12:09 by stoupin          ###   ########.fr       */
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
	write(2, "Error: ", 7);
	write (2, vm->err_msg, ft_strlen(vm->err_msg));
	write(2, "\n", 1);
}