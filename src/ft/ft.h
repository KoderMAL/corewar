/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 16:36:08 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/11 14:13:09 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_H
# define FT_H

# include <string.h>

size_t	ft_strlen(const char *s);
int		ft_isprint(int c);
char	*ft_strchr(const char *s, int c);
int		ft_atoi(char *str);
int		ft_isdigit(int c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcpy(char *dst, const char *src);

#endif
