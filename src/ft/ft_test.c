/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 11:28:02 by stoupin           #+#    #+#             */
/*   Updated: 2018/01/17 11:28:03 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/tests.h"
#include "ft_test.h"

void	ft_test(t_tests_env *env)
{
	tests_print(env, "\nTesting ft\n");
	ft_atoi_test(env);
	ft_strchr_test(env);
}
