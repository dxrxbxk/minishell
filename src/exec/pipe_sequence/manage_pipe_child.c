/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_pipe_child.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <momadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 03:11:11 by momadani          #+#    #+#             */
/*   Updated: 2022/11/20 05:05:33 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_init_children(t_child **first, t_ast *ast)
{
	t_child	*new;

	new = NULL;
	while (ast)
	{
		new = ft_child_new();
		if (!new)
			return (ft_error(MEM_ERROR, NULL, NULL, -1));
		ft_child_add_back(first, new);
		ast = ast->left;
		if (ast)
			ast = ast->left;
	}
	return (0);
}

int	launch_pipe_children(t_child *child, t_ast *ast, t_mini *data)
{
	while (child) //&& ast
	{
		if (ft_create_pipe(child) == -1)
			return (-1);
		child->pid = fork();
		if (child->pid == -1)
			return (ft_error("fork: ", strerror(errno), NULL, -1));
		if (child->pid == 0)
			exec_pipe_child(child, ast->right, data);
		if (ft_close_pipe(child) == -1)
			return (-1);
		ast = ast->left;
		if (ast)
			ast = ast->left;
		child = child->next;
	}
	return (0);
}

int	launch_pipe_sequence(t_ast *ast, t_mini *data)
{
	t_child	*child;

	child = NULL;
	if (ft_init_children(&child, ast) == -1)
		return (-1);
	if (ft_init_pipe_child_redirections(child, ast) == -1)
		return (-1);
	if (launch_pipe_children(child, ast, data) == -1)
		return (-1);
	ft_wait_children(child);
	ft_interpret_child_status(child);
	//free children
	if (g_status == 130)
		return (-1);
	return (0);
}