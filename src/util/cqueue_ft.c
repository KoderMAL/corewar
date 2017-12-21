#include "util/cqueue.h"

int			ft_cqueue_cmp(const char *name, t_cqueue *cqueue)
{
	int				i;
	t_cqueue_elem	*elem;

	i = 0;
	elem = cqueue->first;
	while (i < cqueue->len)
	{
		if (name[i] != elem->c)
			return (name[i] - elem->c);
		i++;
		elem = elem->next;
	}
	return (name[i]);
}

void		ft_cqueue_move(char *dest, t_cqueue *cqueue)
{
	while (cqueue->len > 0)
		*dest++ = cqueue_pop(cqueue);
}
