/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 13:10:50 by lramirez          #+#    #+#             */
/*   Updated: 2018/02/08 12:16:26 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "vm.h"

/*
** Récupère le T_REG sur 1 octet (char), après l'octet de paramètrage.
** Affiche le contenu en ascii.
** Décrémente le process de 2 cycles (coût d'un aff).
*/

int	op_aff(t_vm *vm, t_thread *process)
{
	int		reg_nbr;
	int		display;

	reg_nbr = vm->map[(process->location + 2) % MEM_SIZE];
	display = process->r[reg_nbr] % 256;
	if (reg_nbr <= REG_NUMBER)
		write(1, &display, 1);
	process->cycles -= 2;
	process->location = (process->location + 3) % MEM_SIZE;
	return (1);
}
