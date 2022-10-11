/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 14:53:22 by diroyer           #+#    #+#             */
/*   Updated: 2022/10/11 16:56:32 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
int	parse(char *str)
{
	t_token	*token;
	int	i;

	i = 0;
	token = malloc(sizeof(*token)); //protec
	while (str[i])
	{
		if (ft_strchr(token_type, str[i]))
		{
			token->str = ft_strndup(str, i);
			token->type = token_type
		}

	}
	return (0);
}
*/
int	get_line(t_mini *data)
{
	char *str;

	(void)data;
	while (1)
	{
		handle_signals();
		str = readline("minishell :");
		if (str == NULL) // EOF / CTRL + D
			exit(1);
		if (str[0] == 0)
		{
			//new prompt
			ft_putstr_fd("", 1);
		}
		add_history(str); 
//		parse(str);
	//	tab = ft_split(str, ' ');
	//	print_tab(tab);
//		printf("%s", str);
	}
	return (0);
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
		if (!(*elm)->key)
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
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
		{
			data->PATH = ft_strdup(env[i] + 5);
			if (!data->PATH)
				return (-1);
		}
		i++;
	}
	data->sPATH = ft_split(data->PATH, ':');
	print_tab(data->sPATH);
	free(data->PATH);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_mini data;
	(void)env;
	(void)data;
//	get_env(&data, env);
//	get_path(&data, env);
	if (ac == 1)
	{
		set_terminal(1);
		get_line(&data);
		set_terminal(0);
	}
}
