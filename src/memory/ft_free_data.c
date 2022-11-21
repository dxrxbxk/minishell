/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 04:29:51 by momadani          #+#    #+#             */
/*   Updated: 2022/11/21 04:48:47 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_free_data(t_mini *data)
{
	free_tab(&data->sPATH);
	free_env(data->env);
	data->env = NULL;
	return (0);
}
