/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:18:39 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/11 23:23:01 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_built	*init_fpointer(void)
{
	static t_built	data[NB_BUILTS];
	
	data[0].builtins = &ft_echo;
	data[0].cmd = "echo";
	data[1].builtins = &ft_unset;
	data[1].cmd = "unset";
	data[2].builtins = &ft_env;
	data[2].cmd = "env";
	data[3].builtins = &ft_pwd;
	data[3].cmd = "pwd";
	data[4].builtins = &ft_cd;
	data[4].cmd = "cd";
	data[5].builtins = &ft_exit;
	data[5].cmd = "exit";
	data[6].builtins = &ft_export;
	data[6].cmd = "export";
	return (data);
}

char	*check_cmd(char *path, char *cmd)
{
	char *tmp;

	tmp = ft_mega_join(path, "/", cmd);
	if (!access(tmp, F_OK | X_OK))
		return (tmp);
	return (NULL);
}

char	*check_path(char **path, char *cmd)
{
	int i;
	char *npath;

	i = -1;
	if (!path || !*path)
		return (NULL);
	while (path[++i])
	{
		if (ft_strchr(path[i], '/'))
		{
			npath = check_cmd(path[i], cmd);
			if (npath)
				return (npath);
		}
	}
	if (path[i] == NULL)
		ft_error(cmd, ": command not found", "\n");
	return (NULL);
}

static int	tab_len(char **av)
{
	int i;

	i = 0;
	while (av[i])
		i++;
	return (i);
}

static int	is_builtin(char **av, t_mini *shell)
{
	int	i;
	t_built *data;

	i = -1;
	data = init_fpointer();
	while (++i < NB_BUILTS)
	{
		if (!ft_strcmp(data[i].cmd, av[0]))
			return (data[i].builtins(shell->env, av, tab_len(av)));
	}
	return (1);
}

int	exec_path(char *npath, char **av, char **env)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid < 0)
		printf("failed\n");
	else if (pid == 0)
	{
		execve(npath, av, env);
	}
	else
	{
		if (waitpid(pid, &status, 0) > 0)
		{
			if (WIFEXITED(status) && !WEXITSTATUS(status))
            	printf("program execution successful\n");
            else if (WIFEXITED(status) && WEXITSTATUS(status))
			{
                if (WEXITSTATUS(status) == 127)
                    printf("execv failed\n");
                else
                    printf("program terminated normally,"
                    " but returned a non-zero status\n");
            }
            else
				printf("program didn't terminate normally\n");
        }
        else 
        	printf("waitpid() failed\n");
	}
	return (0);
}

int init_exec(char **av, t_mini *shell)
{
	char *npath;
	char **env;

	(void)npath;
	(void)env;
	env = lst_to_tab(shell->env);
	if (!*av || !av)
		return (1);
	if (!is_builtin(av, shell))
		return (0);
	else
	{
		npath = check_path(shell->sPATH, av[0]);
		if (npath)
			exec_path(npath, av, env);
	}
	return (0);
}
