/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 14:26:46 by dhadley           #+#    #+#             */
/*   Updated: 2018/01/23 14:33:51 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "assembly.h"

void	assemble(t_env *env)
{
	t_pqueue	gaps;
	
	pqueue_init(&gaps);
	env->prog_size = pass(env, env->instructions, &gaps, 1);
	if (env->err == 0 && env->prog_size > 0)
	{
		env->champion = (unsigned char*)malloc(sizeof(unsigned char) * env->prog_size);
		if (env->champion == NULL)
		{
			err(env, "memory error", -1);
			return ;
		}
		ft_memset(env->champion, '\0', env->prog_size);
	}
	if (env->err == 0)
		pass(env, env->instructions, &gaps, 2);
	pqueue_delete(&gaps);
}
