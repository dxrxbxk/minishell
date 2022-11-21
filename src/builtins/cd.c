/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:34:03 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/21 02:12:09 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	cd_error(char *av)
{
	char	*error;

	error = ft_strjoin(av, ": ");
	if (!error)
		return (1);
	ft_error("cd: ", error, strerror(errno), 1);
	free(error);
	return (1);
}

static void	replace_pwd(char *replace, t_env *lst)
{
	char	*cwd;
	t_env	*new;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return ;
	if (!get_key_value(lst, replace))
	{
		new = ft_env_new(replace, cwd);
		ft_env_addback(&lst, new);
	}
	else
		ft_replace_env(lst, replace, cwd);
}

static int	swap_old_pwd(char *wd, t_env *lst)
{
	char 	*old;

	(void)wd;
	if (!get_env_key(lst, "OLDPWD") && !get_env_key(lst, "OLDPWD"))
		return (ft_error("cd: OLDPWD not set", NULL, NULL, 1));
	if (ft_strcmp(get_key_value(lst, "PWD"), get_key_value(lst, "OLDPWD")))
	{
		old = ft_strdup(get_key_value(lst, "PWD"));
		if (!chdir(get_key_value(lst, "OLDPWD")))
		{
			replace_pwd("PWD", lst);
			ft_replace_env(lst, "OLDPWD", old);
			printf("%s\n", get_key_value(lst, "PWD"));
		}
		else
			return (ft_error("cd: OLDPWD not set", NULL, NULL, 1));
	}
	else
		printf("%s\n", get_key_value(lst, "PWD"));
	return (0);
}

int	ft_cd(t_env *lst, char **av, int ac)
{
	if (ac == 2 && !ft_strcmp(av[1], "-"))
		return (swap_old_pwd(av[1], lst));
	else if (ac == 1)
	{
		replace_pwd("OLDPWD", lst);
		if (!get_key_value(lst, "HOME") && chdir(get_key_value(lst, "HOME")))
			return (ft_error("cd: HOME not set", NULL, NULL, 1));
		else
			ft_replace_env(lst, "PWD", ft_strdup(get_key_value(lst, "HOME")));
	}
	else if (ac == 2)
	{
		replace_pwd("OLDPWD", lst);
		if (!chdir(av[1]))
			replace_pwd("PWD", lst);
		else
			return (cd_error(av[1]));
	}
	else
		return (ft_error("cd : too many arguments", NULL, NULL, 1));
	return (0);
}
