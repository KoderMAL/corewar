/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states_label.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 16:31:14 by stoupin           #+#    #+#             */
/*   Updated: 2018/01/23 18:04:10 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main/asm.h"
#include "states.h"
#include "util/pqueue.h"

int		check_label(t_env *env)
{
	t_cqueue_elem	*elem;
	int				i;

	elem = env->characters.first;
	i = 0;
	while (i < env->characters.len && env->err == 0)
	{
		if (!ft_strchr(g_label_chars, elem->c))
			err(env, "incorrect character in label", env->characters.len - i);
		elem = elem->next;
		i++;
	}
	if (env->err == 0)
		return (1);
	else
		return (0);
}
