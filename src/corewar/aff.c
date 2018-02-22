/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lramirez <lramirez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 13:10:50 by lramirez          #+#    #+#             */
/*   Updated: 2018/02/21 18:28:41 by lramirez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "vm.h"

/*
** Il n’y a qu’un paramètre, qui est un registre, dont le contenu est interprété
** comme la valeur ASCII d’un caractère à afficher sur la sortie standard.
** Ce code est modulo 256.
*/

void		op_aff(t_thread *pc)
{
	// openfile_write_char(&(vm->stdout), (char)pc->r[pc->params[0]] % 256);
	return ;
}
