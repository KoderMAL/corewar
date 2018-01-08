/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembly.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhadley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 15:10:38 by dhadley           #+#    #+#             */
/*   Updated: 2018/01/08 18:36:44 by dhadley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSEMBLY_H
# define ASSEMBLY_H

/*
** from assemble.c
*/

void	assemble(t_env *env);

/*
** from first_pass.c
*/

void	store_location(t_env *env);
void	(*assemble_op)(char *champion, t_pqueue *gaps, int *LC, t_pqueue 

/*
** from second_pass.c
*/

/*
** conversion functions
*/

void	assemble_live(char *champ, int *LC, t_pqueue *gaps, t_pqueue args);
void	assemble_ld(char *champ, int *LC, t_pqueue *gaps, t_pqueue args);
void	assemble_st(char *champ, int *LC, t_pqueue *gaps, t_pqueue args);
void	assemble_add(char *champ, int *LC, t_pqueue *gaps, t_pqueue args);
void	assemble_sub(char *champ, int *LC, t_pqueue *gaps, t_pqueue args);
void	assemble_and(char *champ, int *LC, t_pqueue *gaps, t_pqueue args);
void	assemble_or(char *champ, int *LC, t_pqueue *gaps, t_pqueue args);
void	assemble_xor(char *champ, int *LC, t_pqueue *gaps, t_pqueue args);
void	assemble_zjump(char *champ, int *LC, t_pqueue *gaps, t_pqueue args);
void	assemble_ldi(char *champ, int *LC, t_pqueue *gaps, t_pqueue args);
void	assemble_sti(char *champ, int *LC, t_pqueue *gaps, t_pqueue args);
void	assemble_fork(char *champ, int *LC, t_pqueue *gaps, t_pqueue args);
void	assemble_lld(char *champ, int *LC, t_pqueue *gaps, t_pqueue args);
void	assemble_lldi(char *champ, int *LC, t_pqueue *gaps, t_pqueue args);
void	assemble_lfork(char *champ, int *LC, t_pqueue *gaps, t_pqueue args);
void	assemble_aff(char *champ, int *LC, t_pqueue *gaps, t_pqueue args);


#endif
