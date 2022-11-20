/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <momadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 05:08:32 by momadani          #+#    #+#             */
/*   Updated: 2022/11/20 05:24:15 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_get_cmd_redirections(t_child *child, t_ast *ast)
{
	// t_redir_type	type;
	// char			*path;
	// int				fd;
	// size_t			i;

	if (!ast)
		return (0);
	child->redir = malloc(sizeof(t_redir) * ((ft_lbranch_len(ast) / 2) + 1));
	if (!child->redir)
		return (set_child_status(child, ft_error(MEM_ERROR, NULL, NULL, 1)));
    if (ft_add_cmd_redirections(child->redir, ast) == -1)
        return (set_child_status(child, 1));
/*	i = 0;
	while (ast && ast->left)
	{
		type = ft_which_redir(ast->token->type);
		path = ft_strdup(ast->left->token->str);
		if (!path && ast->left->token->str != NULL)
			return (set_child_status(child, ft_error(MEM_ERROR, NULL, NULL, 1)));
		fd = -1;
		ft_fill_redir_struct(&child->redir[i], type, path, fd);
		ast = ast->left->left;
		i++;
	}
	ft_fill_redir_struct(&child->redir[i], END, NULL, -1);*/
	return (0);
}