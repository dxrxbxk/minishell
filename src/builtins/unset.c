/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 01:21:49 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/20 18:29:24 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

static void	del_and_link(t_env *lst, char *rem)
{
	t_env *del;

	del = NULL;
	if (!ft_strcmp(lst->key, rem))
		ft_pad(lst);
	while (lst->next && ft_strcmp(lst->next->key, rem))
		lst = lst->next;
	if (lst->next && !ft_strcmp(lst->next->key, rem))
	{
		del = get_lst_pointer(lst, rem);
		lst->next = del->next;
		ft_env_delone(del);
	}
}

int	ft_unset(t_env *lst, char **av, int ac)
{
	int	i;

	i = 0;
	while (++i < ac)
	{
		if (get_env_key(lst, av[i]))
			del_and_link(lst, av[i]);
		if (!ft_strcmp("PATH", av[i]))
			free_tab(data->sPATH);
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
