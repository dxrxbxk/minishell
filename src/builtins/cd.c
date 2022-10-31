/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:34:03 by diroyer           #+#    #+#             */
/*   Updated: 2022/10/31 23:00:20 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		ft_cd(t_env *lst, char **av, int ac)
{
	int	i;
	char *cwd;

	i = 1;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (-1);
	ft_replace_env(lst, "OLDPWD", cwd);
	while (ac > 1 && av[i][0] == '-' && ac--)
		i++;
	free(cwd);
	if (ac == 2)
	{
		if (!chdir(av[i]))
		{
			cwd = getcwd(NULL, 0);
			ft_replace_env(lst, "PWD", cwd);
			free(cwd);
			printf("NEW %s\n", get_env_str(lst, "PWD"));

		}
		else
		{
			write(2, "cd: ", 4);
			perror(av[i]);
		}
	}
	else
		write(2, "cd: too many arguments\n", 23);
	return (0);
}
