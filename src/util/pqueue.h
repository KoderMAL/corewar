/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pqueue.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 13:50:22 by alalaoui          #+#    #+#             */
/*   Updated: 2018/02/12 17:28:27 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PQUEUE_H
# define PQUEUE_H
# include "pqueue.h"

typedef struct	s_pqueue_elem
{
	void					*p;
	struct s_pqueue_elem	*prev;
	struct s_pqueue_elem	*next;
}				t_pqueue_elem;

typedef struct	s_pqueue
{
	t_pqueue_elem	*first;
	t_pqueue_elem	*last;
	int				len;
}				t_pqueue;

/*
** pqueue.c
*/

void			pqueue_init(t_pqueue *pqueue);
int				pqueue_push(t_pqueue *pqueue, void *p);
void			*pqueue_pop(t_pqueue *pqueue);
void			pqueue_delete(t_pqueue *pqueue);
void			pqueue_clean(t_pqueue *pqueue);

/*
** pqueue_util.c
*/

int				pqueue_push_front(t_pqueue *pqueue, void *p);
void			*pqueue_remove(t_pqueue *pqueue, t_pqueue_elem *elem);

#endif
