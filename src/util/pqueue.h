/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pqueue.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 13:50:22 by alalaoui          #+#    #+#             */
/*   Updated: 2017/12/19 16:31:50 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PQUEUE_H
# define PQUEUE_H
# include "pqueue.h"

typedef struct	s_pqueue_elem
{
	void					*p;
	struct s_pqueue_elem	*next;
}				t_pqueue_elem;

typedef struct	s_pqueue
{
	t_pqueue_elem	*first;
	t_pqueue_elem	*last;
	int				len;
}				t_pqueue;

void			pqueue_init(t_pqueue *pqueue);
int				pqueue_push_pqueue(t_pqueue *pqueue, void *p);
void			pqueue_delete(t_pqueue *pqueue);

#endif
