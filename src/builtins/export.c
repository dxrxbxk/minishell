/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:40:44 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/09 14:40:34 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int		export_key(char *str)
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

static void	fill_env(t_env *lst, t_env *cpy, char *av)
{
	char *key;
	char *value;
	t_env *new;

		key = ft_strndup(av, ft_findi(av, '='));
		value = ft_strdup(ft_strchr(av, '=') + 1);
		if (get_env_str(cpy, key) != NULL)
		{
			ft_replace_env(lst, key, value);
			ft_replace_env(cpy, key, value);
		}
		else
		{
			printf("2222222222222222222222222222\n");
			new = ft_env_new(key, value);
			ft_env_addback(&lst, new);
			ft_env_addback(&cpy, new);
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
		print_env(cpy, 1);
		print_env(lst, 0);
	}
	while (++i < ac)
	{
		if (export_key(av[i]) > 0)
			fill_env(lst, cpy, av[i]);
		else if (export_key(av[i]) == 0)
			fill_env_cpy(cpy, av[i]);
		else
			ft_error("export: `", av[i], "': not a valid identifier\n");
	}
	return (0);
}
