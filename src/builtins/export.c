/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:40:44 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/04 16:55:18 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
	else if (str[i] == '\0')
		return (0);
	return (-1);
}

t_env	*lst_copy(t_env *lst)
{
	t_env	*new;

	new = ft_env_new(lst->key, lst->value);
	if (!new)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
		ft_env_addback(&new, ft_env_new(lst->key, lst->value));
	}
	return (new);
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
	//free
}

void	fill_env(t_env *lst, t_env *cpy, char *av, int state)
{
	char *key;
	char *value;
	t_env *new;

	if (state == 1)
	{	
		key = ft_strndup(av, ft_findi(av, '='));
		value = ft_strdup(ft_strchr(av, '=') + 1);
		if (get_env_str(lst, key) != NULL)
			ft_replace_env(lst, key, value);
		else
		{
			new = ft_env_new(key, value);
			ft_env_addback(&lst, new);
		}
	}
	if (state == 2)
	{	
		key = ft_strndup(av, ft_strlen(av));
		value = ft_strndup("", 0);
		new = ft_env_new(key, value);
		ft_env_addback(&cpy, new);
	}
}

int		ft_export(t_env *lst, t_env *cpy, char **av, int ac)
{
	int		i;

	i = 0;
	if (ac == 1)
	{
		sort_list(cpy);
		print_env(cpy);
	}
	while (++i < ac)
	{
		if (export_key(av[i]) > 0)
			fill_env(lst, cpy, av[i], 1);
		else if (export_key(av[i]) == 0)
			fill_env(lst, cpy, av[i], 2);
		else
			ft_error("export: `", av[i], "': not a valid identifier\n");
	}
	return (0);
}
