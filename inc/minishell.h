/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:17:28 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/20 19:57:59 by momadani         ###   ########.fr       */
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
# include <fcntl.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/sysmacros.h>
# define BRACKETS 0
# define SQUOTES 1
# define DQUOTES 2
# define MEM_ERROR "Memory allocation failed"
# include <struct.h>
# include <env.h>
# include <lexer.h>
# include <parsing.h>
# include <utils.h>
# include <builtins.h>
# include <signals.h>
# include <exec.h>
# include <memory.h>

extern int	g_status;

void	print_tab(char **tab);
int		tab_len(char **av);

#endif
