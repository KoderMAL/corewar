/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pqueue_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 12:12:58 by stoupin           #+#    #+#             */
/*   Updated: 2018/02/12 17:38:14 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "pqueue.h"

/*
** take all the queue over
*/

int		pqueue_push_front(t_pqueue *pqueue, void *p)
{
	t_pqueue_elem	*element;

	if (p == NULL)
		return (1);
	element = (t_pqueue_elem*)malloc(sizeof(t_pqueue_elem));
	if (element == NULL)
		return (1);
	element->p = p;
	element->next = pqueue->first;
	element->next->prev = element;
	element->prev = NULL;
	pqueue->first = element;
	pqueue->len++;
	return (0);
}

/*
** remove an element from the queue
*/

void	*pqueue_remove(t_pqueue *pqueue, t_pqueue_elem *elem)
{
	void	*p;

	if (pqueue == NULL || elem == NULL || pqueue->len < 1)
		return (NULL);
	elem->prev->next = elem->next;
	elem->next->prev = elem->prev;
	pqueue->len--;
	p = elem->p;
	free(elem);
	return (p);
}
