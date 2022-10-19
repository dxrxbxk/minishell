/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:34:03 by diroyer           #+#    #+#             */
/*   Updated: 2022/10/19 18:54:40 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_cd(int ac, char **av)
{
	int	i;

	i = 1;
	while (ac > 1 && av[i][0] == '-' && ac--)
		i++;
	if (ac == 2)
	{
		if (chdir(av[i]) != 0)
		{
			write(2, "cd: ", 4);
			perror(av[i]);
		}
		//printf("%s", getcwd(av[i], strlen(av[i])));
	}
	else if (ac > 2)
		write(2, "cd: too many arguments\n", 23);
	return (0);
}
