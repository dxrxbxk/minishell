/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_to_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 09:45:00 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/11 21:11:42 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int lst_size(t_env *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

char	**lst_to_tab(t_env *lst)
{
	char	**tab;
	t_env	*curr;
	int		i;

	curr = lst;
	tab = calloc(sizeof(char *), lst_size(lst) + 1);
	if (!tab)
		return (NULL);
	i = 0;
	while (curr)
	{
		if (curr->value)
			tab[i] = ft_mega_join(curr->key, "=", curr->value);
		curr = curr->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}