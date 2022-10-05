/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:20:20 by diroyer           #+#    #+#             */
/*   Updated: 2021/12/03 20:01:09 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*tmp;
	t_list	*curr;

	curr = lst;
	while (curr)
	{
		tmp = ft_lstnew(f(curr->content));
		if (!tmp)
			ft_lstclear(&curr, del);
		else
		{
			ft_lstadd_back(&new, tmp);
			curr = curr->next;
		}
	}
	return (new);
}
