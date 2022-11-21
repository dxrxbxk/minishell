/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 19:58:14 by momadani          #+#    #+#             */
/*   Updated: 2022/11/21 06:26:45 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_H
# define MEMORY_H

# include <struct.h>

int	ft_free_children(t_child *child);







t_mini	**ft_memptr_data(t_mini **data);
t_child	**ft_memptr_child(t_child **child);

#endif
