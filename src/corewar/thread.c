/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 14:08:01 by alalaoui          #+#    #+#             */
/*   Updated: 2018/03/06 15:22:13 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_thread		*create_thread(t_vm *vm, int n)
{
	t_thread	*new_thread;
	static int	i = -1;
	int			j;

	j = 0;
	if (!(new_thread = (t_thread*)malloc(sizeof(t_thread))))
		return (NULL);
	new_thread->vm = vm;
	new_thread->carry = 0;
	while (j < REG_NUMBER + 1)
		new_thread->r[j++] = 0;
	new_thread->r[1] = n;
	new_thread->countdown = -1;
	new_thread->op = NULL;
	new_thread->cycles = CYCLE_TO_DIE;
	new_thread->alive = false;
	new_thread->location = (ABS(i) - 1) * (MEM_SIZE / vm->n_champs);
	new_thread->shift = 0;
	new_thread->shift_save = 0;
	new_thread->bytecode = 0;
	new_thread->last_live = 0;
	vm->thread_counter++;
	new_thread->number = vm->thread_counter;
	i--;
	return (new_thread);
}

t_thread		*dup_thread(t_thread *src_thread, int pc)
{
	t_thread	*new_thread;
	int			j;

	new_thread = (t_thread*)malloc(sizeof(t_thread));
	if (new_thread == NULL)
		return (NULL);
	new_thread->vm = src_thread->vm;
	new_thread->carry = src_thread->carry;
	j = 0;
	while (j < REG_NUMBER + 1)
	{
		new_thread->r[j] = src_thread->r[j];
		j++;
	}
	new_thread->countdown = -1;
	new_thread->cycles = CYCLE_TO_DIE;
	new_thread->location = pc;
	new_thread->alive = false;
	new_thread->last_live = src_thread->last_live;
	if (src_thread->alive == true)
		new_thread->alive = true;
	new_thread->vm->thread_counter++;
	new_thread->number = new_thread->vm->thread_counter;
	new_thread->shift = 0;
	new_thread->shift_save = 0;
	return (new_thread);
}
