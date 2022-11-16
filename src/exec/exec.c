/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:18:39 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/16 20:03:32 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*check_rel_path(char *cmd)
{
	if (!access(cmd, F_OK | X_OK))
		return (ft_strdup(cmd));
	else
		perror(cmd);
	return (NULL);
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
	printf("cmd %s\n", cmd);
	if (ft_strchr(cmd, '.'))
		return (check_rel_path(cmd));
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
		perror(cmd);
	return (NULL);
}

int	exec_path(char *npath, char **av, char **env)
{
	pid_t pid;
	int status;

//	printf("npath %s\n", npath);
//	print_tab(av);
//	print_tab(env);
	pid = fork();
	if (pid < 0)
		printf("fork error occurred\n");
	else if (pid == 0)
	{
		execve(npath, av, env);
		perror("execve");
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

	env = lst_to_tab(shell->env);
	if (!*av || !av)
		return (1);
	if (!is_builtin(av))
		return (exec_builtin(av, shell));
	else
	{
		npath = check_path(shell->sPATH, av[0]);
		if (npath)
			exec_path(npath, av, env);
	}
	return (0);
}
