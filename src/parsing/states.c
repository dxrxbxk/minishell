/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 20:32:08 by momadani          #+#    #+#             */
/*   Updated: 2022/11/02 01:32:27 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parserror(char *msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("syntax error near unexpected token ", STDERR_FILENO);
	ft_putchar_fd('`', STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putchar_fd('\'', STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

int	ft_checkerror(int state, t_token *lst, long separators[3])
{
	if ((state == 0 || state == 1 || state == 5)
		&& !lst && !separators[0] && !separators[1] && !separators[2])
		return (0);
	if (state == 5 && separators[0] < 0)
		ft_parserror(")");
	else if (!lst)
		ft_parserror("newline");
	else
		ft_parserror(lst->str);
	return (1);
}

int	ft_state_5(t_token *lst, long separators[3])
{
	ft_move_wspace(&lst, WHITE_SPACE);
	if (lst && lst->type == RIGHT_P)
		return (separators[BRACKETS]--, ft_state_5(lst->next, separators));
	if (lst && (lst->type == AND || lst->type == D_PIPE))
		return (ft_state_4(lst->next, separators));
	return (!ft_checkerror(5, lst, separators));
}

int	ft_state_4(t_token *lst, long separators[3])
{
	ft_move_wspace(&lst, WHITE_SPACE);
	if (lst && lst->type == LEFT_P)
		return (separators[BRACKETS]++, ft_state_4(lst->next, separators));
	if (lst && (lst->type == QUOTE || lst->type == D_QUOTE))
		return (ft_state_1(lst, separators));
	if (lst && ft_token_is_word(lst->type))
		return (ft_state_1(lst->next, separators));
	if (lst && ft_token_is_redir(lst->type))
		return (ft_state_2(lst->next, separators));
	return (!ft_checkerror(4, lst, separators));
}

int	ft_state_3(t_token *lst, long separators[3])
{
	ft_move_wspace(&lst, WHITE_SPACE);
	if (lst && ft_token_is_redir(lst->type))
		return (ft_state_2(lst->next, separators));
	if (lst && (lst->type == QUOTE || lst->type == D_QUOTE))
		return (ft_state_1(lst, separators));
	if (lst && ft_token_is_word(lst->type))
		return (ft_state_1(lst->next, separators));
	return (!ft_checkerror(3, lst, separators));
}

int	ft_state_2(t_token *lst, long separators[3])
{
	ft_move_wspace(&lst, WHITE_SPACE);
	if (lst && (lst->type == QUOTE || lst->type == D_QUOTE))
		return (ft_state_1(lst, separators));
	if (lst && ft_token_is_word(lst->type))
		return (ft_state_1(lst->next, separators));
	return (!ft_checkerror(2, lst, separators));
}

int	ft_state_1(t_token *lst, long separators[3])
{
	if (lst && (lst->type == QUOTE || lst->type == D_QUOTE))
		ft_move_next(&lst, lst->type, &separators[lst->type - 5]); //potential problem
	ft_move_wspace(&lst, WHITE_SPACE);
	if (lst && (lst->type == QUOTE || lst->type == D_QUOTE))
		return (ft_state_1(lst, separators));
	if (lst && ft_token_is_word(lst->type))
		return (ft_state_1(lst->next, separators));
	if (lst && ft_token_is_redir(lst->type))
		return (ft_state_2(lst->next, separators));
	if (lst && (lst->type == PIPE))
		return (ft_state_3(lst->next, separators));
	if (lst && (lst->type == AND || lst->type == D_PIPE))
		return (ft_state_4(lst->next, separators));
	if (lst && lst->type == RIGHT_P)
		return (separators[BRACKETS]--, ft_state_5(lst->next, separators));
	return (!ft_checkerror(1, lst, separators));
}

int	ft_state_0(t_token *lst, long separators[3])
{
	ft_move_wspace(&lst, WHITE_SPACE);
	if (lst && lst->type == LEFT_P)
		return (separators[BRACKETS]++, ft_state_0(lst->next, separators));
	if (lst && (lst->type == QUOTE || lst->type == D_QUOTE))
		return (ft_state_1(lst, separators));
	if (lst && ft_token_is_word(lst->type))
		return (ft_state_1(lst->next, separators));
	if (lst && ft_token_is_redir(lst->type))
		return (ft_state_2(lst->next, separators));
	return (!ft_checkerror(0, lst, separators));
}
