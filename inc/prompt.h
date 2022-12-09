/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 19:05:30 by diroyer           #+#    #+#             */
/*   Updated: 2022/12/09 02:17:09 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# ifdef BONUS
#  define THEME 1
# else
#  define THEME 0
# endif

# define SHELL "\033[1m\033[44;30m "
# define GREEN_ARROW "\033[1m\033[32m❱ \033[0m"
# define RED_ARROW "\033[1m\033[31m❱ \033[0m"
# define PWD_COLOR "\033[1m\033[30m "
# define RESET "\033[0m"

char	*get_input(int ret, t_env *lst);

#endif
