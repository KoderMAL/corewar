/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pqueue_fast_pass.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 12:12:58 by stoupin           #+#    #+#             */
/*   Updated: 2018/01/26 12:14:57 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "pqueue.h"

/*
** take all the queue over
*/

int	pqueue_push_front(t_pqueue *pqueue, void *p)
{
	t_pqueue_elem	*element;

	if (p == NULL)
		return (1);
	element = (t_pqueue_elem*)malloc(sizeof(t_pqueue_elem));
	if (element == NULL)
		return (1);
	element->p = p;
	element->next = pqueue->first;
	pqueue->first = element;
	pqueue->len++;
	return (0);
}
