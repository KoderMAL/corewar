/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_hooks.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 09:58:14 by stoupin           #+#    #+#             */
/*   Updated: 2018/01/29 10:01:56 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_HOOKS_H
# define GUI_HOOKS_H

/*
** This header is separated from gui.h to avoid circular include
** between vm.h and gui.h
*/

# include "corewar/vm.h"
# include "gui.h"

/*
** gui_hooks.c
*/

int						gui_close(t_vm *vm);
int						gui_key_pressed(int key, t_vm *vm);
int						gui_redraw(t_vm *vm);
void					gui_init_hooks(t_vm *vm);

#endif
