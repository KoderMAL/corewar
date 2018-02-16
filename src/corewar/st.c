/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhadley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 18:33:49 by dhadley           #+#    #+#             */
/*   Updated: 2018/02/16 18:33:51 by dhadley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Cette instruction prend 2 paramètres. Elle store (REG_SIZE OCTET)
** la valeur du
** premier argument (toujours un registre) dans le second.
**
** st r4,34 store la valeur de r4 à l’adresse ( pc + (34 % IDX_MOD))
** st r3,r8 copie r3 dans r8
** This op does not modify the carry
*/

void	op_st(t_thread *pc)
{
	int value;

	value = get(pc, 0);
	set(pc, 1, value);
}
