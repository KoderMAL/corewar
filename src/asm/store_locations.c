/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_locations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 17:45:35 by dhadley           #+#    #+#             */
/*   Updated: 2018/02/08 11:32:35 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "assembly.h"

t_gap	*create_gap(int *lc, t_argument arg, int has_idx, int gaplc)
{
	t_gap	*gap;

	gap = (t_gap *)malloc(sizeof(t_gap));
	if (gap == NULL)
		return (NULL);
	gap->location = *lc;
	gap->command_location = gaplc;
	if (arg.lab_type == T_IND || has_idx)
	{
		gap->size = IND_SIZE;
		*lc += IND_SIZE;
	}
	else
	{
		gap->size = DIR_SIZE;
		*lc += DIR_SIZE;
	}
	gap->name = arg.name;
	gap->label = arg.label;
	return (gap);
}

void	store_label(int lc, t_label *label)
{
	label->location = lc;
}
