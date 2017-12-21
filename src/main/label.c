#include <stdlib.h>
#include "asm.h"
#include "util/cqueue.h"

t_label	*label_from_cqueue(t_cqueue *cqueue, int instruction_number)
{
	t_label	*label;

	label = (t_label*)malloc(sizeof(t_label)
									 + sizeof(char) * (cqueue->len + 1));
	if (label == NULL)
		return (NULL);
	label->name = (char*)((void*)label + sizeof(label));
	ft_cqueue_move(label->name, cqueue);
	label->len = cqueue->len;
	label->instruction_number = instruction_number;
	return (0);
}
