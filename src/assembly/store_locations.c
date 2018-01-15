/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_locations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhadley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 17:45:35 by dhadley           #+#    #+#             */
/*   Updated: 2018/01/15 11:59:30 by dhadley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembly.h"

void	store_gap(int *LC, t_pqueue *gaps, t_argument *arg, int has_idx)
{
	t_gap	*gap;
	
	gap = (t_gap *)malloc(sizeof(t_gap)); //protect malloc;
	gap.location = *LC;
	if (arg.lab_type == T_IND || has_idx)
	{
		gap.size = IND_SIZE;
		*LC += IND_SIZE;
	}
	else
	{
		gap.size = DIR_SIZE;
		*LC += DIR_SIZE;
	}
	gap.name = arg.name;
	gap->label = arg->label;
	if (pqueue_push(gaps, gap))
		//return error;
}

void	store_label(int LC, t_label *label)
{
	label.location = LC;
}
