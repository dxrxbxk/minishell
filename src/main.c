/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 14:53:22 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/13 21:50:52 by momadani         ###   ########.fr       */
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
	if (msg && *msg)
	    printf("%.5s", msg);
	else if (msg && !*msg)
	    printf("\"\\0\"");
	else
		printf("%s", msg);
    printf("\n");
    print_tree(root->left, space);
} 

int	get_line(t_mini *data)
{
	char *input;
	t_token *tok;
	t_ast	*root;

	tok = NULL;
	root = NULL;
	while (1)
	{
		handle_signals();
		input = readline("minishell :");
		if (input == NULL) // EOF / CTRL + D
			exit(free_data(data));
		root = NULL;
		tok = NULL;
		if (parsing(input, &tok, &root, data->env) != 0)
			continue ;
		root = NULL;
		tok = NULL;
//		init_exec(ft_split(str, ' '), data);
		add_history(input); 
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
