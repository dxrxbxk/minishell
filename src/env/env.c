/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 20:07:13 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/13 20:07:53 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*ret_pwd(void)
{
	char *cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	return (cwd);
}

char	**create_env(void)
{
	char **env;
	char *cwd;

	cwd = ret_pwd();
	env = malloc(sizeof(char *) * 3);
	if (!env)
		return (NULL);
	env[0] = ft_strjoin("PWD=", cwd);
	env[1] = ft_strjoin("SHLVL=", "0");
	env[2] = NULL;
	return (env);
}

int	get_env(t_mini *data, char **env)
{
	t_env	**elm;
	int		i;

	elm = &data->env;
	i = 0;
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
	int	i;

	i = 0;
	data->sPATH = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
		{
			data->PATH = ft_strdup(ft_strchr(env[i], '=') + 1);
			if (!data->PATH)
				return (-1);
			data->sPATH = ft_split(data->PATH, ':');
			if (!data->sPATH)
				return (-1);
			print_tab(data->sPATH);
			free(data->PATH);
		}
		i++;
	}
	return (0);
}

int	get_shlvl(t_mini *data)
{
	char *value;
	char *tmp;
	int	ret;

	value = ft_strdup(get_env_str(data->env, "SHLVL"));
	if (!value)
		return (-1);
	ret = ft_atoi(value) + 1;
	if (ret > 999)
	{
		ft_error("warning: shell level (1000) too high, resetting to 1\n", "", "");
		ret = 1;
	}
	tmp = value;
	value = ft_itoa(ret);
	free(tmp);
	ft_replace_env(data->env, "SHLVL", value);
	return (0);
}

int	ft_count_words2(char const *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}
