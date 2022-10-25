/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 20:32:08 by momadani          #+#    #+#             */
/*   Updated: 2022/10/25 17:46:53 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_move_wspace(t_token **lst, t_type type)
{
	while (*lst && (*lst)->type == type)
		*lst = (*lst)->next;
	return (*lst != NULL);
}
/*
int	ft_token_is_word

int	ft_token_is_redir

int	ft_token_is_pipe
*/
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

int	ft_state_5(t_token **lst, long separators[3])
{
	ft_move_wspace(lst, WHITE_SPACE);
	if (*lst && (*lst)->type == RIGHT_P)
		return (separators[BRACKETS]--, ft_state_5(&(*lst)->next, separators));
	if (*lst && ((*lst)->type == AND || (*lst)->type == D_PIPE))
		return (ft_state_4(&(*lst)->next, separators));
	return ((*lst == NULL) && !separators[BRACKETS] && !separators[SQUOTES] && !separators[DQUOTES]);
}

int	ft_state_4(t_token **lst, long separators[3])
{
	ft_move_wspace(lst, WHITE_SPACE);
	if (*lst && (*lst)->type == LEFT_P)
		return (separators[BRACKETS]++, ft_state_4(&(*lst)->next, separators));
	if (*lst && ((*lst)->type == QUOTE || (*lst)->type == D_QUOTE))
		return (ft_state_1(lst, separators));
	if (*lst && ((*lst)->type == WORD || (*lst)->type == DOLLAR))
		return (ft_state_1(&(*lst)->next, separators));
	if (*lst && ((*lst)->type == LESS || (*lst)->type == GREAT
		|| (*lst)->type == D_LESS || (*lst)->type == D_GREAT))
		return (ft_state_2(&(*lst)->next, separators));
	return (0);
}

int	ft_state_3(t_token **lst, long separators[3])
{
	ft_move_wspace(lst, WHITE_SPACE);
	if (*lst && ((*lst)->type == LESS || (*lst)->type == GREAT
		|| (*lst)->type == D_LESS || (*lst)->type == D_GREAT))
		return (ft_state_2(&(*lst)->next, separators));
	if (*lst && ((*lst)->type == QUOTE || (*lst)->type == D_QUOTE))
		return (ft_state_1(lst, separators));
	if (*lst && ((*lst)->type == WORD || (*lst)->type == DOLLAR))
		return (ft_state_1(&(*lst)->next, separators));
	return (0);
}

int	ft_state_2(t_token **lst, long separators[3])
{
	ft_move_wspace(lst, WHITE_SPACE);
	if (*lst && ((*lst)->type == QUOTE || (*lst)->type == D_QUOTE))
		return (ft_state_1(lst, separators));
	if (*lst && ((*lst)->type == WORD || (*lst)->type == DOLLAR))
		return (ft_state_1(&(*lst)->next, separators));
	return (0);
}

int	ft_state_1(t_token **lst, long separators[3])
{
	if (*lst && ((*lst)->type == QUOTE || (*lst)->type == D_QUOTE))
		ft_move_next(lst, (*lst)->type, &separators[(*lst)->type - 6]);
	ft_move_wspace(lst, WHITE_SPACE);
	if (*lst && ((*lst)->type == QUOTE || (*lst)->type == D_QUOTE))
		return (ft_state_1(lst, separators));
	if (*lst && ((*lst)->type == WORD || (*lst)->type == DOLLAR))
		return (ft_state_1(&(*lst)->next, separators));
	if (*lst && ((*lst)->type == LESS || (*lst)->type == GREAT
		|| (*lst)->type == D_LESS || (*lst)->type == D_GREAT))
		return (ft_state_2(&(*lst)->next, separators));
	if (*lst && ((*lst)->type == PIPE))
		return (ft_state_3(&(*lst)->next, separators));
	if (*lst && ((*lst)->type == AND || (*lst)->type == D_PIPE))
		return (ft_state_4(&(*lst)->next, separators));
	if (*lst && (*lst)->type == RIGHT_P)
		return (separators[BRACKETS]--, ft_state_5(&(*lst)->next, separators));
	return (!*lst && !separators[BRACKETS] && !separators[SQUOTES] && !separators[DQUOTES]);
}

int	ft_state_0(t_token **lst, long separators[3])
{
	ft_move_wspace(lst, WHITE_SPACE);
//	printf("separators %ld\n", separators[BRACKETS]);
	if (*lst && (*lst)->type == LEFT_P)
		return (separators[BRACKETS]++, ft_state_0(&(*lst)->next, separators));
	if (*lst && ((*lst)->type == QUOTE || (*lst)->type == D_QUOTE))
		return (ft_state_1(lst, separators));
	if (*lst && ((*lst)->type == WORD || (*lst)->type == DOLLAR))
		return (ft_state_1(&(*lst)->next, separators));
	if (*lst && ((*lst)->type == LESS || (*lst)->type == GREAT
		|| (*lst)->type == D_LESS || (*lst)->type == D_GREAT))
		return (ft_state_2(&(*lst)->next, separators));
	return ((*lst == NULL) && !separators[BRACKETS] && !separators[SQUOTES] && !separators[DQUOTES]);
}

int	parser(t_token *first)
{
	t_token	**lst;
	long	separators[3];

	lst = &first;
	separators[BRACKETS] = 0;
	separators[DQUOTES] = 0;
	separators[SQUOTES] = 0;
	return (ft_state_0(lst, separators));
}
