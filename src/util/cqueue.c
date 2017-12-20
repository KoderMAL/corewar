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

int			cqueue_push_front(t_cqueue *cqueue, char c)
{
	t_cqueue_elem	*element;

	element = (t_cqueue_elem*)malloc(sizeof(t_cqueue_elem));
	if (element == NULL)
		return (1);
	element->c = c;
	element->next = cqueue->first;
	element->prev = NULL;
	if (cqueue->len == 0)
		cqueue->last = element;
	else
		cqueue->first->prev = element;
	cqueue->first = element;
	cqueue->len++;
	return (0);
}

char		cqueue_pop_back(t_cqueue *cqueue)
{
	t_cqueue_elem	*element;
	char			c;

	if (cqueue->len == 0)
		return (0);
	element = cqueue->last;
	cqueue->last = element->prev;
	if (cqueue->len == 1)
		cqueue->first = NULL;
	else
		cqueue->last->next = NULL;
	cqueue->len--;
	c = element->c;
	free(element);
	return (c);
}

char		*cqueue_join(t_cqueue *cqueue)
{
	char	*joined;
	int		copied;

	copied = 0;
	joined = (char*)malloc(sizeof(char) * (cqueue->len + 1));
	if (joined == NULL)
	{
		while (cqueue->len > 0)
			joined[copied++] = cqueue_pop_back(cqueue);
		return (NULL);
	}
	while (cqueue->len > 0)
		joined[copied++] = cqueue_pop_back(cqueue);
	joined[copied] = '\0';
	return (joined);
}

int			cqueue_delete(t_cqueue *cqueue)
{
	t_cqueue_elem	*element;

	while (cqueue->len > 0)
	{
		element = cqueue->last;
		cqueue->last = element->prev;
		if (cqueue->len == 1)
			cqueue->first = NULL;
		else
			cqueue->last->next = NULL;
		cqueue->len--;
		free(element);
	}
	return (1);
}
