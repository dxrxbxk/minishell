/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 01:21:49 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/17 19:52:18 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_unset(t_env *lst, char **av, int ac)
{
	t_env *tmp;
	t_env *curr;
	int	i;

	i = 0;
	curr = lst;
	while (++i < ac)
	{
		tmp = curr;
		while (tmp && ft_strcmp(tmp->key, av[i]))
		{
			lst = tmp;
			tmp = tmp->next;
		}
		if (tmp == NULL)
			continue ;
		lst->next = tmp->next;
		ft_env_delone(tmp);
	}
	return (0);
}
