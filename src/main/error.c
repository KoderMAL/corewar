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

#include <unistd.h>
#include <stdlib.h>
#include "main/asm.h"
#include "ft/ft.h"

void		ft_err(t_env *env, char *s)
{
	env->err = 1;
	env->err_msg = s;
}

void		ft_error_check(int err, char *err_msg)
{
	if (err)
		write(1, err_msg, ft_strlen(err_msg));
}
