/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 21:10:15 by diroyer           #+#    #+#             */
/*   Updated: 2022/10/13 22:02:21 by diroyer          ###   ########.fr       */
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

void	ft_add_token(t_token **alst, t_token *new)
{
	t_token *curr;

	curr = *alst;
	if (*alst == NULL)
		*alst = new;
	else
	{
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
}

t_token	*ft_new_token(void *content, t_type type)
{
	t_token *new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->str = ft_strdup(content);
	if (new->str)
		return (NULL);
	new->type = type;
	new->next = NULL;
	return (new);
}
