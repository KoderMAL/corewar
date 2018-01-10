/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble_live.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhadley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 15:04:26 by dhadley           #+#    #+#             */
/*   Updated: 2018/01/10 18:41:05 by dhadley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembly.h"

void	assemble_live(char *champ, int *LC, t_pqueue *gaps, t_pqueue args)
{
	champ[(*LC)++] = 1;
	if (args->first->p.type == T_LAB)
		//store gap with lab name and size 4
	else
		encode_4_bytes(champ, LC, args->first->p.value);

}
