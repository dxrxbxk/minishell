/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 14:53:22 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/10 17:36:27 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	get_line(t_mini *data)
{
	char *str;
	char **env;
	t_token *tok;

	tok = NULL;
	env = NULL;
	while (1)
	{
		handle_signals();
		str = readline("minishell :");
		if (str == NULL) // EOF / CTRL + D
			exit(free_data(data));
		if (str[0] == '\n') //idk
			printf("salut\n");
		lexer(&tok, str);
		if (parser(tok))
			expand(&tok, data->env);
		print_list(tok);
		tok = NULL;
		//ft_unset(data->env, ft_split(str, ' '), ft_count_words2(str, ' '));
		//print_env(data->env, 0);
//		ft_export(data->env, ft_split(str, ' '), ft_count_words2(str, ' '));
//		print_env(data->env);
		(void)env;
		//printf("%s\n",get_env_str(data->env, "SHLVL"));
//		ft_cd(data->env,ft_split(str, ' '), ft_count_words2(str, ' '));
//		ft_echo(ft_split(str, ' '), ft_count_words2(str, ' '));
//		lexer(&tok, str);
//		ft_export(data->env, str);
//		printf("----------------------------------\n");
//		unset(data->env, "ABC");
//		print_list(tok);
		add_history(str); 
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	(void)av;
	(void)ac;
	t_mini data;
	if (!*env)
		env = create_env();
	get_env(&data, env);
	get_path(&data, env);
	get_shlvl(&data);
	data.env_cpy = lst_copy(data.env);
//	print_tab(env);
	if (ac == 1)
	{
		if (get_line(&data) == -1)
			return (0);
	}
}
