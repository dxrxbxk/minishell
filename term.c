/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:28:44 by diroyer           #+#    #+#             */
/*   Updated: 2022/10/07 13:40:32 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_terminal(int status)
{
	struct termios	terminal;
	static struct termios	tmp;

	if (status)
	{
		tcgetattr(0, &tmp);
		tcgetattr(0, &terminal);
		terminal = tmp;
		terminal.c_lflag &= ~ECHOCTL;
		tcsetattr(0, TCSAFLUSH, &terminal);
		return ;
	}
	tcsetattr(0, TCSAFLUSH, &tmp);
}
