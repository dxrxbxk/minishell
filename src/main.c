/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 14:53:22 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/03 20:09:21 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	get_line(t_mini *data)
{
	char *str;
	t_token *tok;

	tok = NULL;
	(void)tok;
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
	//	ft_cd(data->env,ft_split(str, ' '), ft_count_words2(str, ' '));
//		ft_echo(ft_split(str, ' '), ft_count_words2(str, ' '));
//		ft_export(data->env, ft_split(str, ' '), ft_count_words2(str, ' '));
//		lexer(&tok, str);
//		ft_export(data->env, str);
//		printf("----------------------------------\n");
//		unset(data->env, "ABC");
//		print_list(tok);
//		printf("exit ret = %d\n", ft_exit(ft_split(str, ' '), ft_count_words2(str, ' ')));
		add_history(str); 
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	(void)av;
	(void)ac;
	t_mini data;
	(void)env;
	(void)data;
	get_env(&data, env);
	get_path(&data, env);
	if (ac == 1)
	{
		if (get_line(&data) == -1)
			return (0);
	}
}
