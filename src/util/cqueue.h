/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cqueue.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 13:50:22 by alalaoui          #+#    #+#             */
/*   Updated: 2017/12/19 16:31:50 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Cqueue_H
# define Cqueue_H

typedef struct	s_cqueue_elem
{
	char				c;
	struct s_cqueue_elem	*next;
}				t_cqueue_elem;

typedef struct	s_cqueue
{
	t_cqueue_elem	*first;
	t_cqueue_elem	*last;
	int				len;
}				t_cqueue;

void			cqueue_init(t_cqueue *cqueue);
int				cqueue_push(t_cqueue *cqueue, char c);
char			cqueue_pop(t_cqueue *cqueue);
char			*cqueue_join(t_cqueue *cqueue);
void			cqueue_delete(t_cqueue *cqueue);

#endif
