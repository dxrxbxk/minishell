/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:45:35 by momadani          #+#    #+#             */
/*   Updated: 2022/11/16 23:56:39 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_print_redirections(t_redir *redir)
{
	char	*msg;
	while (redir->type != END)
	{
		if (redir->type == INFILE)
			msg = "<";
		if (redir->type == HEREDOC)
			msg = "<<";
		if (redir->type == OUTFILE)
			msg = ">";
		if (redir->type == APPEND)
			msg = ">>";
		printf("\ntype : %s path : %s\n", msg, redir->path);
		redir++;
	}
	return (0);
}

void	ft_exit_free(t_mini *data, t_child *child, int retval)
{
	//free mem
	(void)data;
	(void)child;
	exit(retval);
}

int	ft_get_args(t_child *child, t_ast *ast, t_mini *data)
{
	size_t	i;

	if (!ast)
		return (0);
	child->argv = malloc(sizeof(char *) * (ft_rbranch_len_skip_null(ast) + 1));
	if (!child->argv)
		ft_exit_free(data, child, ft_error("Memory allocation error\n", NULL, NULL, 1));
	i = 0;
	while (ast)
	{
		if (ast->token->str)
		{
			child->argv[i] = ft_strdup(ast->token->str);
			if (!child->argv)
			ft_exit_free(data, child,
				ft_error("Memory allocation error\n", NULL, NULL, 1));
			i++;
		}
		ast = ast->right;
	}
	child->argv[i] = NULL;
	return (0);
}

void	exec_child(t_child *child, t_ast *ast, t_mini *data)
{
	ft_get_redirections(child, ast->left, data);
	ft_apply_redirections(child->redir, child, data);
	ft_get_args(child, ast->right, data);
	if (!child->argv)
		ft_exit_free(data, child, 0);
	
}

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
//	if (is_builtin)
//		return (exec_builtin())
	child->pid = fork();
	if (child->pid == -1)
		return (ft_error("fork: ", strerror(errno), "\n", -1));
	if (child->pid == 0)
		exec_child(child, ast, data);
	waitpid(-1, &child->status, 0);
//	wait_child(child);
	//(interpret exit status from child->status)
//	ft_free_children(child);
	return (0);
}
