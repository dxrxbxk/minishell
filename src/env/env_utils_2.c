/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:27:55 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/23 06:04:44 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_env_export(t_env *print)
{
	t_env	*tmp;

	tmp = lst_copy(print);
	sort_list(tmp);
	while (tmp)
	{
		if (tmp->value)
			printf("export %s=\"%s\"\n", tmp->key, tmp->value);
		else if (tmp->key)
			printf("export %s\n", tmp->key);
		tmp = tmp->next;
	}
	free_env(tmp);
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
