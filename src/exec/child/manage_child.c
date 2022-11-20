/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <momadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 03:08:12 by momadani          #+#    #+#             */
/*   Updated: 2022/11/20 05:05:08 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	launch_child(t_ast *ast, t_mini *data)
{
	t_child	*child;

	child = ft_child_new();	
	if (!child)
		return (ft_error(MEM_ERROR, NULL, NULL, -1));
	if (is_builtin(ast->right))
		return (launch_builtin(child, ast, data));
	child->pid = fork();
	if (child->pid == -1)
		return (/*ft_free_children(child), */ft_error("fork: ",
											strerror(errno), NULL, -1));
	if (child->pid == 0)
		exec_child(child, ast, data);
	ft_wait_children(child);
	ft_interpret_child_status(child);
//	ft_free_children(child);
	if (g_status == 130)
		return (-1);
	return (0);
}