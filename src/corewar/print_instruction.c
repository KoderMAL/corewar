/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_instruction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <alalaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 15:39:45 by alalaoui          #+#    #+#             */
/*   Updated: 2018/03/05 15:42:05 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	print_instruction_start(t_vm *vm, t_thread *pc)
{
	int		n_digits;
	int		nbr;

	if (vm->verbose == 0)
		return ;
	nbr = pc->number;
	n_digits = 1;
	while (nbr >= 10)
	{
		nbr /= 10;
		n_digits++;
	}
	if (n_digits > 4)
		n_digits = 4;
	openfile_write_str(&(vm->stdout), "P", 0);
	nbr = 0;
	while (nbr < 5 - n_digits)
	{
		openfile_write_str(&(vm->stdout), " ", 0);
		nbr++;
	}
	openfile_write_nbr(&(vm->stdout), pc->number, 0);
	openfile_write_str(&(vm->stdout), " | ", 0);
}
