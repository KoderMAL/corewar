/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <alalaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 14:08:01 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/23 13:53:11 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_thread		*create_thread()
{
	t_thread	*new_thread;
	static int	i = 1;

	new_thread = (t_thread*)malloc(sizeof(t_thread));
	new_thread->carry = 0;
	new_thread->reg1 = i++;
	new_thread->reg2 = 0;
	new_thread->reg3 = 0;
	new_thread->location = 0;
	return (new_thread);
}

void			thread_init(t_vm *vm)
{
	int			i;

	i = 0;
	while (i++ < vm->nb_champs)
		pqueue_push(vm->threads, create_thread());
}