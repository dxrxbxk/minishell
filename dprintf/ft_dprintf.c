/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:39:43 by diroyer           #+#    #+#             */
/*   Updated: 2022/10/26 20:01:23 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dprintf.h>

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

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

void	check_format(int fd, char cmp, t_list **list)
{
	if (cmp == 's')
		print_sring(fd);
}

int		ft_dprintf(int fd, const char *format, ...)
{
	size_t	i;
	size_t	start;
	va_list	arg;
	char	*first;
	t_list	*lst;

	i = -1;
	start = -1;
	va_start(arg, format);
	if (!format)
		return (-1);
	if (ft_findi(format, '%') > 0)
		first = ft_strndup(format, ft_findi(format));
	else
		write(fd, format, ft_strlen(format));
	while (format[++i] && ++start)
	{
		if (format[i] == '%' && )
			check_format(fd, format[i + 1], &lst);
			

	}
	va_end(arg);
	return (0);
}
