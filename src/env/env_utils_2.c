/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:27:55 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/21 08:15:13 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	create_env_node(t_env **first, void *key, void *value)
{
	t_env *new;

	new = ft_env_new(ft_strdup(key), ft_strdup(value));
	ft_env_addback(first, new);
}

void	ft_env_addback(t_env **first, t_env *new)
{
	t_env	*current;

	current = *first;
	if (!*first)
		*first = new;
	else
	{
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

t_env	*ft_env_new(void *key, void *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	print_env_export(t_env *print)
{
	t_env	*tmp;

	tmp = lst_copy(print);
	sort_list(tmp);
	while (tmp)
	{
		if (tmp->value)
			printf("export %s=\"%s\"\n", tmp->key, tmp->value);
		else if (tmp->key && *tmp->key != '\0')
			printf("export %s\n", tmp->key);
		tmp = tmp->next;
	}
	free_env(tmp);
}

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
