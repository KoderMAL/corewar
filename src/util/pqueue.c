/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pqueue.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 13:49:27 by alalaoui          #+#    #+#             */
/*   Updated: 2017/12/06 15:41:28 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "pqueue.h"

void		pqueue_init(t_pqueue *pqueue)
{
	pqueue->len = 0;
	pqueue->first = NULL;
	pqueue->last = NULL;
}

int			pqueue_push(t_pqueue *pqueue, void *p)
{
	t_pqueue_elem	*element;

	if (p == NULL)
		return (1);
	element = (t_pqueue_elem*)malloc(sizeof(t_pqueue_elem));
	if (element == NULL)
		return (1);
	element->p = p;
	element->next = NULL;
	if (pqueue->len == 0)
   		pqueue->first = element;
	else
		pqueue->last->next = element;
	pqueue->last = element;
	pqueue->len++;
	return (0);
}

void		pqueue_delete(t_pqueue *pqueue)
{
	t_pqueue_elem	*elem;
	t_pqueue_elem	*elem_next;

	elem = pqueue->first;
	while (pqueue->len > 0)
	{
		elem_next = elem->next;
		free(elem->p);
		free(elem);
		elem = elem_next;
		pqueue->len--;
	}
	pqueue->first = NULL;
	pqueue->last = NULL;
}
