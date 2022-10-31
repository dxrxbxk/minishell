/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 20:32:08 by momadani          #+#    #+#             */
/*   Updated: 2022/10/31 04:57:31 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_token_is_word(t_type type)
{
	return (type == WORD || type == DOLLAR || type == WILDCARDS);
}

int	ft_token_is_redir(t_type type)
{
	return (type == LESS || type == GREAT || type == D_LESS || type == D_GREAT);
}

int	ft_move_wspace(t_token **lst, t_type type)
{
	while (*lst && (*lst)->type == type)
		*lst = (*lst)->next;
	return (*lst != NULL);
}

int	ft_move_next(t_token **lst, t_type type, long *separator)
{
	if ((*lst)->type == type)
		*lst = ((*separator)++, ((*lst)->next));
	while (*lst && (*lst)->type != type)
		*lst = (*lst)->next;
	if (*lst && (*lst)->type == type)
		*lst = ((*separator)--, (*lst)->next);
	return (*lst != NULL);
}

int	parser(t_token *first)
{
	t_token	*lst;
	long	separators[3];

	lst = first;
	separators[BRACKETS] = 0;
	separators[SQUOTES] = 0;
	separators[DQUOTES] = 0;
	return (ft_state_0(lst, separators));
}
