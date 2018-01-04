#include <stdlib.h>
#include "asm.h"

/*
** initializes an instruction
** instruction->arguments must have been initialized with pqueue_init first!
*/

void			instruction_init(t_env *env)
{
	if (env->op)
	{
		env->instruction.op = env->op;
		env->op = NULL;
	}
	pqueue_delete(&(env->instruction.arguments));
}

/*
** duplicates an instruction
*/

t_instruction	*instruction_dup(t_instruction *instruction)
{
	t_instruction	*new_instruction;

	new_instruction = (t_instruction*)malloc(sizeof(t_instruction));
	if (new_instruction == NULL)
		return (NULL);
	new_instruction->op = instruction->op;
	new_instruction->arguments = instruction->arguments;
	return (new_instruction);
}
