/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   siqueue.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 13:50:22 by alalaoui          #+#    #+#             */
/*   Updated: 2017/12/19 16:31:50 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIQUEUE_H
# define SIQUEUE_H
# include "cqueue.h"

typedef struct	s_siqueue_elem
{
	char					*s;
	int						len;
	int						i;
	struct s_siqueue_elem	*next;
}				t_siqueue_elem;

typedef struct	s_siqueue
{
	t_siqueue_elem	*first;
	t_siqueue_elem	*last;
	int				len;
}				t_siqueue;

void			siqueue_init(t_siqueue *siqueue);
int				siqueue_push_cqueue(t_siqueue *siqueue, t_cqueue *cqueue, int i);
void			siqueue_delete(t_siqueue *siqueue);

#endif
