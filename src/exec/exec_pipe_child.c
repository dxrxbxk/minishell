/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 04:13:41 by momadani          #+#    #+#             */
/*   Updated: 2022/11/18 05:29:43 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_close_unused_pipe(t_child *child, t_mini *data)
{
	int		prev_pipeout_rank;
	int		next_pipein_rank;

	prev_pipeout_rank = -1;
	if (child->prev)
		prev_pipeout_rank = ft_get_pipeout_redir_rank(child->prev->redir);
	next_pipein_rank = -1;
	if (child->next)
		next_pipein_rank = ft_get_pipein_redir_rank(child->next->redir);
	if (child->prev && close(child->prev->redir[prev_pipeout_rank].fd) == -1) // make it more explicit can add ft_close that ignore if fd == -1
		ft_exit_free(data, child, ft_error("close: ", strerror(errno), NULL, 1));
	if (child->next && close(child->next->redir[next_pipein_rank].fd) == -1) // make it more explicit
		ft_exit_free(data, child, ft_error("close: ", strerror(errno), NULL, 1));
	return (0);
}

void	exec_pipe_child(t_child *child, t_ast *ast, t_mini *data)
{
	ft_close_unused_pipe(child, data);
	ft_apply_redirections(child->redir, child, data);
	ft_get_args(child, ast->right, data);
	if (!child->argv || !*child->argv)
		ft_exit_free(data, child, 0);
	ft_find_cmd_path(child, data);
	ft_check_is_directory(data, child, child->pathname);
	child->envp = ft_lst_to_tab(data->env);
	execve(child->pathname, child->argv, child->envp);
	ft_error("execve: ", strerror(errno), NULL, 1);
	//mem release
	exit(1);
}
