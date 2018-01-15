/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cqueue.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 16:21:55 by stoupin           #+#    #+#             */
/*   Updated: 2018/01/10 16:22:59 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CQUEUE_H
# define CQUEUE_H

typedef struct	s_cqueue_elem
{
	char					c;
	struct s_cqueue_elem	*next;
}				t_cqueue_elem;

typedef struct	s_cqueue
{
	t_cqueue_elem	*first;
	t_cqueue_elem	*last;
	int				len;
}				t_cqueue;

/*
** cqueue.c
*/

void			cqueue_init(t_cqueue *cqueue);
int				cqueue_push(t_cqueue *cqueue, char c);
char			cqueue_pop(t_cqueue *cqueue);
char			*cqueue_join(t_cqueue *cqueue);
void			cqueue_delete(t_cqueue *cqueue);

/*
** cqueue_ft.c
*/

int				ft_cqueue_cmp(const char *name, t_cqueue *cqueue);
void			ft_cqueue_move(char *dest, t_cqueue *cqueue);

#endif
