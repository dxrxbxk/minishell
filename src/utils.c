/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:28:09 by diroyer           #+#    #+#             */
/*   Updated: 2022/10/31 18:30:13 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		ft_error(char *msg, char *var, char *msg2)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(var, 2);
	ft_putstr_fd(msg2, 2);
	return (1);
}

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

void	print_env(t_env *print)
{
	while (print)
	{
		printf("%s %s\n", print->key, print->value);
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

void	ft_replace_env(t_env *lst, char *cmp, char *value)
{
	while (lst)
	{
		if (!ft_strcmp(lst->key, cmp))
		{
			free(lst->value);
			lst->value = value;
		}
		lst = lst->next;
	}
}

void	print_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		printf("%s\n", tab[i]);
}

