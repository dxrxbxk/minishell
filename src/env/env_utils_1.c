/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:24:57 by diroyer           #+#    #+#             */
/*   Updated: 2022/12/09 02:03:31 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_env(t_env *print)
{
	while (print)
	{
		if (print->value != NULL && *print->key != '\0')
			printf("%s=%s\n", print->key, print->value);
		print = print->next;
	}
}

char	*get_key_value(t_env *lst, char *get)
{
	while (lst)
	{
		if (!ft_strcmp(lst->key, get))
			return (lst->value);
		lst = lst->next;
	}
	return (NULL);
}

char	*get_env_key(t_env *lst, char *get)
{
	while (lst)
	{
		if (!ft_strcmp(lst->key, get))
			return (lst->key);
		lst = lst->next;
	}
	return (NULL);
}

void	ft_join_env(t_env *lst, char *cmp, char *value)
{
	char	*tmp;

	while (lst)
	{
		if (!ft_strcmp(lst->key, cmp))
		{
			free(cmp);
			tmp = lst->value;
			lst->value = ft_strjoin(lst->value, value);
			free(tmp);
			free(value);
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
			lst->value = value;
		}
		lst = lst->next;
	}
}