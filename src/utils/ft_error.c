/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:33:59 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/16 15:39:20 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_error(char *msg, char *var, char *msg2, int ret)
{
	char *print;

	print = ft_mega_join(msg, var, msg2);
	if (!print)
		return (1);
	ft_putstr_fd(print, 2);
	free(print);
	return (ret);
}
