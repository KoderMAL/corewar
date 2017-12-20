/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 14:37:28 by alalaoui          #+#    #+#             */
/*   Updated: 2017/10/05 14:44:20 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void			free_split(char ***split)
{
	int			j;

	j = 0;
	while ((*split)[j])
		free((*split)[j++]);
	free(*split);
}