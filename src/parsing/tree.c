/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:42:28 by momadani          #+#    #+#             */
/*   Updated: 2022/11/10 23:13:38 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
/*
int	ft_create_tree(t_ast **root, t_token **token)
{
	if (*root && (*root)->token->type == ROOT)
		*root = (*root)->right;
	while (*token)
	{
		if ((*token)->type == LEFT_P)
		{
			ft_create_node_right(root, OP_SEQ);
			*token = (*token)->next;
			ft_create_tree(&(*root)->right, token);
		}
		else if (ft_token_is_word((*token)->type) || ft_token_is_redir((*token)->type))
		{
			ft_create_node_right(root, OP_SEQ);
			ft_
		}
	}
}

int	ft_tree_2(t_ast **ast, t_token **token)
{

}
*/

int	ft_addcmd_node(t_ast *ast, t_token **token)
{
	(void)ast;
	while (*token && (*token)->type != D_PIPE && (*token)->type != AND
			 && (*token)->type != RIGHT_P)
		*token = (*token)->next;
	return (0);
}

int	ft_create_tree(t_ast *ast, t_token **token)
{
	while (*token)
	{
		if (*token && (*token)->type == LEFT_P)
		{
			ft_create_node_right(&ast, OP_SEQ);
			*token = (*token)->next;
			ft_create_tree(ast->right, token);
		}
		if (*token && (ft_token_is_word((*token)->type) || ft_token_is_redir((*token)->type)))
		{
			ft_create_node_right(&ast, CMD);
			ft_addcmd_node(ast->right, token);
		}
		if (*token && (*token)->type == RIGHT_P)
		{
			*token = (*token)->next;
			break ;
		}
		if (*token && ((*token)->type == AND || (*token)->type == D_PIPE))
		{
			ft_astadd_last_left(&ast, ft_astnew(*token));
			ft_create_node_left(&ast, OP_SEQ);
			*token = (*token)->next;
			ast = ast->left->left;
		}
	}
	return (0);
}

int	ft_init_tree(t_ast **root, t_token *token)
{
	t_ast	*cpy;

	if (ft_create_node_right(root, OP_SEQ) == -1)
		return (-1);
	cpy = *root;
	return (ft_create_tree(cpy, &token));
}

// '('
// CMD or PIPE SEQ
// ')'
// '&&' or '||'
