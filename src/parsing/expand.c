/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 21:42:52 by momadani          #+#    #+#             */
/*   Updated: 2022/11/02 04:27:29 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_token_delone(t_token *token)
{
	free(token->str);
	free(token);
}

void	ft_remove_token(t_token *a, t_token *b)
{
	a->next = b->next;
	ft_token_delone(b);
}

void	ft_merge_tokens(t_token *a, t_token *b)
{
	char	*content;

	content = ft_strjoin(a->str, b->str);
	free(a->str);
	a->str = content;
	ft_remove_token(a, b);
}

int	expand(t_token **first, t_env *env)
{
	ft_dollar_expand(*first, env);
	ft_quotes_expand(*first);
	ft_tokencat(first);
	return (0);
}
