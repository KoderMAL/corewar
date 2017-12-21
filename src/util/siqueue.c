/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   siqueue.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 13:49:27 by alalaoui          #+#    #+#             */
/*   Updated: 2017/12/06 15:41:28 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cqueue.h"
#include "siqueue.h"

void		siqueue_init(t_siqueue *siqueue)
{
	siqueue->len = 0;
	siqueue->first = NULL;
	siqueue->last = NULL;
}

int			siqueue_push_cqueue(t_siqueue *siqueue, t_cqueue *cqueue, int i)
{
	t_siqueue_elem	*element;

	element = (t_siqueue_elem*)malloc(sizeof(t_siqueue_elem)
									 + sizeof(char) * (cqueue->len + 1));
	if (element == NULL)
		return (1);
	element->s = (char*)((void*)element + sizeof(t_siqueue_elem));
	element->len = cqueue->len;
	element->i = i;
	element->next = NULL;
	if (siqueue->len == 0)
   		siqueue->first = element;
	else
		siqueue->last->next = element;
	siqueue->last = element;
	siqueue->len++;
	return (0);
}

void		siqueue_delete(t_siqueue *siqueue)
{
	t_siqueue_elem	*elem;
	t_siqueue_elem	*elem_next;

	elem = siqueue->first;
	while (siqueue->len > 0)
	{
		elem_next = elem->next;
		free(elem);
		elem = elem_next;
		siqueue->len--;
	}
	siqueue->first = NULL;
	siqueue->last = NULL;
}
