/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhadley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 11:51:04 by dhadley           #+#    #+#             */
/*   Updated: 2018/01/26 12:23:23 by dhadley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Pseudocode for each cycle **


ft_cycles(params)
{
	while (game_cycle < INT_MAX)
	{
		ft_check_stuff(t_vm vm, game_cycle);
		ft_check_countdown(t_vm vm);
		game_cycle++;
	}
}

--------------

ft_check_stuff(t_vm *vm, cycles)
{
	//check if delta--
	for each threads
		//check nbr lives stuff
		//check if thread is dead (and pop)
}
 
--------------

ft_check_countdown(t_vm *vm)
{
	while (threads)
	{
		if (thread->countdown == -1)
		{
			if (map[thread->location] == opcode)
				{
					thread->countdown = opcode->cycles;
					thread->location++;
				}
			else
				thread->location++;
		}
		else if (thread->countdown == 0)
		{
			do_op(opcode);
		}
		else
			thread->countdown--;
		thread = thread->next;
	}
}

**
**
