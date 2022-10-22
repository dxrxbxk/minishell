/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:40:44 by diroyer           #+#    #+#             */
/*   Updated: 2022/10/22 13:53:08 by diroyer          ###   ########.fr       */
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

int		export_key(char *str)
{
	int	i;

	i = 0;
	if (str[0] != '_' && !ft_isalpha(str[0]))
		return (-1);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	if (str[i] == '=')
		return (i);
	return (-1);
}

int		ft_export(t_env *lst, char *str)
{
	t_env	*new;
	char *key;
	char *value;

	if (str && export_key(str) > 0)
	{
		key = ft_strndup(str, ft_findi(str, '='));
		value = ft_strdup(ft_strchr(str, '=') + 1);
		if (get_env_str(lst, key) != NULL)
			ft_replace_env(lst, key, value);
		else
		{
			new = ft_env_new(key, value);
			ft_env_addback(&lst, new);
		}
	}
	else
		printf("error export\n");
	if (*str == '\0')
		print_env(lst);
	else
		print_env(lst); //del this
	return (0);
}
