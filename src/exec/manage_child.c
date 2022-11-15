/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:45:35 by momadani          #+#    #+#             */
/*   Updated: 2022/11/15 18:45:47 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	launch_child(t_ast *root, t_ast *ast, t_mini *data)
{
	t_child	*child;

	(void)root;
	(void)ast;
	(void)data;
	child = ft_child_new();	
	if (!child)
		return (-1);
	return (0);
}
