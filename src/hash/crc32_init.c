/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crc32_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 14:59:14 by stoupin           #+#    #+#             */
/*   Updated: 2018/01/10 14:59:17 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crc32.h"

void	crc32_init(t_hash_env *env)
{
	crc32_init_000_024(env->crc32_tab);
	crc32_init_025_049(env->crc32_tab);
	crc32_init_050_074(env->crc32_tab);
	crc32_init_075_099(env->crc32_tab);
	crc32_init_100_124(env->crc32_tab);
	crc32_init_125_149(env->crc32_tab);
	crc32_init_150_174(env->crc32_tab);
	crc32_init_175_199(env->crc32_tab);
	crc32_init_200_224(env->crc32_tab);
	crc32_init_225_249(env->crc32_tab);
	crc32_init_250_255(env->crc32_tab);
}
