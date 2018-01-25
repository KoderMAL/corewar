/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <alalaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 14:08:01 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/25 11:42:43 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_thread		*create_thread()
{
	t_thread	*new_thread;
	static int	i = 1;
	int			j;

	j = 1;
	new_thread = (t_thread*)malloc(sizeof(t_thread));
	if (new_thread == NULL)
		return (NULL);
	new_thread->carry = 0;
	ft_memset(new_thread->r, 0, REG_NUMBER);
	//if option -n == 0
		new_thread->r[0] = i++;
	new_thread->location = 0;
	return (new_thread);
}

void			thread_init(t_vm *vm, int *i)
{
		pqueue_init(&(vm->champs_fd[*i].threads));
		pqueue_push(&(vm->champs_fd[*i].threads), create_thread());
}