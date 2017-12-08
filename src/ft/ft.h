/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 16:36:08 by alalaoui          #+#    #+#             */
/*   Updated: 2017/12/08 15:22:09 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_H
# define FT_H

# include <string.h>

size_t	ft_strlen(const char *s);
void	ft_bzero(void *s, size_t n);
int		ft_isprint(int c);
char	*ft_strchr(const char *s, int c);

#endif
