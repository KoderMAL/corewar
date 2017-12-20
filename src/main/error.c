/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 16:19:23 by alalaoui          #+#    #+#             */
/*   Updated: 2017/12/13 11:27:56 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main/asm.h"

int		err(t_env *env, char *s)
{
	env->err = 1;
	env->err_msg = s;
	return (1);
}

int		err_display(t_env *env)
{
	if (env->err)
		openfile_write_str(&(env->stderr), env->err_msg, 1);
	return (env->err);
}
