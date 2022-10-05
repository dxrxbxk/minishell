/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:33:18 by diroyer           #+#    #+#             */
/*   Updated: 2021/11/24 18:14:10 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*curr;

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
