/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crc32.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 14:58:03 by stoupin           #+#    #+#             */
/*   Updated: 2018/01/10 14:58:05 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CRC32_H
# define CRC32_H

typedef struct	s_hash_env
{
	unsigned long	crc32_tab[256];
}				t_hash_env;

/*
** crc32_init_0.c
*/

void			crc32_init_000_024(unsigned long *tab);
void			crc32_init_025_049(unsigned long *tab);
void			crc32_init_050_074(unsigned long *tab);
void			crc32_init_075_099(unsigned long *tab);

/*
** crc32_init_1.c
*/

void			crc32_init_100_124(unsigned long *tab);
void			crc32_init_125_149(unsigned long *tab);
void			crc32_init_150_174(unsigned long *tab);
void			crc32_init_175_199(unsigned long *tab);

/*
** crc32_init_2.c
*/

void			crc32_init_200_224(unsigned long *tab);
void			crc32_init_225_249(unsigned long *tab);
void			crc32_init_250_255(unsigned long *tab);

/*
** crc32_init.c
*/

void			crc32_init(t_hash_env *env);

/*
** crc32.c
*/

unsigned int	crc32_hash(t_hash_env *env, char *keystring);

#endif
