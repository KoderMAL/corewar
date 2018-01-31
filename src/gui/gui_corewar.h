/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_corewar.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 09:58:14 by stoupin           #+#    #+#             */
/*   Updated: 2018/01/30 16:46:02 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_COREWAR_H
# define GUI_COREWAR_H

# include "corewar/vm.h"
# include "gui.h"

/*
** gui_hooks.c
*/

int		gui_close(t_vm *vm);
int		gui_key_pressed(int key, t_vm *vm);
int		gui_redraw(t_vm *vm);
void	gui_init_hooks(t_vm *vm);

/*
** fonts.c
*/

int		fonts_load(t_vm *vm);
void	fonts_clean(t_vm *vm);

#endif
