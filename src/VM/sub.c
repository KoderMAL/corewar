/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lramirez <lramirez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 13:06:48 by lramirez          #+#    #+#             */
/*   Updated: 2018/01/26 13:16:42 by lramirez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "vm.h"

// Récupère les 2 T_REG sur 1 octet chacun (char).
// Place leur soustraction dans le 3ème T_REG.
// Modifie le carry.
// Décrémente le process de 10 cycles (coût d'un sub).

void		sub(t_vm *vm, t_thread process)
{
	char	r1;
	char	r2;

	r1 = vm->map[(process->location + 1) % MEM_SIZE];
	r2 = vm->map[(process->location + 2) % MEM_SIZE];
	vm->map[(process->location + 3) % MEM_SIZE] = r1 - r2;
	process->carry = (process->carry == 0) ? 1 : 0;
	process->location = (process->location + 3) % MEM_SIZE;
	process->cycles -= 10;
}
