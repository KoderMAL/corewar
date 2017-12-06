/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states_special.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 16:24:28 by stoupin           #+#    #+#             */
/*   Updated: 2017/12/06 16:24:29 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main/asm.h"
#include "util/clist.h"

void	state_comment(t_env *env, char c)
{
	if (c == '\n')
	{
		env->state = env->state_next;
		env->state_next = NULL;
	}
}

void    state_number(t_env *env, char c)
{
    if ((c >= '0' && c <= '9') || c == '-' || c == '+')
    {
        if ((c == '+' || c == '-') && env->clist.len > 0)
        {
            env->err = 1;
            env->err_msg = "syntax error while parsing number: misplaced '+' or '-'\n";
        }
        if (clist_push_front(&(env->clist), c))
        {
            env->err = 1;
            env->err_msg = "memory error while parsing number\n";
        }
    }
    else
    {
        env->state = env->state_next;
        env->state_next = NULL;
        env->reread = 1;
    }
}
