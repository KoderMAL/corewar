/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_locations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 17:45:35 by dhadley           #+#    #+#             */
/*   Updated: 2018/01/23 14:29:26 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "assembly.h"

t_gap	*create_gap(int *LC, t_argument arg, int has_idx, int gapLC)
{
	t_gap	*gap;
	
	gap = (t_gap *)malloc(sizeof(t_gap)); //protect malloc;
	if (gap == NULL)
		return (NULL);
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
	return (gap);
}

void	store_label(int LC, t_label *label)
{
	label->location = LC;
}
