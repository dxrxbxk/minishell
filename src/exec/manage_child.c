/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:45:35 by momadani          #+#    #+#             */
/*   Updated: 2022/11/17 23:10:28 by momadani         ###   ########.fr       */
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
		ft_exit_free(data, child, ft_error(MEM_ERROR, NULL, NULL, 1));
	i = 0;
	while (ast)
	{
		if (ast->token->str)
		{
			child->argv[i] = ft_strdup(ast->token->str);
			if (!child->argv)
				ft_exit_free(data, child, ft_error(MEM_ERROR, NULL, NULL, 1));
			i++;
		}
		ast = ast->right;
	}
	child->argv[i] = NULL;
	return (0);
}

int	ft_check_is_directory(t_mini *data, t_child *child, char *path)
{
	struct stat sb;

	if (lstat(path, &sb) == -1)
		ft_exit_free(data, child, ft_error("lstat", NULL, NULL, 1));
	if (sb.st_mode & S_IFDIR)
		ft_exit_free(data, child, ft_error(path, ": Is a directory", NULL, 126));
	return (0);
}

void	exec_child(t_child *child, t_ast *ast, t_mini *data)
{
	ft_get_redirections(child, ast->left, data);
	ft_apply_redirections(child->redir, child, data);
	ft_get_args(child, ast->right, data);
	if (!child->argv || !*child->argv)
		ft_exit_free(data, child, 0);
	ft_find_cmd_path(child, data);
	ft_check_is_directory(data, child, child->pathname);
	child->envp = ft_lst_to_tab(data->env);
	execve(child->pathname, child->argv, child->envp);
	ft_error("execve: ", strerror(errno), NULL, 1);
	//memory realease
	exit(1);
}
