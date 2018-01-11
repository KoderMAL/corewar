/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 16:35:06 by stoupin           #+#    #+#             */
/*   Updated: 2018/01/10 16:35:07 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "asm.h"
#include "util/cqueue.h"

/*
** creates a label from a cqueue and an instruction number
*/

t_label	*label_from_cqueue(t_cqueue *cqueue, int instruction_number)
{
	t_label	*label;

	label = (t_label*)malloc(sizeof(t_label)
								+ sizeof(char) * (cqueue->len + 1));
	if (label == NULL)
		return (NULL);
	label->name = (char*)label + sizeof(t_label);
	label->len = cqueue->len;
	ft_cqueue_move(label->name, cqueue);
	label->instruction_number = instruction_number;
	return (label);
}
