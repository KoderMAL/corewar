/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembly.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 15:10:38 by dhadley           #+#    #+#             */
/*   Updated: 2018/01/23 12:42:54 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSEMBLY_H
# define ASSEMBLY_H

#include "main/asm.h"

/*
** from assemble.c
*/

void	assemble(t_env *env);

/*
** from pass.c
*/

int		pass(t_env *env, t_pqueue instructions, t_pqueue *gaps, int pass);

/*
** from store_locations.c
*/ 

void	store_label(int LC, t_label *label);
void	store_gap(int *LC, t_pqueue *gaps, t_argument arg, int has_idx, int gapLC);

/*
** from encode_bytes.c
*/

void			encode_1_byte(unsigned char *champ, int *LC, int value);
void			encode_2_bytes(unsigned char *champ, int *LC, int value);
void			encode_4_bytes(unsigned char *champ, int *LC, int value);
unsigned char	encode_param_byte(t_instruction *instruction);

/*
** assemble_op.c
*/

void	assemble_op(unsigned char *champ, int *LC, t_pqueue *gaps, t_instruction *instruction);
void	assemble_op_fake(int *LC, t_pqueue *gaps, t_instruction *instruction);

#endif
