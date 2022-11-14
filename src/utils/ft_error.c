/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:33:59 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/14 19:24:44 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>
#include <minishell.h>

void	ft_error(char *msg, char *var, char *msg2)
{
	char *print;

	g_status = 1;
	print = ft_mega_join(msg, var, msg2);
	if (!print)
		return ;
	ft_putstr_fd(print, 2);
	free(print);
}
