/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:17:28 by diroyer           #+#    #+#             */
/*   Updated: 2022/10/20 18:15:23 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <signal.h>
# include <unistd.h>
# include "libft.h"
# include "get_next_line.h"

# define BRACKETS 0
# define SQUOTES 1
# define DQUOTES 2

void	handle_signals(void);
void	set_terminal(int status);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	print_tab(char **tab);

typedef	enum	e_type
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
	LEFT_P,
	RIGHT_P,
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
	char *content;
	t_env *env;
}				t_mini;

void	print_list(t_token *print);

int		lexer(t_token **token, char *input);
int		parser(t_token *token);
int		ft_state_0(t_token **token, long separators[3]);
int		ft_state_1(t_token **token, long separators[3]);
int		ft_state_2(t_token **token, long separators[3]);
int		ft_state_3(t_token **token, long separators[3]);
int		ft_state_4(t_token **token, long separators[3]);
int		ft_state_5(t_token **token, long separators[3]);

t_token	*ft_token_new(void *content, t_type type);
void	ft_tokenadd_back(t_token **alst, t_token *new);

int		ft_strcmp(const char *s1, const char *s2);

#endif
