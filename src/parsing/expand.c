/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 21:42:52 by momadani          #+#    #+#             */
/*   Updated: 2022/10/28 20:40:37 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_dollar_expansion(t_token **first, t_env *env, );

int	expand(t_token **first, t_env *env)
{
	void	(*ft_dollar_expands[3])(t_token, t_env);
	void	(*ft_current_dollar_expand)(t_token, t_env);
	int		inside_quotes;
	t_token	*lst;

	ft_dollar_expands[0] = &ft_usual_dollar_expand();
	ft_dollar_expands[1] = &ft_squotes_dollar_expand();
	ft_dollar_expands[2] = &ft_dquotes_dollar_expand();
	ft_current_dollar_expand = &ft_usual_dollar_expand();
	inside_quotes = 0;
	lst = *first;
	
	while (lst)
	{
		if (!inside_quotes && (lst->type == D_QUOTES || lst->type == S_QUOTES))
		{
			ft_current_dollar_expand = ft_dollar_expands[lst->type - 5]
			inside_quotes = lst->type - 5;
		}
		else if ((inside_quotes == 1 && lst->type == S_QUOTES)
				|| (inside_quotes == 2 && lst->type == D_QUOTES))
		{
			ft_current_dollar_expand = ft_dollar_expands[lst->type - 5]
			inside_quotes = 0;
		}
		if (lst->type == DOLLAR)
			(*ft_current_dollar_expand)(first, lst, env);
		lst = lst->next;
	}
}
