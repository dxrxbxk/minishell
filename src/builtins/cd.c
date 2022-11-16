/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:34:03 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/16 14:51:17 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	replace_pwd(char *replace, t_env *lst)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return ;
	ft_replace_env(lst, replace, cwd);
}

int	ft_cd(t_env *lst, char **av, int ac)
{
	int	i;

	i = 1;
	while (ac > 1 && av[i][0] == '-' && ac--)
		i++;
	if (ac == 1 || ac == 2)
	{
		replace_pwd("OLDPWD", lst);
		if (ac == 1 && chdir(get_key_value(lst, "HOME")))
				ft_error("cd: HOME not set\n", NULL, NULL, 1);
		if (ac == 2)
		{
			if (!chdir(av[i]))
				replace_pwd("PWD", lst);
			else
				ft_error("cd: ", av[i], ": No such file or directory\n", 1);
		}
	}
	else
		ft_error("cd : too many arguments\n", NULL, NULL, 1);
	return (0);
}
