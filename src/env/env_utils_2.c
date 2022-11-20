/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:27:55 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/20 19:23:14 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_env_delone(t_env *elem)
{
	free(elem->key);
	free(elem->value);
	free(elem);
}

void	free_env(t_env *lst)
{
	t_env	*tmp;

	tmp = NULL;
	while (lst)
	{
		tmp = lst->next;
		ft_env_delone(lst);
		lst = tmp;
	}
}

t_env	*lst_copy(t_env *lst)
{
	t_env	*first;
	t_env	*elem;

	first = NULL;
	while (lst)
	{
		elem = ft_env_new(lst->key, lst->value);
		if (!elem)
			return (NULL);
		ft_env_addback(&first, elem);
		lst = lst->next;
	}
	return (first);
}


void	sort_list(t_env *lst)
{
	t_env	*cmp;

	cmp = lst;
	while (lst)
	{
		if (lst->next)
			cmp = lst->next;
		while (cmp)
		{
			if (ft_strcmp(lst->key, cmp->key) > 0)
			{
				ft_swap_str(&lst->key, &cmp->key);
				ft_swap_str(&lst->value, &cmp->value);
			}
			cmp = cmp->next;
		}
		lst = lst->next;
	}
}
