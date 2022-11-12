/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:46:34 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/12 16:17:48 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <sys/types.h>
# include <sys/wait.h>
# include <struct.h>

char	*check_path(char **path, char *cmd);
int		is_builtin(char **av, t_mini *shell);
int		init_exec(char **av, t_mini *shell);
t_built	*init_fpointer(void);

#endif
