/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 15:10:43 by alalaoui          #+#    #+#             */
/*   Updated: 2017/12/13 18:13:20 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main/asm.h"
#include "parsing.h"

void			parse_arguments(t_env *env)
{
	char		*args;
	char		**split;
	int			i;

	i = 0;
	args = clist_join(&env->clist);
	if ((split = ft_strsplit(args, ',')) == NULL)
		ft_err(env, "memory error while using malloc");
	env->commands->op = env->op;
	while (args[i])
	{
		if (args[i] == '%' && args[i + 1] == ':')
			env->commands->args.type = T_DIR;
		else if (args[i] == 'r')
			env->commands->args.type = T_REG;
		else if (args[i] == '%')
			env->commands->args.type = T_IND; // ?
	}
	free_split(&split);
}
