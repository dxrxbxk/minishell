/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:19:46 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/21 15:50:00 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	last_elem(t_env **elm)
{
	*elm = malloc(sizeof(t_env));
	if (!*elm)
		return (-1);
	(*elm)->key = ft_strndup("", 0);
	if (!(*elm)->key)
		return (-1);
	(*elm)->value = ft_strdup("");
	if (!(*elm)->value)
		return (-1);
	elm = &((*elm)->next);
	(*elm) = NULL;
	return (0);
}

void	create_env_node(t_env **first, void *key, void *value)
{
	t_env	*new;

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
