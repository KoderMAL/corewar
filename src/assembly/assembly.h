/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembly.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhadley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 15:10:38 by dhadley           #+#    #+#             */
/*   Updated: 2018/01/15 13:40:32 by dhadley          ###   ########.fr       */
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
** from first_pass.c
*/

void	first_pass(unsigned char *champ, t_pqueue instructions, t_pqueue *gaps);

/*
** from second_pass.c
*/

void	second_pass(unsigned char *champ, t_pqueue gaps);

/*
** from store_locations.c
*/ 

void	store_label(int LC, t_label *label);
void	store_gap(int *LC, t_pqueue *gaps, t_argument *arg, int has_idx);

/*
** from encode_bytes.c
*/

void			encode_1_byte(unsigned char *champ, int *LC, int value);
void			encode_2_byte(unsigned char *champ, int *LC, int value);
void			encode_4_byte(unsigned char *champ, int *LC, int value);
unsigned char	encode_param_byte(t_pqueue args);

/*
** assemble_op.c
*/

void	assemble_op(unsigned char *champ, int *LC, t_pqueue *gaps, t_pqueue args, t_instruction *instruction);

#endif
