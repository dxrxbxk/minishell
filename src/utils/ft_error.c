/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:33:59 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/15 20:52:19 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_error(char *msg, char *var, char *msg2)
{
	char *print;

	g_status = 1;
	print = ft_mega_join(msg, var, msg2);
	if (!print)
		return (1);
	ft_putstr_fd(print, 2);
	free(print);
	return (-1);
}
