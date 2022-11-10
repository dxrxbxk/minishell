/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:24:57 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/10 16:25:28 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_env_addback(t_env **first, t_env *new)
{
	t_env *current;

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
	t_env *new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key= key;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	print_env_export(t_env *print)
{
	t_env *tmp;
	t_env *curr;

	tmp = lst_copy(print);
	sort_list(tmp);
	curr = tmp;
	while (tmp)
	{
		printf("export %s=\"%s\"\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	while (curr)
	{
		free(curr);
		curr = curr->next;
	}
}

void	print_env(t_env *print)
{
	while (print)
	{
		if (*print->value != '\0')
			printf("%s=%s \n", print->key, print->value);
		print = print->next;
	}
}

char	*get_env_str(t_env *lst, char *get)
{
	while (lst)
	{
		if (!ft_strcmp(lst->key, get))
			return (lst->value);
		lst = lst->next;
	}
	return (NULL);
}

void	ft_join_env(t_env *lst, char *cmp, char *value)
{
	char *tmp;

	while (lst)
	{
		if (!ft_strcmp(lst->key, cmp))
		{
			tmp = lst->value;
			lst->value = ft_strjoin(lst->value, value);
			free(tmp);
		}
		lst = lst->next;
	}
}

void	ft_replace_env(t_env *lst, char *cmp, char *value)
{
	while (lst)
	{
		if (!ft_strcmp(lst->key, cmp))
		{
			free(lst->value);
			lst->value = NULL;
			lst->value = ft_strdup(value);
		}
		lst = lst->next;
	}
}
