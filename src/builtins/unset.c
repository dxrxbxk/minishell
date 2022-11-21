/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 01:21:49 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/21 16:12:57 by diroyer          ###   ########.fr       */
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

static void	del_and_link(t_env *lst, char *rem, t_mini *data)
{
	t_env	*del;
	t_env	*tmp;

	del = NULL;
	if (!ft_strcmp(rem, "PATH") && data->sPATH)
		free_tab(&data->sPATH);
	del = get_lst_pointer(lst, rem);
	if (lst == del)
	{
		tmp = data->env;
		data->env = data->env->next;
		ft_env_delone(tmp);
		return ;
	}
	while (lst->next && ft_strcmp(lst->next->key, rem))
		lst = lst->next;
	if (lst->next && !ft_strcmp(lst->next->key, rem))
	{
		tmp = get_lst_pointer(lst, rem);
		lst->next = del->next;
		ft_env_delone(tmp);
	}
}

int	ft_unset(t_env *lst, char **av, int ac)
{
	int		i;
	t_mini	**data;

	i = 0;
	data = ft_memptr_data(NULL);
	while (++i < ac)
	{
		if (get_env_key(lst, av[i]) && *av[i] != '\0')
			del_and_link(lst, av[i], *data);
		lst = (*data)->env;
	}
	return (0);
}
