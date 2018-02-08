/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 14:10:35 by dhadley           #+#    #+#             */
/*   Updated: 2018/02/08 11:33:13 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembly.h"
#include "op.h"

int	pass(t_env *env, t_pqueue instructions, t_pqueue *gaps, int pass)
{
	int				lc;
	int				i;
	t_pqueue_elem	*elem;

	i = 0;
	lc = 0;
	elem = instructions.first;
	while (i < instructions.len)
	{
		if (((t_instruction *)elem->p)->is_lab == false)
		{
			if (pass == 1 && assemble_op_fake(env, &lc, gaps, elem->p))
				return (0);
			if (pass == 2)
				assemble_op(env, &lc, gaps, elem->p);
		}
		else if (pass == 1)
			store_label(lc, (t_label *)elem->p);
		elem = elem->next;
		i++;
	}
	return (lc);
}
