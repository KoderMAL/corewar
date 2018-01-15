/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_pass.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhadley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 19:05:21 by dhadley           #+#    #+#             */
/*   Updated: 2018/01/15 11:59:19 by dhadley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembly.h"

void	second_pass(char *champ, t_pqueue gaps)
{
	int		i;
	int		value;
	int		LC;
	t_gap	*tmp;

	i = 0;
	LC = 0;
	tmp = gaps->first->p;
	while (i < gaps.len)
	{
		LC = tmp.location;
		value = tmp->label.location - tmp.location;
		if (tmp.size == DIR_SIZE)
			encode_4_bytes(champ, &LC, value);
		else
			encode_2_bytes(champ, &LC, value);
		tmp = tmp->next;
		i++;
	}
}
