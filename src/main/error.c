/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 16:19:23 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/17 14:50:43 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main/asm.h"

int		err(t_env *env, char *s, int col_back)
{
	env->err = 1;
	env->err_msg = s;
	if (col_back < 0)
		env->col = -1;
	else
		env->col -= col_back;
	return (1);
}

int		err_display(t_env *env)
{
	if (env->err && ft_strlen(env->err_msg) > 0)
	{
		openfile_write_str(&(env->stderr), "Error: ", 0);
		openfile_write_str(&(env->stderr), env->err_msg, 1);
		if (env->col >= 0)
		{
			openfile_write_str(&(env->stderr), "at line ", 0);
			openfile_write_nbr(&(env->stderr), env->line + 1, 0);
			openfile_write_str(&(env->stderr), ", column ", 0);
			openfile_write_nbr(&(env->stderr), env->col + 1, 1);
		}
	}
	return (env->err);
}
