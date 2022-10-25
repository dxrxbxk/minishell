/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:16:29 by diroyer           #+#    #+#             */
/*   Updated: 2022/10/25 16:09:25 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#define LONG_MAX 0x7fffffffffffffff
#define LONG_MIN 0x8000000000000000

void	exit_numeric(char *str)
{
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(" numeric argument required\n", 2);
}

int	ft_isnum(char *str)
{
	if (!*str)
	{
		exit_numeric(str);
		return (1);
	}
	if (*str == '+' || *str == '-')
		str++;
	while (ft_isdigit(*str))
		str++;
	if (*str == '\0')
		return (0);
	else
		exit_numeric(str);
	return (1);
}

long	result_check(long result, int sign, int over, char *nptr)
{
	if ((result > LONG_MAX && sign == 1) || over == 1)
	{
		exit_numeric(nptr);
		return (2);
	}
	if ((long unsigned)result > LONG_MIN && sign == -1)
	{
		exit_numeric(nptr);
		return (2);
	}
	return (result * sign);
}

long	ft_atoi2(const char *nptr)
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

int	ft_exit(char *av)
{
	long	status;

	ft_putstr_fd("exit\n", 2);
	if (!*av)
		return (0);
	if (ft_isnum(av))
		return (2);
	status = ft_atoi2(av);
	if (status < 0)
	{
		if (status < 255)
			status = status % 256;
		status = status + 256;
	}
	if (status > 255)
		status = status % 256;
	return (status);
}
