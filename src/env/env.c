/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 20:07:13 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/20 21:58:55 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#define SHLVL_WARNING "warning: shell level (1000) too high, resetting to 1"

char	*ret_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	return (cwd);
}

char	**create_env(void)
{
	char	**env;
	char	*cwd;

	cwd = ret_pwd();
	if (!cwd)
		return (NULL);
	env = malloc(sizeof(char *) * 4);
	if (!env)
		return (NULL);
	env[0] = ft_strjoin("PWD=", cwd);
	env[1] = ft_strjoin("SHLVL=", "0");
	env[2] = NULL;
	free(cwd);
	return (env);
}

int	get_env(t_mini *data, char **env)
{
	t_env	**elm;
	int		i;

	elm = &data->env;
	i = 0;
	if (!env)
		return (-1);
	while (env[i])
	{
		*elm = malloc(sizeof(t_env));
		(*elm)->key = ft_strndup(env[i], ft_findi(env[i], '='));
		if (!(*elm)->key)
			return (-1);
		(*elm)->value = ft_strdup(ft_strchr(env[i], '=') + 1);
		if (!(*elm)->value)
			return (-1);
		elm = &((*elm)->next);
		(*elm) = NULL;
		i++;
	}
	return (0);
}

int	get_path(t_mini *data, char **env)
{
	int		i;
	char	*path;

	i = 0;
	data->sPATH = NULL;
	if (!env)
		return (-1);
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
		{
			path = ft_strdup(ft_strchr(env[i], '=') + 1);
			if (!path)
				return (-1);
			data->sPATH = ft_split(path, ':');
			if (!data->sPATH)
				return (-1);
			free(path);
		}
		i++;
	}
	return (0);
}

int	get_shlvl(t_mini *data)
{
	char	*value;
	char	*tmp;
	int		ret;

	value = ft_strdup(get_key_value(data->env, "SHLVL"));
	if (!value)
		return (-1);
	ret = ft_atoi(value) + 1;
	if (ret > 999)
	{
		ft_error(SHLVL_WARNING, NULL, NULL, 0);
		ret = 1;
	}
	tmp = value;
	value = ft_itoa(ret);
	if (!value)
		return (-1);
	free(tmp);
	ft_replace_env(data->env, "SHLVL", value);
	return (0);
}
