/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_locations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 17:45:35 by dhadley           #+#    #+#             */
/*   Updated: 2018/01/23 14:09:55 by dhadley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembly.h"
#include <stdlib.h>

void	store_gap(int *LC, t_pqueue *gaps, t_argument arg, int has_idx, int gapLC)
{
	t_gap	*gap;
	
	gap = (t_gap *)malloc(sizeof(t_gap)); //protect malloc;
	gap->location = *LC;
	gap->command_location = gapLC;
	if (arg.lab_type == T_IND || has_idx)
	{
		gap->size = IND_SIZE;
		*LC += IND_SIZE;
	}
	else
	{
		gap->size = DIR_SIZE;
		*LC += DIR_SIZE;
	}
	gap->name = arg.name;
	gap->label = arg.label;
//	printf("label name = %s and gap name = %s and gap->locatins = %d \n", arg.label->name, gap->name, gap->location);
	if (pqueue_push(gaps, gap))
		;
		//return error;
}

void	store_label(int LC, t_label *label)
{
	label->location = LC;
//	printf("label name = %s LC = %d\n", label->name, label->location);
}
