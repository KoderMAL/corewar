/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhadley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 14:26:46 by dhadley           #+#    #+#             */
/*   Updated: 2018/01/11 19:16:00 by dhadley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	assemble(t_env *env)
{
	t_pqueue	gaps;

	pqueue_init(&gaps);
	ft_memset(env->champion, '\0', CHAMP_MAX_SIZE);
	first_pass(env->champion, env->instructions, &gaps);
	second_pass(env->champion, gaps);

}
