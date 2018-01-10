/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_label.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 16:28:38 by stoupin           #+#    #+#             */
/*   Updated: 2018/01/10 16:28:39 by stoupin          ###   ########.fr       */
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
				label_from_cqueue(&(env->characters), env->instructions.len));
		if (error)
			err(env, "memory error", -1);
	}
	env->header = 0;
	env->state = &state_start;
}
