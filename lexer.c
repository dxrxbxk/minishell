/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:36:50 by diroyer           #+#    #+#             */
/*   Updated: 2022/10/13 18:43:12 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
   static t_token_type		token[] = {
   {" ", WHITE_SPACE},
   {"\t", WHITE_SPACE},
   {"|", PIPE},
   {"||", D_PIPE},
   {"\\", BACKSLASH},
   {"$", DOLLAR},
   {"'", QUOTE},
   {"\"", D_QUOTE},
   {">", GREAT},
   {">>", D_GREAT},
   {"<", LESS},
   {"<<", D_LESS},
   {"&&", AND},
   {NULL, -1},
   };
 */
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

int	token_type(char *str);


// parse token = filling the token structure

int	get_token(char *str, t_token **tok, int *i)
{
	t_token	*new;
	char	*token_content;
	int		type;
	int size = 0;

	(void)**tok;
	(void)type;(void)token_content;(void)new;
	size = token_size(str, i);
	token_content = ft_strndup(str + *i, size);

	printf("token = %s size %d\n", token_content, size);
	//	type = get_token_type(str);
	//	new = ft_lstnew(token_content, size, type)
	//	ft_lstadd_back(tok, new);
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
