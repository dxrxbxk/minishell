/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar_expand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 21:42:52 by momadani          #+#    #+#             */
/*   Updated: 2022/11/02 02:19:05 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_extract_env_value(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (ft_strdup(""));
}

size_t	ft_getkey_size_usual_expand(char *token)
{
	size_t	size;

	size = 0;
	if (token[size] == '\'' || token[size] == '"')
		return (size);
	while (token[size] && (ft_isalnum(token[size]) || token[size] == '_'))
		size++;
	return (size);
}

void	ft_change_dollar_expand(void (**ft)(t_token *, t_env *), t_token *lst)
{
	static int	quotes;

	if (!quotes && lst->type == QUOTE)
	{
		quotes = 1;
		*ft = &ft_squotes_dollar_expand;
	}
	else if (!quotes && lst->type == D_QUOTE)
	{
		quotes = 2;
		*ft = &ft_dquotes_dollar_expand;
	}
	else if (quotes == 1 && lst->type == QUOTE)
	{
		quotes = 0;
		*ft = &ft_usual_dollar_expand;
	}
	else if (quotes == 2 && lst->type == D_QUOTE)
	{
		quotes = 0;
		*ft = &ft_usual_dollar_expand;
	}
}

int	ft_dollar_expand(t_token *lst, t_env *env)
{
	void	(*ft_current_dollar_expand)(t_token *, t_env *);

	ft_current_dollar_expand = &ft_usual_dollar_expand;
	while (lst)
	{
		if (lst->type == D_QUOTE || lst->type == QUOTE)
			ft_change_dollar_expand(&ft_current_dollar_expand, lst);
		else if (lst->type == DOLLAR)
			(*ft_current_dollar_expand)(lst, env);
		lst = lst->next;
	}
	return (0);
}
