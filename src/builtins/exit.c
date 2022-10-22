/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:16:29 by diroyer           #+#    #+#             */
/*   Updated: 2022/10/22 16:14:54 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#define LONG_MAX 0x7fffffffffffffff
#define LONG_MIN 0x8000000000000000

int	ft_isnum(char *str)
{
	if (!*str)
	{
		printf("exit: %s: numeric argument required\n", str);
		return (1);
	}
	if (*str == '+' || *str == '-')
		str++;
	while (ft_isdigit(*str))
		str++;
	if (*str == '\0')
		return (0);
	else
		printf("exit: %s: numeric argument required\n", str);
	return (1);
}
static long ft_atoi2(const char *nptr)
{
	unsigned long long	result;
	int					sign;
	size_t				i;

	i = 0;
	result = 0;
	sign = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
		result = result * 10 + (nptr[i++] - '0');
	if (result > LONG_MAX && sign == 1)
	{
		printf("exit: %s: numeric argument required\n", nptr);
		result = result - LONG_MAX + 1;
	}
	if (result > LONG_MIN && sign == -1)
	{
		printf("exit: %s: numeric argument required\n", nptr);
		result = result - LONG_MIN + 1;
	}
	return (result);
}

int	ft_exit(char *av)
{
	printf("exit\n");
	ft_isnum(av);
	long	status = ft_atoi2(av);
	if (status < 256)
		return (status);
	return (status % 256);
}
