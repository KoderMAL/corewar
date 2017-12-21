/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cqueue.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 13:49:27 by alalaoui          #+#    #+#             */
/*   Updated: 2017/12/06 15:41:28 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cqueue.h"

void		cqueue_init(t_cqueue *cqueue)
{
	cqueue->len = 0;
	cqueue->first = NULL;
	cqueue->last = NULL;
}

int			cqueue_push(t_cqueue *cqueue, char c)
{
	t_cqueue_elem	*element;

	element = (t_cqueue_elem*)malloc(sizeof(t_cqueue_elem));
	if (element == NULL)
		return (1);
	element->c = c;
	element->next = NULL;
	if (cqueue->len == 0)
   		cqueue->first = element;
	else
		cqueue->last->next = element;
	cqueue->last = element;
	cqueue->len++;
	return (0);
}

char		cqueue_pop(t_cqueue *cqueue)
{
	t_cqueue_elem	*element;
	char			c;

	if (cqueue->len == 0)
		return (0);
	element = cqueue->first;
	cqueue->first = element->next;
	if (cqueue->len == 1)
		cqueue->last = NULL;
	cqueue->len--;
	c = element->c;
	free(element);
	return (c);
}

char		*cqueue_join(t_cqueue *cqueue)
{
	char	*joined;
	int 	copied;

	copied = 0;
	joined = (char*)malloc(sizeof(char) * (cqueue->len + 1));
	if (joined == NULL)
	{
		cqueue_delete(cqueue);
		return (NULL);
	}
	while (cqueue->len > 0)
		joined[copied++] = cqueue_pop(cqueue);
	joined[copied] = '\0';
	return (joined);
}

void		cqueue_delete(t_cqueue *cqueue)
{
	while (cqueue->len > 0)
		cqueue_pop(cqueue);
}
