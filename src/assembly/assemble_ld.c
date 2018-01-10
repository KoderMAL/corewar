/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble_ld.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhadley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 16:54:30 by dhadley           #+#    #+#             */
/*   Updated: 2018/01/10 18:40:19 by dhadley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembly.h"

void	assemble_ld(unsigned char *champ, int *LC, t_pqueue *gaps, t_pqueue args)
{
	char	param_byte;
	t_argument	*tmp;
	int		i;

	i = 0;
	champ[(*LC)++] = 2;
	if optruc == 1;
		champ[(*LC)++] = encode_param_byte(args);
	tmp = args->first->p;
	while (i < args.len)
	{
		if (tmp.type == T_LAB)
			//storegap with lab name and size 2 or 4;
		else if (tmp.type == T_DIR)
			encode_4_bytes(champ, LC, tmp.value);
		else if (tmp.type == T_IND)
			encode_2_bytes(champ, LC, tmp.value);
		else if (tmp.type == T_REG)
			encode_1_byte(champ, LC, tmp.value);
		i++;
		tmp = tmp->next;
	}	

}
