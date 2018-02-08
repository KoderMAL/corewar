/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 16:35:06 by stoupin           #+#    #+#             */
/*   Updated: 2018/02/08 11:22:08 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "asm.h"
#include "util/cqueue.h"

/*
** creates a label from a cqueue and an instruction number
*/

t_label	*label_from_cqueue(t_cqueue *cqueue)
{
	t_label	*label;

	label = (t_label*)malloc(sizeof(t_label)
								+ sizeof(char) * (cqueue->len + 1));
	if (label == NULL)
		return (NULL);
	label->name = (char*)label + sizeof(t_label);
	ft_cqueue_move(label->name, cqueue);
	label->location = 0;
	label->is_lab = 1;
	return (label);
}

t_label	*label_dup(t_label *label)
{
	t_label		*new_label;

	new_label = (t_label*)malloc(sizeof(t_label) +
			sizeof(char) * (ft_strlen(label->name) + 1));
	if (label == NULL)
		return (NULL);
	new_label->name = (char*)new_label + sizeof(t_label);
	ft_strcpy(new_label->name, label->name);
	new_label->is_lab = 1;
	new_label->location = 0;
	return (new_label);
}
