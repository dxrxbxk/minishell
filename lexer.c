/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:36:50 by diroyer           #+#    #+#             */
/*   Updated: 2022/10/12 16:21:49 by diroyer          ###   ########.fr       */
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
//lexer takes a string and returns a filled token structure (token pos, type, and the content attached to it

int	get_token_size(char *str);
int	get_token_type(char *str);

t_token	*lexer(char *str)
{
	t_token	*tok;
	int		i;
	int		len_str;

	i = 0;
	len_str = ft_strlen(str);
	while (i < len_str)
	{
		get_token(str, tok, &i);
	}
	return (tok);
}
// parse token = filling the token structure

int	get_token(char *str, t_token **tok, int *i)
{
	t_token	*new;
	char	*token_content;
	int		size;
	int		type;

	size = get_token_size(str);
	token_content = ft_strndup(str, size);
	type = get_token_type(str);
//	new = ft_lstnew(token_content, size, type)
//	ft_lstadd_back(tok, new);
	*i += size;

}

*/
