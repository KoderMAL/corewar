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
	new_argument->value = argument->value;
	new_argument->name = argument->name;
	new_argument->label = argument->label;
	return (new_argument);
}
