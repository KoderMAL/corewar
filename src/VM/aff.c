/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lramirez <lramirez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 13:10:50 by lramirez          #+#    #+#             */
/*   Updated: 2018/01/26 17:44:28 by lramirez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "vm.h"

// Récupère le T_REG sur 1 octet (char), après l'octet de paramètrage.
// Affiche le contenu en ascii.
// Décrémente le process de 2 cycles (coût d'un aff).

void		aff(t_vm *vm, t_thread process)
{
	char	reg_nbr;
	char	val_reg;

	reg_nbr = vm->map[(process->location + 2) % MEM_SIZE];
	if (reg_nbr <= REG_NUMBER)
		write(1, &(process->r[reg_nbr] % 256), 1);
	process->cycles -= 2;
}
