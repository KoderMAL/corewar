/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lramirez <lramirez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 12:10:18 by lramirez          #+#    #+#             */
/*   Updated: 2018/02/13 18:05:16 by lramirez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Récupère les 3 valeurs des T_REG sur 1 octet chacun.
** Vérifie que les 3 valeurs réfèrent à des registres existants.
** Si oui, additionne les valeurs des 2 premiers registres et place le
** résultat dans le 3ème,
** met le carry à 1 et déplace le PC à la fin du 3ème T_REG.
** Si non, met le carry à 0 et déplace le PC d'1 octet.
** Dans les deux cas, décrémente le process de 10 cycles (coût d'un add).
*/

int	op_add(t_vm *vm, t_thread *process)
{
	int		r1;
	int		r2;
	int		r3;

	r1 = vm->map[(process->location + 2) % MEM_SIZE];
	r2 = vm->map[(process->location + 3) % MEM_SIZE];
	r3 = vm->map[(process->location + 4) % MEM_SIZE];
	if ((r1 <= REG_NUMBER && r1 >= 1) && (r2 <= REG_NUMBER && r2 >= 1) &&
		(r3 <= REG_NUMBER && r3 >= 1)
	{
		process->r[r3] = process->r[r1] + process->r[r2];
		printf("third register contains %c\n", r[r3]);
		process->carry = 1;
		process->location = (process->location + 5) % MEM_SIZE;
	}
	else
	{
		process->carry = 0;
		process->location = (process->location + 2) % MEM_SIZE;
	}
	process->cycles -= 10;
	return (1);
}
