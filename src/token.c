/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 21:10:15 by diroyer           #+#    #+#             */
/*   Updated: 2022/10/14 21:12:29 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list(t_token *print)
{
	printf("saliti\n");
	while (print)
	{
		printf("tok->str = %s and tok->type = %d\n", print->str, print->type);
		print = print->next;
	}
}

void	ft_tokenadd_back(t_token **first, t_token *new)
{
	t_token *current;

	current = *first;
	if (!*first)
		*first = new;
	else
	{
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

t_token	*ft_token_new(void *content, t_type type)
{
	t_token *new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->str = content;
	new->type = type;
	new->next = NULL;
	return (new);
}
