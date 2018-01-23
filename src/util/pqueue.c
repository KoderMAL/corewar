/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pqueue.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 13:49:27 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/23 16:14:56 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "pqueue.h"

/*
** initializes a queue of pointers
** the cqueue is a linked list containing pointers
** they can be read in the same order as they are written
*/

void		pqueue_init(t_pqueue *pqueue)
{
	pqueue->len = 0;
	pqueue->first = NULL;
	pqueue->last = NULL;
}

/*
** appends a pointer to the queue
*/

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

/*
** pops a pointer from the queue
*/

void		*pqueue_pop(t_pqueue *pqueue)
{
	t_pqueue_elem	*element;
	void			*p;

	if (pqueue->len == 0)
		return (NULL);
	element = pqueue->first;
	pqueue->first = element->next;
	if (pqueue->len == 1)
		pqueue->last = NULL;
	pqueue->len--;
	p = element->p;
	free(element);
	return (p);
}

/*
** empties the queue
** the stored pointers are lost
*/

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

void		pqueue_clean(t_pqueue *pqueue)
{
	t_pqueue_elem	*elem;
	t_pqueue_elem	*elem_next;

	elem = pqueue->first;
	while (pqueue->len > 0)
	{
		elem_next = elem->next;
		free(elem);
		elem = elem_next;
		pqueue->len--;
	}
	pqueue->first = NULL;
	pqueue->last = NULL;
}
