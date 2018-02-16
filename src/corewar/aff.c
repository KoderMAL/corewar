/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 13:10:50 by lramirez          #+#    #+#             */
/*   Updated: 2018/02/16 15:42:17 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "vm.h"

/*
** Récupère le T_REG sur 1 octet (char), après l'octet de paramètrage.
** Affiche le contenu en ascii.
** Décrémente le process de 2 cycles (coût d'un aff).
*/

int	op_aff(t_thread *process)
{
	//int		reg_nbr;
	//int		display;
	//t_vm *vm;

	//vm = process->vm;
	//reg_nbr = vm->map[(process->location + 2) % MEM_SIZE];
	// display = process->r[reg_nbr] % 256;
	// if (reg_nbr <= REG_NUMBER)
	// 	openfile_write_char(&(vm->stdout), (char)display);
	process->cycles -= 2;
	process->location = (process->location + 3) % MEM_SIZE;
	return (1);
}
