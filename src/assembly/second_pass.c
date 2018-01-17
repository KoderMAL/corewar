/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_pass.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhadley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 19:05:21 by dhadley           #+#    #+#             */
/*   Updated: 2018/01/17 18:54:59 by dhadley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembly.h"

void	second_pass(unsigned char *champ, t_pqueue gaps)
{
	int		i;
	int		value;
	int		LC;
	t_pqueue_elem	*tmp;
	t_gap	*gap;

	i = 0;
	LC = 0;
	tmp = gaps.first;
	while (i < gaps.len)
	{
		gap = tmp->p;
		LC = gap->location;
		value = gap->label->location - (gap->command_location - 1);
		if (gap->size == DIR_SIZE)
			encode_4_bytes(champ, &LC, value);
		else
			encode_2_bytes(champ, &LC, value);
		tmp = tmp->next;
		i++;
	}
}
