/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 13:10:50 by lramirez          #+#    #+#             */
/*   Updated: 2018/02/23 21:18:06 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "vm.h"

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
