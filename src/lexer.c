/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:36:50 by diroyer           #+#    #+#             */
/*   Updated: 2022/10/25 17:43:28 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//lexer takes a string and returns a filled token structure (token pos, type, and the content attached to it
static int	ft_token_size(char *str, int *i)
{
	int size;
	int	y;

	size = 0;
	if (ft_strchr("\t |\\$'\"><&()*", str[(*i)]))
	{
		if (!ft_strncmp("<<", str + *i, 2) || !ft_strncmp(">>",str + *i, 2))
			return (2);
		if (!ft_strncmp("&&", str + *i, 2) || !ft_strncmp("||", str + *i, 2))
			return (2);
		return (1);
	}
	y = *i - 1;
	while (!ft_strchr("\t |\\$'\"><()*", str[++y]))
	{
		if (str[y + 1] == '&' && str[y + 2] == '&')
			return (size + 1);
		size++;
	}
	return (size);
}

//pas a la norme menfou
static t_type	ft_token_type(char *str)
{
	if (!ft_strcmp(" ", str) || !ft_strcmp("\t", str))
		return (WHITE_SPACE);
	if (!ft_strcmp("|", str))
		return (PIPE);
	if (!ft_strcmp("\\", str))
		return (BACKSLASH);
	if (!ft_strcmp("*", str))
		return (WILDCARDS);
	if (!ft_strcmp("$", str))
		return (DOLLAR);
	if (!ft_strcmp("'", str))
		return (QUOTE);
	if (!ft_strcmp("\"", str))
	   return (D_QUOTE);
	if (!ft_strcmp(">", str))
		return (GREAT);
	if (!ft_strcmp("<", str))
		return (LESS);
	if (!ft_strcmp(">>", str))
		return (D_GREAT);
	if (!ft_strcmp("<<", str))
		return (D_LESS);
	if (!ft_strcmp("&&", str))
		return (AND);
	if (!ft_strcmp("||", str))
		return (D_PIPE);
	if (!ft_strcmp("(", str))
		return (LEFT_P);
	if (!ft_strcmp(")", str))
		return (RIGHT_P);
	return (WORD);
}

// parse token = filling the token structure
static t_token	*ft_extract_token(char *input, int *i)
{
	char	*content;
	int 	size;
	t_type	type;

	size = ft_token_size(input, i);
	content = ft_strndup(input + *i, size);
	type = ft_token_type(content);
	*i += size;
//	printf("token = %s size = %d ", content, size);
//	printf("type %d\n", type);
	return (ft_token_new(content, type));
}

int	lexer(t_token **token, char *input)
{
	t_token	*new;
	int		i;
 
	i = 0;
	while (input[i])
	{
		new = ft_extract_token(input, &i);
		if (!new)
			return (0);
		ft_tokenadd_back(token, new);
	}
//	print_list(*token);
	return (1);
}
