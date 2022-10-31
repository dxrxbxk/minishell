/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:40:44 by diroyer           #+#    #+#             */
/*   Updated: 2022/10/28 20:34:51 by diroyer          ###   ########.fr       */
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

int		ft_export(t_env *lst, char **av, int ac)
{
	t_env	*new;
	char *key;
	char *value;
	int	i;

	i = 0;
	if (ac == 1)
		ft_env(lst);
	while (++i < ac)
	{
		if (av[i] && export_key(av[i]) > 0)
		{
			key = ft_strndup(av[i], ft_findi(av[i], '='));
			value = ft_strdup(ft_strchr(av[i], '=') + 1);
			if (get_env_str(lst, key) != NULL)
				ft_replace_env(lst, key, value);
			else
			{
				new = ft_env_new(key, value);
				ft_env_addback(&lst, new);
			}
		}
		else
			printf("not valid id %s\n", av[i]);
	}
	return (0);
}
