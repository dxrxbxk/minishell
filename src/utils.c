/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:28:09 by diroyer           #+#    #+#             */
/*   Updated: 2022/10/22 02:03:17 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

