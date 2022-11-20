/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 18:48:08 by momadani          #+#    #+#             */
/*   Updated: 2022/11/20 18:48:12 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_print_redirections(t_redir *redir)
{
	char	*msg;
	while (redir->type != END)
	{
		if (redir->type == INFILE)
			msg = "<";
		if (redir->type == HEREDOC)
			msg = "<<";
		if (redir->type == OUTFILE)
			msg = ">";
		if (redir->type == APPEND)
			msg = ">>";
		printf("\ntype : %s path : %s\n", msg, redir->path);
		redir++;
	}
	return (0);
}
