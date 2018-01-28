/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <alalaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 18:06:57 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/24 12:47:59 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		err2(t_vm *vm, char *err_msg)
{
	vm->err = 1;
	vm->err_msg = err_msg;
}

void		err2_display(t_vm *vm)
{
	if (vm->err == 0)
		return ;
	write(1, "Error: ", 7);
	write (1, vm->err_msg, ft_strlen(vm->err_msg));
	write(1, "\n", 1);
}