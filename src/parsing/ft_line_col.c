/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line_col.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 13:26:37 by alalaoui          #+#    #+#             */
/*   Updated: 2017/12/06 13:48:17 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main/asm.h"
#include "parsing.h"

void		ft_line_col(t_env *env, char c)
{
	if (c == '\n')
	{
		env->col = 0;
		env->line++;
	}
	else if (ft_isprint(c) || c == '\t' || c == ' ')
		env->col++;
}
