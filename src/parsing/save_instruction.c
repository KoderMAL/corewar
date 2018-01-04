/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_instruction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 17:48:23 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/04 18:14:28 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main/asm.h"

/*
** Cette fonction doit prendre env->instruction,
** controler que l'instruction est correcte
** puis l'ajouter a env->instructions a l'aide de 
** instruction_dup
*/

static int		check_types(t_instruction *instruction)
{
return(1);
}

static int		check_instruction(t_instruction *instruction)
{
return (1);	
}

void			save_instruction(t_env *env)
{
	t_instruction *new;

	new = NULL;
	if (check_instruction(&env->instruction) == -1)
		err(env, "invalid instruction format\n", 0);
	else
	{
		new = instruction_dup(&env->instruction);
		pqueue_push(&env->instructions, new);
	}
}
