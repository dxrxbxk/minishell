/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:34:28 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/16 13:40:57 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char *get_input(void)
{
	char	*input;

	if (!isatty(0))
	{
		input = get_next_line(0);
		if (input && input[ft_strlen(input) - 1] == '\n')
			input[ft_strlen(input) - 1] = '\0';
	}
	else
	{
		if (!isatty(2))
			input = readline("");
		else
			input = readline("bash-1.0$ ");
		if (input)
			add_history(input);
	}
	return (input);
}
