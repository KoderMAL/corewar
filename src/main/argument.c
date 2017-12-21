#include <stdlib.h>
#include "asm.h"

/*
** duplicates an argument
*/

t_argument	*argument_dup(t_argument *argument)
{
	t_argument	*new_argument;

	new_argument = (t_argument*)malloc(sizeof(t_argument));
	if (new_argument == NULL)
		return (NULL);
	new_argument->type = argument->type;
	new_argument->value[0] = argument->value[0];
	new_argument->value[1] = argument->value[1];
	new_argument->value[2] = argument->value[2];
	new_argument->value[3] = argument->value[3];
	return (new_argument);
}
