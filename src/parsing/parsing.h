/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 16:36:08 by alalaoui          #+#    #+#             */
/*   Updated: 2017/12/05 18:17:01 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "main/asm.h"

void	state_0(t_env *env, char c);
void	state_1(t_env *env, char c);
void	state_2(t_env *env, char c);
void	state_3(t_env *env, char c);
void	state_4(t_env *env, char c);
void	state_5(t_env *env, char c);
void	state_6(t_env *env, char c);
void	state_7(t_env *env, char c);
void	state_8(t_env *env, char c);
void	state_9(t_env *env, char c);

#endif
