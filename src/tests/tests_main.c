/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 11:46:47 by stoupin           #+#    #+#             */
/*   Updated: 2018/01/16 11:46:47 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"
#include "ft/ft_test.h"
#include "util/pqueue_test.h"
#include "util/cqueue_test.h"

int	main(void)
{
	t_tests_env	env;

	tests_init(&env);
	ft_test(&env);
	pqueue_test(&env);
	cqueue_test(&env);
	tests_exit(&env, 0);
	return (0);
}
