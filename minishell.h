/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:17:28 by diroyer           #+#    #+#             */
/*   Updated: 2022/10/07 13:46:11 by diroyer          ###   ########.fr       */
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

typedef struct s_token
{
	char 	*str; //split whitespaces
	int		type; //pipe, quote etc.
	char	*args;// agrs.
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
}				t_mini;

#endif
