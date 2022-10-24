/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:16:29 by diroyer           #+#    #+#             */
/*   Updated: 2022/10/24 18:36:31 by diroyer          ###   ########.fr       */
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

long	ft_atoi2(const char *nptr)
{
	long		result;
	int		sign;
	size_t	i;
	int over;

	i = 0;
	over = 0;
	result = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	sign = 1 + ((nptr[i] == '-' && ++i) * -2);
	printf("sign = %d\n", sign);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (result != (result * 10) / 10)
			over = 1;
		if (result > 0 && ((result * 10) + (nptr[i]) - '0') == 0)
			over = 1;
		result = result * 10 + (nptr[i++] - '0');
		printf("over = %d result = %ld\n", over, result);
		if (result - (sign < 0) < 0)
			over = 1;
		
	}
	if ((result > LONG_MAX && sign == 1) || over == 1)
	{
		exit_numeric((char*)nptr);
		return (2);
	}
	if ((long unsigned)result > LONG_MIN && sign == -1)
	{
		exit_numeric((char*)nptr);
		return (2);
	}
	return (result * sign);
}
/*
   static int	ft_atoi2(const char *nptr)
   {
   long	result;
   long					sign;
   size_t				i;
   int over; 

   over = 0;
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
   {
   printf("result * 10 / 10 = %li\n", (result * 10) / 10);
   if (result != (result * 10) / 10)
   over = 1;
   result = result * 10 + (nptr[i++] - '0');
   printf(" result %li\n", result);
   if (result - (sign < 0) < 0)
   over = 1;
   }
   printf("over = %d\n", over);
   if (result > LONG_MAX || over == 1)
   {
   exit_numeric((char*)nptr);
   return (2);
   }
   return (result * sign);
   }
 */
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
