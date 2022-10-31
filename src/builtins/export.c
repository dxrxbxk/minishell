/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:40:44 by diroyer           #+#    #+#             */
/*   Updated: 2022/10/31 18:25:59 by diroyer          ###   ########.fr       */
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
	return (-1);
}

t_env	*lst_copy(t_env *lst)
{
	t_env	*new;

	new = ft_env_new(lst->key, lst->value);
	while (lst->next)
	{
		lst = lst->next;
		ft_env_addback(&new, ft_env_new(lst->key, lst->value));
	}
	return (new);
}


void	sort_list(t_env *tosort)
{
	t_env	*lst;
	t_env	*cmp;

	lst = lst_copy(tosort);
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
		printf("export %s %s\n", lst->key, lst->value);
		lst = lst->next;
	}
}

int		ft_export(t_env *lst, char **av, int ac)
{
	t_env	*new;
	char *key;
	char *value;
	int	i;

	i = 0;
	if (ac == 1)
		sort_list(lst);
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
			ft_error("export: `", av[i], "': not a valid identifier\n");
	}
	return (0);
}
