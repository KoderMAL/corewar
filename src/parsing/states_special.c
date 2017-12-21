/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states_special.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 16:24:28 by stoupin           #+#    #+#             */
/*   Updated: 2017/12/13 15:03:10 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main/asm.h"
#include "util/cqueue.h"

/*void    state_number(t_env *env, char c)
{
    if ((c >= '0' && c <= '9') || c == '-' || c == '+')
    {
        if ((c == '+' || c == '-') && env->cqueue.len > 0)
            err(env, "syntax error while parsing number: misplaced '+' or '-'");
        if (cqueue_push(&(env->cqueue), c))
            err(env, "memory error while parsing number");
    }
    else
    {
        env->state = env->state_next;
        env->state_next = NULL;
        env->reread = 1;
    }
}
*/