/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_pass.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhadley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 17:28:49 by dhadley           #+#    #+#             */
/*   Updated: 2018/01/08 18:36:34 by dhadley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembly.h"

void	*get_op(t_pqueue_elem *elem)
{
	if (instruction->op.opcode == 1)
		return (&assemble_live);
}

void	first_pass(char	*champion, t_pqueue instructions, t_pqueue *gaps)
{
	int	LC;
	int i;
	void (*assemble_op)(char *champion, int *LC, t_pqueue *gaps, t_pqueue args);
	t_pqueue_elem	*elem;
	
	i = 0;
	LC = 0;
	elem = instructions->first;
	while (i < instructions.len)
	{
		//if elem->p islab (call store_lab_location)
		//else call get_op from array of functions)
		
		assemble_op = get_op(elem);
		if (elem->p.is_lab (autre));
		(assemble_op)(champ, gaps, LC, elem->p->arguments);
	}
	

	
}
