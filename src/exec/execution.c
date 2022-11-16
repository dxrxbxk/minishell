/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 22:41:05 by momadani          #+#    #+#             */
/*   Updated: 2022/11/17 00:21:00 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_tree(t_ast *root, int space);

int	launch_pipe_sequence(t_ast *root, t_ast *ast, t_mini *data)
{
	(void)root;
	(void)ast;
	(void)data;
	return (0);
}

int	launch_children(t_ast *root, t_ast *ast, t_mini *data)
{
	print_tree(ast, 0);
	if (ast->token->type == PIPE_SEQ)
		return (launch_pipe_sequence(root, ast, data));
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
