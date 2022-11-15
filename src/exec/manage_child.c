/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:45:35 by momadani          #+#    #+#             */
/*   Updated: 2022/11/15 22:46:25 by momadani         ###   ########.fr       */
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
	//if builtin do not fork
	// -> builtin function
	child->pid = fork();
	if (child->pid == -1)
		return (ft_error("fork: ", strerror(errno), "\n"));
	if (child->pid == 0)

	return (0);
}
