/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clist.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 13:50:22 by alalaoui          #+#    #+#             */
/*   Updated: 2017/12/06 15:42:55 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIST_H
# define CLIST_H

# include <stdlib.h>

typedef struct	s_clist_elem
{
	char				c;
	struct s_clist_elem	*prev;
	struct s_clist_elem	*next;
}				t_clist_elem;

typedef struct	s_clist
{
	t_clist_elem	*first;
	t_clist_elem	*last;
	size_t			len;
}				t_clist;

void			clist_init(t_clist *clist);
int				clist_push_front(t_clist *clist, char c);
char			clist_pop_back(t_clist *clist);
char			*clist_join(t_clist *clist);
int				clist_delete(t_clist *clist);

#endif
