/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:34:03 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/23 05:31:10 by diroyer          ###   ########.fr       */
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

static void	replace_pwd(char *replace, t_env **lst)
{
	char	*cwd;
	t_env	*new;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return ;
	if (!get_key_value(*lst, replace))
	{
		new = ft_env_new(ft_strdup(replace), cwd);
		ft_env_addback(lst, new);
	}
	else
		ft_replace_env(*lst, ft_strdup(replace), cwd);
}

int	ft_cd(t_env **lst, char **av, int ac)
{
	if (ac == 1)
	{
		replace_pwd("OLDPWD", lst);
		if (get_key_value(*lst, "HOME") && chdir(get_key_value(*lst, "HOME")))
			return (ft_error("cd: HOME not set", NULL, NULL, 1));
		else
			ft_replace_env(*lst, "PWD", ft_strdup(get_key_value(*lst, "HOME")));
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
