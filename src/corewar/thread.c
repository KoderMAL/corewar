/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 14:08:01 by alalaoui          #+#    #+#             */
/*   Updated: 2018/02/08 14:10:34 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_thread		*create_thread(t_vm *vm, int n)
{
	t_thread	*new_thread;
	static int	i = -1;
	int			j;

	j = 0;
	new_thread = (t_thread*)malloc(sizeof(t_thread));
	if (new_thread == NULL)
		return (NULL);
	new_thread->carry = 0;
	while (j < REG_NUMBER + 1)
		new_thread->r[j++] = 0;
	new_thread->r[1] = n;
	new_thread->countdown = -1;
	new_thread->cycles = CYCLE_TO_DIE;
	new_thread->location = (ABS(i) - 1) * (MEM_SIZE / vm->nb_champs);
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
	return (new_thread);
}
