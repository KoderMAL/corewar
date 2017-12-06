/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 16:36:08 by alalaoui          #+#    #+#             */
/*   Updated: 2017/12/06 13:26:24 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "main/asm.h"
# include "ft/ft.h"

void	state_comment(t_env *env, char c);

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

void	state_10(t_env *env, char c);
void	state_11(t_env *env, char c);
void	state_12(t_env *env, char c);
void	state_13(t_env *env, char c);
void	state_14(t_env *env, char c);

void	state_15(t_env *env, char c);
void	state_16(t_env *env, char c);
void	state_17(t_env *env, char c);
void	state_18(t_env *env, char c);
void	state_19(t_env *env, char c);

void	ft_line_col(t_env *env, char c);

#endif
