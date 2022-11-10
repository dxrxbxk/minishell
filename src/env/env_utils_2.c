/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:27:55 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/10 16:01:38 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_env	*lst_copy(t_env *lst)
{
	t_env	*new;

	new = ft_env_new(lst->key, lst->value);
	if (!new)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
		ft_env_addback(&new, ft_env_new(lst->key, lst->value));
	}
	return (new);
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
	//free
}
