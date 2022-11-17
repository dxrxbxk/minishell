/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 23:49:51 by momadani          #+#    #+#             */
/*   Updated: 2022/11/17 21:50:44 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_open(char *path, t_redir_type type)
{
	int		fd;
	int		flags;
	mode_t	mode;
	
	mode = 0;
	if (type == INFILE || type == HEREDOC)
		flags = O_RDONLY;
	else if (type == OUTFILE)
	{
		flags = O_WRONLY | O_CREAT | O_TRUNC;
		mode = 0666;
	}
	else if (type == APPEND)
	{
		flags = O_WRONLY | O_CREAT | O_APPEND;
		mode = 0666;
	}
	fd = open(path, flags, mode);
	return (fd);
}

int	ft_dup2(int fd, t_redir_type type)
{
	int	retval;

	retval = 0;
	if (type == INFILE || type == HEREDOC || type == PIPE_IN)
		retval = dup2(fd, STDIN_FILENO);
	else if (type == OUTFILE || type == APPEND || type == PIPE_OUT)
		retval = dup2(fd, STDOUT_FILENO);
	return (retval);
}

int	ft_close(int fd)
{
	if (close(fd) == -1)
		return (-1);
	return (0);
}

int	ft_apply_redirections(t_redir *redir, t_child *child, t_mini *data)
{
	if (!redir)
		return (0);
	while (redir->type != END)
	{
		if (!redir->path && redir->type != PIPE_IN && redir->type != PIPE_OUT)
			ft_exit_free(data, child,
				ft_error("ambiguous redirect", NULL, NULL, 1));
		if (redir->type != PIPE_IN && redir->type != PIPE_OUT)
			redir->fd = ft_open(redir->path, redir->type);
		if (redir->fd == -1)
			ft_exit_free(data, child,
				ft_error(redir->path, ": ", strerror(errno), 1));
		if (ft_dup2(redir->fd, redir->type) == -1)
			ft_exit_free(data, child, 
				ft_error(redir->path, ": ", strerror(errno), 1));
		if (ft_close(redir->fd) == -1)
			ft_exit_free(data, child,
				ft_error(redir->path, ": ", strerror(errno), 1));
		redir++;
	}
	return (0);
}

int	ft_get_redirections(t_child *child, t_ast *ast, t_mini *data)
{
	size_t	i;

	if (!ast)
		return (0);
	child->redir = malloc(sizeof(t_redir) * (ft_lbranch_len(ast) / 2) + 1);
	if (!child->redir)
		ft_exit_free(data, child, ft_error(MEM_ERROR, NULL, NULL, 1));
	i = 0;
	while (ast && ast->left)
	{
		if (ast->token->type == LESS)
			child->redir[i].type = INFILE;
		else if (ast->token->type == D_LESS)
			child->redir[i].type = HEREDOC;
		else if (ast->token->type == GREAT)
			child->redir[i].type = OUTFILE;
		else if (ast->token->type == D_GREAT)
			child->redir[i].type = APPEND;
		if (ast->left->token->str)
			child->redir[i].path = ft_strdup(ast->left->token->str);
		if (!child->redir[i].path && ast->left->token->str)
			ft_exit_free(data, child, ft_error(MEM_ERROR, NULL, NULL, 1));
		child->redir[i].fd = -1;
		ast = ast->left->left;
		i++;
	}
	child->redir[i].type = END;
	child->redir[i].path = NULL;
	return (0);
}
