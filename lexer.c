/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:36:50 by diroyer           #+#    #+#             */
/*   Updated: 2022/10/13 22:08:19 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//lexer takes a string and returns a filled token structure (token pos, type, and the content attached to it
int	token_size(char *str, int *i)
{
	int size;
	int	y;

	size = 0;
	y = *i -1;
	if (ft_strchr("\t |\\$'\"><&()", str[(*i)]))
	{
		if (!ft_strncmp("<<", str + *i, 2) || !ft_strncmp(">>",str + *i, 2))
			return (2);
		else if (!ft_strncmp("&&", str + *i, 2) || !ft_strncmp("||", str + *i, 2))
			return (2);
		else
			return (1);
	}
	while (!ft_strchr("\t |\\$'\"><()", str[++y]))
	{
		if (str[y + 1] == '&' && str[y + 2] == '&')
			return (size + 1);
		size++;
	}
	return (size);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if (*s1 != *s2)
		return ((unsigned char)*s1 - (unsigned char)*s2);
	return (0);
}

//pas a la norme menfou
t_type	token_type(char *str)
{
	if (!ft_strcmp(" ", str) || !ft_strcmp("\t", str))
		return (WHITE_SPACE);
	else if (!ft_strcmp("|", str))
		return (PIPE);
	else if (!ft_strcmp("\\", str))
		return (BACKSLASH);
	else if (!ft_strcmp("$", str))
		return (DOLLAR);
	else if (!ft_strcmp("'", str))
		return (QUOTE);
	else if (!ft_strcmp("\"", str))
		return (D_QUOTE);
	else if (!ft_strcmp(">", str))
		return (GREAT);
	else if (!ft_strcmp("<", str))
		return (LESS);
	else if (!ft_strcmp(">>", str))
		return (D_GREAT);
	else if (!ft_strcmp("<<", str))
		return (D_LESS);
	else if (!ft_strcmp("&&", str))
		return (AND);
	else if (!ft_strcmp("||", str))
		return (D_PIPE);
	else if (!ft_strcmp("(", str))
		return (LEFT_P);
	else if (!ft_strcmp(")", str))
		return (RIGHT_P);
	else
		return (WORD);
}


// parse token = filling the token structure

int	get_token(char *str, t_token **tok, int *i)
{
	char	*token_content;
	t_type		type;
	int size = 0;

	size = token_size(str, i);
	token_content = ft_strndup(str + *i, size);

	type = token_type(token_content);
	printf("token = %s size = %d ", token_content, size);
	printf("type %d\n", type);
	*tok = ft_new_token(token_content, type);
	//printf("tok %s\n", (*tok)->str);
	free(token_content);
	*i += size;
	return (0);
}

t_token	*lexer(char *str)
{
	t_token	*tok;
	int		i;
	int		len_str;

	i = 0;
	len_str = ft_strlen(str);
	while (i < len_str)
	{
		get_token(str, &tok, &i);
	}
	return (tok);
}
