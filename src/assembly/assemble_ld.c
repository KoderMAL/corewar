/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble_ld.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhadley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 16:54:30 by dhadley           #+#    #+#             */
/*   Updated: 2018/01/09 21:01:23 by dhadley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembly.h"

void	assemble_ld(char *champ, int *LC, t_pqueue *gaps, t_pqueue args)
{
	char	*buf;
	char	param_byte;

	champ[*LC] = 2;
	(*LC)++;
	// encode param_byte
	
	//if lab storegap with lab name and size (2 or 4)
	
	//else encode DIR or IND
	
	//encode reg
	

}
