/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lramirez <lramirez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 16:36:08 by alalaoui          #+#    #+#             */
/*   Updated: 2018/02/17 15:10:31 by lramirez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_H
# define FT_H

# include <string.h>

size_t	        ft_strlen(const char *s);
int		        ft_isprint(int c);
char	        *ft_strchr(const char *s, int c);
int		        ft_atoi(char *str);
int		        ft_isdigit(int c);
int     		ft_str_isdigit(char *s);
int	        	ft_isspace(int c);
int		        ft_strcmp(const char *s1, const char *s2);
char	        *ft_strcpy(char *dst, const char *src);
void        	*ft_memset(void *b, int c, size_t len);
void	        *ft_memcpy(void *dst, const void *src, size_t n);
size_t          ft_intlen(unsigned int n);
char	        *ft_itoa(int n);
void            *ft_memalloc(size_t size);
char            *ft_strnew(size_t size);
unsigned int    ft_abs(int n);


#endif
