/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 13:16:44 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/17 13:25:57 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "asm.h"
#include "util/cqueue.h"

int			arg_from_cqueue(t_cqueue *cqueue, t_argument *argument)
{
	argument->type = 0;
	argument->lab_type = 0;
	argument->value = 0;
	argument->label = NULL;
	argument->name = malloc(sizeof(char) * (cqueue->len + 1));
	if (argument->name == NULL)
		return (1);
	ft_cqueue_move(argument->name, cqueue);
	return (0);
}

/*
** clean an argument
*/

void		argument_clean(t_argument *argument)
{
	if (argument->name != NULL)
		free(argument->name);
}
