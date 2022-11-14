/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 19:39:02 by momadani          #+#    #+#             */
/*   Updated: 2022/11/14 14:03:56 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	parsing(char *input, t_token **first, t_ast **root, t_env *env)
{
	if (lexer(first, input) == -1)
		return (-1);
	if (parser(*first) == -1)
		return (-1);
	if (expand(first, env) == -1)
		return (-1);
	if (!*first)
		return (1);
	if (ast_init(root, *first) == -1)
		return (-1);
	return (0);
}
