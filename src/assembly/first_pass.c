/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_pass.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhadley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 17:28:49 by dhadley           #+#    #+#             */
/*   Updated: 2018/01/11 19:17:15 by dhadley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembly.h"

//make size of champion a bit bigger and change to unsigned char;

void	first_pass(char	*champ, t_pqueue instructions, t_pqueue *gaps)
{
	int	LC;
	int i;
	t_pqueue_elem	*elem;

	i = 0;
	LC = 0;
	elem = instructions->first;
	while (i < instructions.len)
	{
		if (LC > MAX_CHAMP_SIZE)
			//return error (size of champion is too big);
		if (elem->p.is_lab == false)
		{
			assemble_op(champ, &LC, gaps, elem->p.arguments, elem->p);
		}
		else
		{
			store_label(LC, elem->p);
		}
		elem = elem->next;
		i++;
	}
}
