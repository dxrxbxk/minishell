/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:34:03 by diroyer           #+#    #+#             */
/*   Updated: 2022/10/21 15:07:53 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		ft_cd(t_env *lst, char *str)
{
//	int	i;
	char buf[100];

//	printf("%s\n", get_env_str(lst, "PWD");

//	printf("getcwd = %s\n", getcwd(buf, 100));
	ft_replace_env(lst, "OLDPWD", getcwd(buf, 100));
	printf("OLD %s\n", get_env_str(lst, "OLDPWD"));
	/*
	while (ac > 1 && av[i][0] == '-' && ac--)
		i++;

	if (ac == 2)
	{
	*/
		if (!chdir(str))//av[i]))
		{
			ft_replace_env(lst, "PWD", getcwd(buf, 100));
			printf("NEW %s\n", get_env_str(lst, "PWD"));

		}
		else
		{
			write(2, "cd: ", 4);
			perror(str);//av[i]);
		}
/*
	else if (ac > 2)
		write(2, "cd: too many arguments\n", 23);
		*/
	return (0);
}
