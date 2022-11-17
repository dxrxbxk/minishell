/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 22:41:05 by momadani          #+#    #+#             */
/*   Updated: 2022/11/17 23:20:53 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_tree(t_ast *root, int space);

int	launch_pipe_sequence(t_ast *ast, t_mini *data)
{
	t_child *child;

	child = NULL;
	child = ft_child_new();	
	if (!child)
		return (-1);
	(void)ast;
	(void)data;
	return (0);
}


int	launch_child(t_ast *root, t_ast *ast, t_mini *data)
{
	t_child	*child;

	(void)root;
	child = NULL;
	child = ft_child_new();	
	if (!child)
		return (-1);
	//if builtin do not fork
	// -> builtin function
//	if (is_builtin)
//		return (exec_builtin())
	child->pid = fork();
	if (child->pid == -1)
		return (ft_error("fork: ", strerror(errno), "\n", -1));
	if (child->pid == 0)
		exec_child(child, ast, data);
	waitpid(-1, &child->status, 0);
	g_status = child->status;
//	printf("status %d\n", child->status);
//	wait_child(child);
	//(interpret exit status from child->status)
//	ft_free_children(child);
	return (0);
}

int	launch_children(t_ast *root, t_ast *ast, t_mini *data)
{
//	print_tree(ast, 0);
	if (ast->token->type == PIPE_SEQ)
		return (launch_pipe_sequence(ast->left, data));
	else if (ast->token->type == CMD)
		return (launch_child(root, ast, data));
	return (1);
}

int	execution(t_ast *root, t_ast *ast, t_mini *data)
{
	//add heredoc
	if (!ast)
		return (0);
	if (ast->token->type == OP_SEQ)
	{
		if (execution(root, ast->right, data) == -1)
			return (-1);
		if (execution(root, ast->left, data) == -1)
			return (-1);
	}
	else if (ast->token->type == CMD || ast->token->type == PIPE_SEQ)
		return (launch_children(root, ast, data));
	else if (ast->token->type == AND && g_status == 0)
		return (execution(root, ast->left, data));
	else if (ast->token->type == D_PIPE && g_status != 0)
		return (execution(root, ast->left, data));
	else
		return (execution(root, ast->left->left, data));
	return (0);
}
