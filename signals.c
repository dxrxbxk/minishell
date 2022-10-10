/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:03:49 by diroyer           #+#    #+#             */
/*   Updated: 2022/10/10 16:17:20 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	inthandler(int sig)
{
	(void)sig;
	ft_putendl_fd("", 1);
	exit(1);
	//set exit status at 1
	//new line with rl
	//replace buffer rl
	// display new line
}

void	handle_signals(void)
{
	signal(SIGINT, inthandler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	signal(SIGHUP, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
}
