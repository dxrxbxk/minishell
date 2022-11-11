/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:40:44 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/11 20:59:23 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	export_key(char *str, int *join)
{
	int	i;

	i = 0;
	if (str[0] != '_' && !ft_isalpha(str[0]))
		return (-1);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	if (str[i] == '+' && str[i + 1] == '=')
	{
		*join = 1;
		return (i + 1);
	}
	else if (str[i] == '=')
		return (i);
	else if (str[i] == '\0')
		return (0);
	return (-1);
}

static void	fill_env(t_env *lst, char *av, int join)
{
	char *key;
	char *value;
	t_env *new;

	if (join)
		key = ft_strndup(av, ft_findi(av, '+'));
	else
		key = ft_strndup(av, ft_findi(av, '='));
	value = ft_strdup(ft_strchr(av, '=') + 1);
	if (get_env_str(lst, key) != NULL && join == 0)
		ft_replace_env(lst, key, value);
	else if (get_env_str(lst, key) != NULL && join == 1)
		ft_join_env(lst, key, value);
	else
	{
		new = ft_env_new(key, value);
		ft_env_addback(&lst, new);
	}
}

static void	fill_env_cpy(t_env *cpy, char *av)
{
	char *key;
	char *value;
	t_env *new;

	key = ft_strndup(av, ft_strlen(av));
	if (!get_env_str(cpy, key))
	{
		value = NULL;
		new = ft_env_new(key, value);
		ft_env_addback(&cpy, new);
	}
}

int		ft_export(t_env *lst, char **av, int ac)
{
	int		i;
	int		join;

	i = 0;
	join = 0;
	if (ac == 1)
		print_env_export(lst);
	while (++i < ac)
	{
		if (export_key(av[i], &join) > 0)
			fill_env(lst, av[i], join);
		else if (export_key(av[i], &join) == 0)
			fill_env_cpy(lst, av[i]);
		else
			ft_error("export: `", av[i], "': not a valid identifier\n");
	}
	return (0);
}
