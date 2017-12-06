/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 13:49:27 by alalaoui          #+#    #+#             */
/*   Updated: 2017/12/06 15:41:28 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clist.h"

void		clist_init(t_clist *clist)
{
	clist->len = 0;
	clist->first = NULL;
	clist->last = NULL;
}

int			clist_push_front(t_clist *clist, char c)
{
	t_clist_elem	*element;

	element = (t_clist_elem*)malloc(sizeof(t_clist_elem));
	if (element == NULL)
		return (1);
	element->c = c;
	element->next = clist->first;
	element->prev = NULL;
	if (clist->len == 0)
		clist->last = element;
	else
		clist->first->prev = element;
	clist->first = element;
	clist->len++;
	return (0);
}

char		clist_pop_back(t_clist *clist)
{
	t_clist_elem	*element;
	char			c;

	if (clist->len == 0)
		return (0);
	element = clist->last;
	clist->last = element->prev;
	if (clist->len == 1)
		clist->first = NULL;
	else
		clist->last->next = NULL;
	clist->len--;
	free(element);
	return (c);
}

char		*clist_join(t_clist *clist)
{
	char	*joined;
	size_t	copied;

	joined = (char*)malloc(sizeof(char) * (clist->len + 1));
	if (joined == NULL)
		return (NULL);
	copied = 0;
	while (clist->len > 0)
		joined[copied++] = clist_pop_back(clist);
	joined[copied] = '\0';
	return (joined);
}

int			clist_delete(t_clist *clist)
{
	t_clist_elem	*element;

	while (clist->len > 0)
	{
		element = clist->last;
		clist->last = element->prev;
		if (clist->len == 1)
			clist->first = NULL;
		else
			clist->last->next = NULL;
		clist->len--;
		free(element);
	}
	return (1);
}
