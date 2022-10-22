/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:04:50 by diroyer           #+#    #+#             */
/*   Updated: 2022/10/22 13:03:40 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *nptr)
{
	int		result;
	int		sign;
	size_t	i;

	i = 0;
	result = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	sign = 1 + ((nptr[i] == '-' && ++i) * -2);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (result != (result * 10) / 10)
		{
			printf("too big\n");
			return ;
		}
		result = result * 10 + (nptr[i++] - '0');
		if (result - (sign < 0) < 0)
		{
			printf("too big\n");
			return ;
		}
	}
	return (result * sign);
}
