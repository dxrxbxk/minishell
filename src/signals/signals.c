/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:03:49 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/17 18:11:15 by momadani         ###   ########.fr       */
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
	//set exit status at 1
	//new line with rl
	//replace buffer rl
	// display new line
	// control c = mettre exit status = 130
}

void	handle_signals(void)
{
	signal(SIGINT, inthandler);
	signal(SIGQUIT, SIG_IGN);
}
