/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 14:10:35 by dhadley           #+#    #+#             */
/*   Updated: 2018/01/23 15:53:00 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembly.h"
#include "main/op.h"

int	pass(t_env *env, t_pqueue instructions, t_pqueue *gaps, int pass)
{
	int	LC;
	int i;
	t_pqueue_elem	*elem;

	i = 0;
	LC = 0;
	elem = instructions.first;
	while (i < instructions.len)
	{
		/*if (LC > CHAMP_MAX_SIZE)
		{
			err(env, "champion too large", -1);
			return (LC);
		}*/
		if (((t_instruction *)elem->p)->is_lab == false)
		{
			if (pass == 1 && assemble_op_fake(env, &LC, gaps, elem->p))
				return (0);
			if (pass == 2)
				assemble_op(env, &LC, gaps, elem->p);
		}
		else if (pass == 1)
			store_label(LC, (t_label *)elem->p);
		elem = elem->next;
		i++;
	}
	return (LC);
}
