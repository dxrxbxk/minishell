/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:16:29 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/16 15:43:30 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#define LONG_MAX 0x7fffffffffffffff
#define LONG_MIN 0x8000000000000000

static int	ft_isnum(char *str)
{
	int	i;

	i = 0;
	if (!*str)
	{
		ft_error("exit: ", str, " numeric argument required\n", 1);
		return (1);
	}
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] == '\0')
		return (0);
	else
		ft_error("exit: ", str, " numeric argument required\n", 1);
	return (1);
}

static long	result_check(long result, int sign, int over, char *nptr)
{
	if ((result > LONG_MAX && sign == 1) || over == 1)
	{
		ft_error("exit: ", nptr, " numeric argument required\n", 1);
		return (2);
	}
	if ((long unsigned)result > LONG_MIN && sign == -1)
	{
		ft_error("exit: ", nptr, " numeric argument required\n", 1);
		return (2);
	}
	return (result * sign);
}

static long	ft_atoi2(const char *nptr)
{
	long	result;
	int		sign;
	size_t	i;
	int		over;
	long	tmp;

	i = 0;
	over = 0;
	result = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	sign = 1 + ((nptr[i] == '-' && ++i) * -2);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		tmp = result;
		result = result * 10 + (nptr[i++] - '0');
		if ((unsigned long)result == LONG_MIN && sign == -1)
			return (result_check(result, sign, 0, (char *)nptr));
		if (tmp > result)
			over = 1;
	}
	return (result_check(result, sign, over, (char *)nptr));
}

int	ft_exit(t_env *lst, char **av, int ac)
{
	long	status;

	(void)lst;
	ft_putstr_fd("exit\n", 2);
	if (ac > 2)
		ft_error("exit:", NULL, " too many arguments\n", 1);
	else if (ac == 2 && ft_isnum(av[1]))
		status = 2;
	else if (ac == 2 && !ft_isnum(av[1]))
		status = ft_atoi2(av[1]);
	else
		status = 0;
	if (ac <= 2)
		exit((unsigned char)status);
	return (0);
}
