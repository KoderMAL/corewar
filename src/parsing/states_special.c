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

void	state_comment(t_env *env, char c)
{
	if (c == '\n')
	{
		env->state = env->state_backup;
		env->state_backup = NULL;
	}
}
