/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhadley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 14:26:46 by dhadley           #+#    #+#             */
/*   Updated: 2018/01/16 16:15:04 by dhadley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembly.h"

void	assemble(t_env *env)
{
	t_pqueue	gaps;
	
	pqueue_init(&gaps);
	ft_memset(env->champion, '\0', CHAMP_MAX_SIZE);
	env->prog_size = first_pass(env->champion, env->instructions, &gaps);
	second_pass(env->champion, gaps);
}
