/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 13:16:44 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/15 17:31:05 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "asm.h"
#include "util/cqueue.h"

/*
** duplicates an argument
*/

t_argument	*arg_from_cqueue(t_cqueue *cqueue)
{
	t_argument	*argument;

	argument = (t_argument*)malloc(sizeof(t_argument) +
			sizeof(char) * (cqueue->len + 1));
	if (argument == NULL)
		return (NULL);
	argument->name = (char*)argument + sizeof(t_argument);
	ft_cqueue_move(argument->name, cqueue);
	argument->type = 0;
	argument->lab_type = 0;
	argument->value = 0;
	argument->label = NULL;
	return (argument);
}

t_argument	*argument_dup(t_argument *argument)
{
	t_argument	*new_argument;

	new_argument = (t_argument*)malloc(sizeof(t_argument) + 
			sizeof(char) * (ft_strlen(argument->name) + 1));
	if (new_argument == NULL)
		return (NULL);
	new_argument->name = (char*)new_argument + sizeof(t_argument);
	ft_strcpy(new_argument->name,argument->name);
	new_argument->type = argument->type;
	new_argument->lab_type = argument->lab_type;
	new_argument->value = argument->value;
	new_argument->label = argument->label;
	return (new_argument);
}
