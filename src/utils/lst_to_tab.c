/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_to_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 09:45:00 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/10 10:46:41 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*ft_strjoin_tab(char *s1, char *s2, char *s3)
{
	size_t	len;
	char	*array;

	if (!s1 && !s2 && !s3)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	array = malloc(sizeof(char) * (len + 1));
	if (!array)
		return (NULL);
	array[0] = '\0';
	ft_strcpy(array, s1);
	ft_strcat(array, s2);
	ft_strcat(array, s3);
	return (array);
}

char	**lst_to_tab(t_env *lst)
{
	char **tab;
	int	i;
	t_env	*curr;

	curr = lst;
	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	tab = calloc(sizeof(char *), i + 1);
	if (!tab)
		return (NULL);
	i = 0;
	while (curr)
	{
		tab[i] = ft_strjoin_tab(curr->key, "=", curr->value);
		curr = curr->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
