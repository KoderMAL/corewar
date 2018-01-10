/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_pass.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhadley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 17:28:49 by dhadley           #+#    #+#             */
/*   Updated: 2018/01/10 18:49:14 by dhadley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembly.h"

//add function to check if LC is bigger than the size of the champ

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
		if (elem->p.is_lab == false)
		{
			assemble_op(champ, &LC, gaps, elem->p.arguments, elem->p);
			elem = elem->next;
		}
		else
			//call store lab function with *LC and the elem->p to store the LC;
			//if elem->p islab (call store_lab_location)
			//
		i++;
	}
}
