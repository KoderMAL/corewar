/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembly.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 15:10:38 by dhadley           #+#    #+#             */
/*   Updated: 2018/02/08 11:29:44 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSEMBLY_H
# define ASSEMBLY_H

# include "asm.h"

/*
** from assemble.c
*/

void			assemble(t_env *env);

/*
** from pass.c
*/

int				pass(t_env *env, t_pqueue instructions, t_pqueue *gaps,
						int pass);

/*
** from store_locations.c
*/

void			store_label(int lc, t_label *label);
t_gap			*create_gap(int *lc, t_argument arg, int has_idx, int gaplc);

/*
** from encode_bytes.c
*/

void			encode_1_byte(unsigned char *champ, int *lc, int value);
void			encode_2_bytes(unsigned char *champ, int *lc, int value);
void			encode_4_bytes(unsigned char *champ, int *lc, int value);
void			encode_bytes(unsigned char *champ, int *lc, int value, int n);
unsigned char	encode_param_byte(t_instruction *instruction);

/*
** assemble_op.c
*/

void			assemble_op(t_env *env, int *lc, t_pqueue *gaps,
							t_instruction *instruction);
int				assemble_op_fake(t_env *env, int *lc, t_pqueue *gaps,
									t_instruction *instruction);

#endif
