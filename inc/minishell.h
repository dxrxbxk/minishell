/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:17:28 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/13 22:57:59 by diroyer          ###   ########.fr       */
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

# define BRACKETS 0
# define SQUOTES 1
# define DQUOTES 2
//NOTES

//we could make pointer fonction for builtins
/*
typdedef struct s_builtins
{
	char *content;
	int		(*builtins)(struct s_cmd *)
}
*/
void	ft_error(char *msg, char *var, char *msg2);
void	print_tab(char **tab);
extern	int	g_status;

#include <struct.h>
#include <env.h>
#include <lexer.h>
#include <parsing.h>
#include <utils.h>
#include <builtins.h>
#include <signals.h>
#include <exec.h>
#include <status.h>

#endif
