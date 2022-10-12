/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 14:53:22 by diroyer           #+#    #+#             */
/*   Updated: 2022/10/12 15:00:37 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
static token_type		token_type[] = {
	{" ", WHITE_SPACE},
	{"\t", WHITE_SPACE},
	{"|", PIPE},
	{"||", D_PIPE},
	{"\\", BACKSLASH},
	{"$", DOLLAR},
	{"'", QUOTE},
	{"\"", D_QUOTE},
	{">", GREAT},
	{">>", D_GREAT},
	{"<", LESS},
	{"<<", D_LESS},
	{"&&", AND},
	{NULL, -1},
};
*/
int	free_data(t_mini *data)
{
	t_env **env;
	t_env	*tmp;

	env = &data->env;
	int	i = -1;
	while (++i) 
		free(data->sPATH[i]);
	while (*env)
	{
		tmp = (*env)->next;
		free((*env)->key);
		free((*env)->value);
		free(*env);
		*env = tmp;
	}
	return (0);
}
/*
int	parse_token(char *str)
{
	t_token
}
*/
int	get_token_size();
int	get_token_type(char *str);

int	get_line(t_mini *data)
{
	char *str;
	t_token_type token;	
	(void)token;
	(void)data;

	while (1)
	{
		handle_signals();
		str = readline("minishell :");
		if (str == NULL) // EOF / CTRL + D
			exit(free_data(data));
		if (str[0] == '\n') //idk
			printf("salut\n");
		add_history(str); 
//		parse(str);
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
	if (!data->sPATH)
		return (-1);
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
	get_env(&data, env);
	get_path(&data, env);
	if (ac == 1)
	{
		set_terminal(1);
		if (get_line(&data) == -1)
			set_terminal(0);
	}
}
