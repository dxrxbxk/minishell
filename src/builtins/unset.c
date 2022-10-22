/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 01:21:49 by diroyer           #+#    #+#             */
/*   Updated: 2022/10/22 02:18:32 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	unset(t_env *lst, char *str)
{
	t_env *tmp;

	tmp = lst;
	if (tmp && !ft_strcmp(tmp->key, str))
	{
		lst = tmp->next;
		free(tmp);
		return ;
	}
	while (tmp && ft_strcmp(tmp->key, str))
	{
		lst = tmp;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return ;
	lst->next = tmp->next;
	free(tmp);
}
