/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_heredoc_files.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 22:41:05 by momadani          #+#    #+#             */
/*   Updated: 2022/11/21 09:43:32 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	is_heredoc(t_ast *ast)
{
	int	is_heredoc;

	is_heredoc = 0;
	while (ast && ast->token->type != D_LESS)
		ast = ast->left;
	return (ast != NULL);
}

static int	set_cmd_heredoc(t_ast *ast)
{
	char	*file_path;

	file_path = NULL;
	if (!ast || !is_heredoc(ast->left))
		return (0);
	file_path = heredoc_path();
	while (ast)
	{
		if (ast->token->type == D_LESS && ast->left)
		{
			if (apply_heredoc(file_path, ast->left->token->str) == 1)
				return (free(file_path), -1);
			free(ast->left->token->str);
			ast->left->token->str = ft_strdup(file_path);
		}
		ast = ast->left;
	}
	free(file_path);
	return (0);
}

static int	set_pipe_seq_heredoc(t_ast *ast)
{
	while (ast)
	{
		if (set_cmd_heredoc(ast->right) == -1)
			return (-1);
		ast = ast->left;
		if (ast)
			ast = ast->left;
	}
	return (0);
}

int	set_heredoc_files(t_ast *ast)
{
	if (!ast)
		return (0);
	if (ast->token->type == OP_SEQ)
	{
		if (set_heredoc_files(ast->right) == -1)
			return (-1);
		if (set_heredoc_files(ast->left) == -1)
			return (-1);
	}
	else if (ast->token->type == CMD)
		return (set_cmd_heredoc(ast));
	else if (ast->token->type == PIPE_SEQ)
		return (set_pipe_seq_heredoc(ast->left));
	else if (ast->token->type == AND || ast->token->type == D_PIPE)
		return (set_heredoc_files(ast->left));
	return(0);
}

void	ft_exec_heredoc_child(t_ast *ast)
{
	int	ret;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	ret = set_heredoc_files(ast);
	ft_free_ast_child(&ast);
	if (ret == -1)
		exit(1);
	exit(0);
}

int	set_heredoc(t_ast *ast)
{
	pid_t	pid;
	int		child_status;
	int		exit_status;

	exit_status = 0;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		return (ft_error("fork: ", strerror(errno), NULL, -1));
	if (pid == 0)
		ft_exec_heredoc_child(ast);
	waitpid(pid, &child_status, 0);
	if (ft_is_sigint(child_status))
	{
		ft_putstr_fd("\n", STDERR_FILENO);
		exit_status = 130;
		g_status = exit_status;
	}
	signal(SIGINT, inthandler);
	signal(SIGQUIT, SIG_IGN);
	if (exit_status == 130)
		return (ft_free_ast(ast), -1);
	return (0);
}
