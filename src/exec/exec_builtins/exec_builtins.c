/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <momadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 15:49:17 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/20 18:51:41 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exec_builtin(t_child *child, t_ast *ast, t_mini *shell)
{
	t_built	*data;
	int		ret;
	int		i;

	if (ft_get_args(child, ast->right) != 0)
		return (ft_quit_free_builtin(child));
	i = -1;
	ret = 1;
	data = init_fpointer();
	while (++i < NB_BUILTS)
	{
		if (!ft_strcmp(data[i].cmd, child->argv[0]))
			ret = data[i].builtins(shell->env,
					child->argv, tab_len(child->argv));
	}
	return (ret);
}
