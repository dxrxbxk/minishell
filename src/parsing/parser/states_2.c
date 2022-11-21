/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 05:05:02 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/21 06:32:09 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#define SYNTAX_ERROR "syntax error near unexpected token `" 
#define END_QUOTE "\'"

int	ft_checkerror(int state, t_token *lst, long separators[3])
{
	if ((state == 0 || state == 1 || state == 5)
		&& !lst && !separators[0] && !separators[1] && !separators[2])
		return (0);
	if (state == 5 && separators[0] < 0)
		ft_error(SYNTAX_ERROR, ")", END_QUOTE, 2);
	else if (!lst)
		ft_error(SYNTAX_ERROR, "newline", END_QUOTE, 2);
	else
		ft_error(SYNTAX_ERROR, lst->str, END_QUOTE, 2);
	return (-1);
}

int	ft_state_5(t_token *lst, long separators[3])
{
	ft_move_wspace(&lst, WHITE_SPACE);
	if (lst && lst->type == RIGHT_P)
		return (separators[BRACKETS]--, ft_state_5(lst->next, separators));
	if (lst && (lst->type == AND || lst->type == D_PIPE))
		return (ft_state_4(lst->next, separators));
	return (ft_checkerror(5, lst, separators));
}
