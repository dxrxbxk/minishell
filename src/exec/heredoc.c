/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 18:14:47 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/18 21:32:04 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#define HERE_DOC_WARNING "warning: here-document at line "
#define HERE_DOC_EOF " delimited by end-of-file (wanted `EOF')"

static int	check_len(char *s1, char *s2)
{
	if (ft_strlen(s1) == ft_strlen(s2) - 1)
		return (0);
	return (1);
}

static int	get_and_write(int fd, char *delim)
{
	char *line;
	char *arg;
	static int i = 0;

	ft_putstr_fd("> ", 0);
	line = get_next_line(0);
	if (line && ft_strcmp(line, "\n"))
		i++;
	if (!line)
	{
		arg = ft_itoa(i);
		ft_error(HERE_DOC_WARNING, arg, HERE_DOC_EOF, 0);
		free(arg);
		return (i = 0);
	}
	else if (!ft_strncmp(delim, line, ft_strlen(delim)) 
			&& !check_len(delim, line))
	{
		free(line);
		return (i = 0);
	}
	else
		write(fd, line, ft_strlen(line));
	free(line);
	return (1);
}

int		apply_heredoc(char *path, char *delim)
{
	int	fd;

	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC);
	if (fd == -1)
		return (ft_error("open: ", strerror(errno), NULL, 1));
	while (get_and_write(fd, delim))
		;
	close(fd);
	return (0);
}
