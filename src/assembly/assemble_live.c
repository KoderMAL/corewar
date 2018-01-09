/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble_live.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhadley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 15:04:26 by dhadley           #+#    #+#             */
/*   Updated: 2018/01/09 21:01:28 by dhadley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembly.h"

void	assemble_live(char *champ, int *LC, t_pqueue *gaps, t_pqueue args)
{
	char *buf;

	champ[*LC] = 1;
	(*LC)++;
	if (args->first->p.type == T_LAB)
		//store gap with lab name and size 4
	else
	{
		buf = encode_4_bytes(args->first->p.value);
		while (i < 4)
		{
			champ[*LC] = buf[i];
			i++;
			(*LC)++;
		}
	}

}
