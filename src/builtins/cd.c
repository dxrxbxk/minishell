/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:34:03 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/19 23:57:10 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_symlink(char *path)
{
	struct	stat sb;
	char 	*sym;
	int 	i;

	i = -1;
	sym = NULL;
	while (path[++i])
		;
//	if (path[i - 1] == '/')
//		path[i - 1] = 0;
	if (lstat(path, &sb) == -1)
		perror("lstat");
	if (sb.st_mode & S_IFLNK)
	{
		printf("sym = %s\n", sym);
	}
	return (0);
}

static void	cd_error(char *av)
{
	char	*error;

	error = ft_strjoin(av, ": ");
	if (!error)
		return ;
	ft_error("cd: ", error, strerror(errno), 1);
	free(error);
}

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
	int		i;

	i = 1;
	while (ac > 1 && av[i][0] == '-' && ac--)
		i++;
	if (ac == 1 || ac == 2)
	{
		replace_pwd("OLDPWD", lst);
//		is_symlink(av[i]);
		if (ac == 1 && chdir(get_key_value(lst, "HOME")))
			return (ft_error("cd: HOME not set", NULL, NULL, 1));
		else
			replace_pwd("PWD", lst);
		if (ac == 2)
		{
			if (!chdir(av[i]))
				replace_pwd("PWD", lst);
			else
				cd_error(av[i]);
		}
	}
	else
		return (ft_error("cd : too many arguments\n", NULL, NULL, 1));
	return (0);
}
