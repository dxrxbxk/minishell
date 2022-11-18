/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 01:21:49 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/18 16:38:15 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_swap_values(t_env *a, t_env *b)
{
	ft_swap_str(&a->key, &b->key);
	ft_swap_str(&a->value, &b->value);
}

static void ft_pad(t_env *lst)
{
	t_env *tmp;

	tmp = lst->next;
	while (tmp)
	{
		ft_swap_values(lst, tmp);
		lst = lst->next;
		tmp = tmp->next;
	}
}

static void	del_and_link(t_env *lst, t_env *del)
{
	printf("%s\n", del->key);
	if (lst == del)
		ft_pad(lst);
	printf("%s\n", del->key);
	while (lst && lst != del)
		lst = lst->next;
	if (lst == del)
	{
		printf("%s %s\n", del->key, del->value);
		lst = del->next;
//		ft_env_delone(del);
	}
}

t_env	*get_lst_pointer(t_env *lst, char *cmp)
{
	while (lst)
	{
		if (!ft_strcmp(lst->key, cmp))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

int	ft_unset(t_env *lst, char **av, int ac)
{
	t_env	*tmp;
	int	i;

	i = 0;
	while (++i < ac)
	{
		tmp = get_lst_pointer(lst, av[i]);
		if (tmp)
			del_and_link(lst, tmp);
	}
	return (0);
}

/*

   t_env *tmp;
   t_env *curr;
   int	i;

   i = 0;
   curr = lst;
   while (++i < ac)
   {
   tmp = curr;
   if (tmp && !ft_strcmp(tmp->key, av[i]))
   {
   lst = tmp->next;
   ft_env_delone(tmp);
   }
   while (tmp && ft_strcmp(tmp->key, av[i]))
   {
   lst = tmp;
   tmp = tmp->next;
   }
   if (tmp == NULL)
   return (0);
   lst->next = tmp->next;
   ft_env_delone(tmp);
   {
 */
