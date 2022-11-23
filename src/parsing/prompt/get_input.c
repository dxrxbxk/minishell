/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:34:28 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/24 00:02:18 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <prompt.h>

char	*ret_pwd_color(void)
{
	char	*cwd;
	char	*tmp;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	tmp = cwd;
	cwd = ft_mega_join(PWD_COLOR, ft_strrchr(cwd, '/'), " \033[0m");
	free(tmp);
	return (cwd);
}

static char	*get_prompt(int ret)
{
	char	*prompt;
	char	*pwd;
	char	*arrow;

	if (ret == 0)
		arrow = GREEN_ARROW;
	else
		arrow = RED_ARROW;
	pwd = ret_pwd_color();
	prompt = ft_mega_join(SHELL, pwd, arrow);
	free(pwd);
	return (prompt);
}

char	*get_input(int ret)
{
	char	*input;
	char	*prompt;

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
		{
			prompt = get_prompt(ret);
			input = readline(prompt);
			free(prompt);
		}
		if (input)
			add_history(input);
	}
	return (input);
}
