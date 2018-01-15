/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_label.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 14:17:19 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/15 16:23:17 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main/asm.h"
#include "states.h"

void	save_label(t_env *env)
{
	int	error;

	if (check_label(env))
	{
		error = pqueue_push(
				&(env->labels),
				label_from_cqueue(&(env->characters)));
		if (error)
			err(env, "memory error", -1);
		else
			pqueue_push(&(env->instructions), label_dup(env->labels.last->p));
	}
	env->header = 0;
	env->state = &state_start;
}
