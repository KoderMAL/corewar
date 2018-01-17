/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <alalaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 14:08:01 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/17 14:58:30 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_thread		*create_thread(t_vm *vm)
{
	t_thread	new_thread;
	
	new_thread.carry = 0;
	new_thread.reg1 = 0;
	new_thread.reg2 = 0;
	new_thread.reg3 = 0;
	new_thread.location = 0;
	return (new_thread);
}

void			thread_init(t_vm *vm)
{
	int			i;

	i = 0;
	while (i++ < vm->players)
		pqueue_push(vm->threads, thread_create(vm));
	
}