/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 14:53:22 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/13 01:54:22 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void print_tree(t_ast *root, int space)
{
    if (root == NULL)
        return;
    space += 10;
    print_tree(root->right, space);
    printf("\n");
    for (int i = 10; i < space; i++)
	{
        printf(" ");
	}
	char	*msg;
	if (root->token->type == OP_SEQ)
		msg = "OP";
	if (root->token->type == CMD)
		msg = "CMD";
	if (root->token->type == AND)
		msg = "&&";
	if (root->token->type == PIPE)
		msg = "|";
	if (root->token->type == PIPE_SEQ)
		msg = "P_SEQ";
	if (root->token->type == D_PIPE)
		msg = "||";
	if (root->token->type == GREAT)
		msg = ">";
	if (root->token->type == D_GREAT)
		msg = ">>";
	if (root->token->type == LESS)
		msg = "<";
	if (root->token->type == D_LESS)
		msg = "<<";
	if (root->token->type == WORD)
		msg = root->token->str;
	if (msg)
	    printf("%.5s", msg);
	else
		printf("%s", msg);
    printf("\n");
    print_tree(root->left, space);
} 
int	get_line(t_mini *data)
{
	char *str;
	char **env;
	t_token *tok;
	t_ast	*root;

	tok = NULL;
	env = NULL;
	root = NULL;
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
		{
			expand(&tok, data->env);
			ft_init_tree(&root, tok);
			print_tree(root, 0);
//			print_list(tok);
		}
		root = NULL;
		tok = NULL;
		env = lst_to_tab(data->env);
		(void)env;
//		init_exec(ft_split(str, ' '), data);
		add_history(str); 
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	(void)av;
	(void)ac;
	t_mini data;
	if (!*env || !env)
		env = create_env();
	get_env(&data, env);
	get_path(&data, env);
	get_shlvl(&data);
	if (ac == 1)
	{
		if (get_line(&data) == -1)
			return (0);
	}
}
//		ft_unset(data->env, ft_split(str, ' '), ft_count_words2(str, ' '));
//		ft_export(data->env, ft_split(str, ' '), ft_count_words2(str, ' '));
//		printf("%s\n",get_env_str(data->env, "SHLVL"));
//		ft_cd(data->env,ft_split(str, ' '), ft_count_words2(str, ' '));
//		ft_echo(ft_split(str, ' '), ft_count_words2(str, ' '));
//		unset(data->env, "ABC");
