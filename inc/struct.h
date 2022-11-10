/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:46:24 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/10 22:50:10 by momadani         ###   ########.fr       */
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
	OP_SEQ,
	PIPE_SEQ,
	CMD,
}				t_type;

typedef struct s_ast
{
	struct s_token	*token;
	struct s_ast	*left;
	struct s_ast	*right;
}			t_ast;

typedef struct s_token
{
	char 	*str;
	t_type	type;
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
	int	(*builtins[6])(t_env *, char **, int);

}				t_mini;

#endif
