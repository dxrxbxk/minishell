/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_findi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 18:44:03 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/02 20:40:49 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_findi(char *str, char find)
{
	int	i;

	i = 0;
	if (!str || !find)
		return (-1);
	while (str[i] && str[i] != find)
		i++;
	if (str[i] == find)
		return (i);
	return (-1);
}
