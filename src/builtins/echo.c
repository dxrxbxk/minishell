/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:03:29 by diroyer           #+#    #+#             */
/*   Updated: 2022/10/18 19:27:24 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <string.h>

static	void ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

int		ft_echo_print(char **av, int ac, int i, int n)
{
	while (i < ac)
	{
		ft_putstr(av[i]);
		if (i++ + 1 < ac)
			ft_putstr(" ");
	}
	if (n)
		ft_putstr("\n");
	return (0);
}

int		ft_echo(char **av, int ac)
{
	int	i;

	i = 1;
	if (ac > 1 && av[1][0] == '-' && av[1][1] == 'n')
	{
		while (i < ac && strlen(av[i]) > 1 && av[i][0] == '-' && av[i][1] == 'n')
			i++;
		return (ft_echo_print(av, ac, i, 0));
	}
	else if (ac > 1)
		return (ft_echo_print(av, ac, i, 1));
}

int		main(int ac, char **av)
{
	ft_echo(av, ac);
}
