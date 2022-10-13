/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:17:28 by diroyer           #+#    #+#             */
/*   Updated: 2022/10/13 16:33:07 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include "libft/libft.h"
# include "libft/get_next_line.h"
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <signal.h>
# include <unistd.h>

void	handle_signals(void);
void	set_terminal(int status);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	print_tab(char **tab);

typedef enum	e_type
{
	WORD,
	WHITE_SPACE,
	NLINE,
	PIPE,
	D_PIPE,
	BACKSLASH,
	DOLLAR,
	QUOTE,
	D_QUOTE,
	GREAT,
	D_GREAT,
	LESS,
	D_LESS,
	AND,
}				t_type;

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
	char *content;
	t_env *env;
}				t_mini;

#endif
