/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <alalaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 13:10:50 by lramirez          #+#    #+#             */
/*   Updated: 2018/03/05 18:31:48 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../corewar/vm.h"

/*
** Il n’y a qu’un paramètre, qui est un registre, dont le contenu est interprété
** comme la valeur ASCII d’un caractère à afficher sur la sortie standard.
** Ce code est modulo 256.
*/

void	op_aff(t_thread *pc)
{
	if (!pc->vm->zaz_mode)
		openfile_write_char(&(pc->vm->stdout),
							(char)pc->r[pc->params[0]] % 256);
	return ;
}
