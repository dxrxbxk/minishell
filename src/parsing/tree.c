/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:42:28 by momadani          #+#    #+#             */
/*   Updated: 2022/11/13 02:03:41 by momadani         ###   ########.fr       */
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

int	ft_add_full_cmd(t_ast *ast, t_token **token)
{
	while (*token && (*token)->type != D_PIPE && (*token)->type != AND
			 && (*token)->type != RIGHT_P && (*token)->type != PIPE)
	{
		if (ft_token_is_redir((*token)->type))
		{
			if (ft_astadd_last_left(&ast, ft_astnew(*token)) == -1)
				return (-1);
			if (ft_astadd_last_left(&ast, ft_astnew((*token)->next)) == -1)
				return (-1);
			*token = (*token)->next->next;
		}
		else if ((*token)->type == WORD)
		{
			if (ft_astadd_last_right(&ast, ft_astnew(*token)) == -1)
				return (-1);
			*token = (*token)->next;
		}	
		else
			*token = (*token)->next;
	}
	return (0);
}

int	ft_is_pipe_seq(t_token *token)
{
	while (token && token->type != D_PIPE && token->type != AND
			 && token->type != RIGHT_P && token->type != PIPE)
		token = token->next;
	return (token && token->type == PIPE);
}

int	ft_add_pipe_sequence(t_ast *ast, t_token *token)
{
	ast->token->type = PIPE_SEQ;
	while (ft_is_pipe_seq(token))
	{
		if (ft_create_node_left(&ast, OP_SEQ) == -1)
			return (-1);
		ast = ast->left;
		if (ft_create_node_right(&ast, CMD) == -1)
			return (-1);
		if (ft_add_full_cmd(ast->right, &token) == -1)
			return (-1);
		if (ft_astadd_last_left(&ast, ft_astnew(token)) == -1)
			return (-1);
		token = token->next;
		ast = ast->left;
	}
	if (ft_create_node_left(&ast, OP_SEQ) == -1)
		return (-1);
	ast = ast->left;
	if (ft_create_node_right(&ast, CMD) == -1)
		return (-1);
	if (ft_add_full_cmd(ast->right, &token) == -1)
		return (-1);
	return (0);
}

int	ft_addcmd_node(t_ast *ast, t_token **token)
{
	int	ret_val;

	ret_val = 0;
	if (ft_is_pipe_seq(*token))
		ret_val = ft_add_pipe_sequence(ast, *token);
	else
		ret_val = ft_add_full_cmd(ast, token);
	while (*token && (*token)->type != D_PIPE && (*token)->type != AND
			 && (*token)->type != RIGHT_P)
		*token = (*token)->next;
	return (ret_val);
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
