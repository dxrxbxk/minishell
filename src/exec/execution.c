/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 22:41:05 by momadani          #+#    #+#             */
/*   Updated: 2022/11/18 15:13:20 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_tree(t_ast *root, int space);

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
/*
int	ft_get_redirections(t_child *child, t_ast *ast, t_mini *data)
{
	t_redir_type	type;
	char			*path;
	int				fd;
	size_t			i;

	if (!ast)
		return (0);
	child->redir = malloc(sizeof(t_redir) * ((ft_lbranch_len(ast) / 2) + 1));
	if (!child->redir)
		ft_exit_free(data, child, ft_error(MEM_ERROR, NULL, NULL, 1));
	i = 0;
	while (ast && ast->left)
	{
		type = ft_which_redir(ast->token->type);
		path = ft_strdup(ast->left->token->str);
		if (!path && ast->left->token->str != NULL)
			ft_exit_free(data, child, ft_error(MEM_ERROR, NULL, NULL, 1));
		fd = -1;
		ft_fill_redir_struct(&child->redir[i], type, path, fd);
		ast = ast->left->left;
		i++;
	}
	ft_fill_redir_struct(&child->redir[i], END, NULL, -1);
	return (0);
}*/

int	ft_get_redirections_pipe_seq(t_child *child, t_ast *ast)
{
	t_redir_type	type;
	char			*path;
	int				fd;
	size_t			len;
	size_t			i;

	len = 1;
	len += ft_lbranch_len(ast);
	if (child->prev && child->next)
		len++;
	child->redir = malloc(sizeof(t_redir) * (len + 1));
	if (!child->redir)
		return (ft_error(MEM_ERROR, NULL, NULL, -1));
	i = 0;
	if (child->prev)
		ft_fill_redir_struct(&child->redir[i++], PIPE_IN, NULL, -1);
	if (child->next)
		ft_fill_redir_struct(&child->redir[i++], PIPE_OUT, NULL, -1);
	while (ast && ast->left)
	{
		type = ft_which_redir(ast->token->type);
		path = ft_strdup(ast->left->token->str);
		if (!path && ast->left->token->str != NULL)
			return (ft_error(MEM_ERROR, NULL, NULL, -1));
		fd = -1;
		ft_fill_redir_struct(&child->redir[i], type, path, fd);
		ast = ast->left->left;
		i++;
	}
	ft_fill_redir_struct(&child->redir[i], END, NULL, -1);
	return (0);
}

int	ft_init_pipe_child_redirections(t_child *child, t_ast *ast)
{
	while (child)
	{
		if (ft_get_redirections_pipe_seq(child, ast->right->left) == -1) // protect ast->right->left
			return (-1);
		ast = ast->left;
		if (ast)
			ast = ast->left;
		child = child->next;
	}
	return (0);
}

int	ft_get_pipein_redir_rank(t_redir *redir)
{
	int	rank;

	rank = 0;
	while (redir[rank].type != PIPE_IN && redir[rank].type != END)
		rank++;
	if (redir[rank].type == PIPE_IN)
		return (rank);
	return (0);
}

int	ft_get_pipeout_redir_rank(t_redir *redir)
{
	int	rank;

	rank = 0;
	while (redir[rank].type != PIPE_OUT && redir[rank].type != END)
		rank++;
	if (redir[rank].type == PIPE_OUT)
		return (rank);
	return (0);
}

int	ft_create_pipe(t_child *child)
{
	int	pipefd[2];
	int	pipeout_rank;
	int	pipein_rank;

	if (!child->next)
		return (0);
	if (pipe(pipefd) == -1)
		return (ft_error("pipe: ", strerror(errno), NULL, -1));
	pipeout_rank = ft_get_pipeout_redir_rank(child->redir);
	pipein_rank = ft_get_pipein_redir_rank(child->next->redir);
	if (child->redir[pipeout_rank].type == PIPE_OUT)
		child->redir[pipeout_rank].fd = pipefd[1];
	if (child->next->redir[pipein_rank].type == PIPE_IN)
		child->next->redir[pipein_rank].fd = pipefd[0];
	return (1);
}

int	ft_close_pipe(t_child *child)
{
	int	pipeout_rank;
	int	pipein_rank;
	int	pipeout_fd;
	int	pipein_fd;

	if (!child->prev)
		return (0);
	pipeout_rank = ft_get_pipeout_redir_rank(child->prev->redir);
	pipein_rank = ft_get_pipein_redir_rank(child->redir);
	pipein_fd = -1;
	pipeout_fd = -1;
	if (child->prev->redir[pipeout_rank].type == PIPE_OUT)
		pipeout_fd = child->prev->redir[pipeout_rank].fd;
	if (child->redir[pipein_rank].type == PIPE_IN)
		pipein_fd = child->redir[pipein_rank].fd;
	if (close(pipeout_fd) == -1)	//add ft close that ignore if fd == -1
		return (ft_error("close: ", strerror(errno), NULL, -1));
	if (close(pipein_fd) == -1)		//add ft close that ignore if fd == -1
		return (ft_error("close: ", strerror(errno), NULL, -1));
	return (1);
}

int	launch_pipe_sequence(t_ast *ast, t_mini *data)
{
	t_child *first;
	t_child *child;

	child = NULL;
	if (ft_init_children(&child, ast) == -1)
		return (-1);
	if (ft_init_pipe_child_redirections(child, ast) == -1)
		return (-1);
	first = child;
	while (child)
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
	(void)ast;
	(void)data;
	(void)child;
	while (waitpid(-1, &first->status, 0) != -1)
		;
	//wait children
	//free children
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
		return (ft_error("fork: ", strerror(errno), NULL, -1));
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
