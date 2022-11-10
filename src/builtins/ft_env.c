/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 02:59:26 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/10 16:23:21 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// need to add argc for error management

void	ft_env(t_env *lst, char **av, int ac)
{
	(void)av;
	if (ac > 1)
		ft_error("env:", "", " too many arguments\n");
	print_env(lst);
}
