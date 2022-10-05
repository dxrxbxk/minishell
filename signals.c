/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:03:49 by diroyer           #+#    #+#             */
/*   Updated: 2022/04/11 16:16:20 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrap(int sig)
{
	(void)sig;
	puts("sig interupted");
}

void	ignore_sig(int sig)
{
	signal(sig, ctrap);
}
