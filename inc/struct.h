/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:46:24 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/09 19:03:53 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef	enum	e_type
{
	WORD,
	WHITE_SPACE,
	NLINE,
	PIPE,
	D_PIPE,
	DOLLAR,
	QUOTE,
	D_QUOTE,
	GREAT,
	D_GREAT,
	LESS,
	D_LESS,
	AND,
	LEFT_P,
	RIGHT_P,
	WILDCARDS,
}				t_type;

typedef struct s_token_type
{
	char *value;
	t_type	type;
}			t_token_type;

typedef struct s_token
{
	char 	*str; //split whitespaces
	t_type	type; //pipe, quote etc.
	struct	s_token *next;
}			t_token;

typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
}				t_env;

typedef struct s_mini
{
	char *PATH;
	char **sPATH;
	t_env *env;
	t_env *env_cpy;
}				t_mini;

#endif
