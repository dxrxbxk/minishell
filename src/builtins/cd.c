/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:34:03 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/20 20:01:21 by diroyer          ###   ########.fr       */
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

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return ;
	ft_replace_env(lst, replace, cwd);
}

static int	swap_pwd(char *wd, t_env *lst)
{
	static int	i = 0;

	if (ft_strcmp(get_key_value(lst, "PWD"), get_key_value(lst, "OLDPWD")))
	{
		if (i == 0)
		{
			if (!chdir(wd))
				replace_pwd("PWD", lst);
			else
				return (cd_error(wd));
			i = 1;
		}
		else
		{
			if (!chdir(wd))
				replace_pwd("OLDPWD", lst);
			else
				return (cd_error(wd));
			i = 0;
		}
	}
	return (0);
}

int	ft_cd(t_env *lst, char **av, int ac)
{
	int		i;

	i = 1;
	while (ac > 1 && av[i][0] == '-' && ac--)
		i++;
	if (ac == 1 || ac == 2)
	{
		replace_pwd("OLDPWD", lst);
		if (ac == 1 && chdir(get_key_value(lst, "HOME")))
			return (ft_error("cd: HOME not set", NULL, NULL, 1));
		else
			ft_replace_env(lst, "PWD", ft_strdup(get_key_value(lst, "HOME")));
		if (ac == 2)
		{
			if (!ft_strcmp(av[i], "-"))
				return (swap_pwd(av[i], lst));
			if (!chdir(av[i]))
				replace_pwd("PWD", lst);
			else
				return (cd_error(av[i]));
		}
	}
	else
		return (ft_error("cd : too many arguments", NULL, NULL, 1));
	return (0);
}
