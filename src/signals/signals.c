/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:03:49 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/21 14:27:33 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	inthandler(int sig)
{
	(void)sig;
	ft_putendl_fd("", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_status = 130;
}

void	ft_modify_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	handle_signals(void)
{
	signal(SIGINT, inthandler);
	signal(SIGQUIT, SIG_IGN);
}
