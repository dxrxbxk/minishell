/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 14:53:22 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/20 04:13:02 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	g_status = 0;

void print_tree(t_ast *root, int space)
{
	char	*msg;

	msg = NULL;
    if (root == NULL)
        return;
    space += 10;
    print_tree(root->right, space);
    printf("\n");
    for (int i = 10; i < space; i++)
	{
        printf(" ");
	}
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
	if (msg && *msg && *msg != '\n')
	    printf("%.5s", msg);
	else if (msg && *msg == '\n')
	    printf("\\n");
	else if (msg && !*msg)
	    printf("\"\\0\"");
	else
		printf("%s", msg);
    printf("\n");
    print_tree(root->left, space);
} 
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 14:53:22 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/14 19:22:38 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


int	prompt(t_mini *data)
{
	char *input;
	t_token *tok;
	t_ast	*root;

	input = NULL;
	tok = NULL;
	root = NULL;
	rl_outstream = stderr;
	while (1)
	{
		handle_signals();
					// ATTENTION : WILDCARDS are tokenize but not interpreted
		free(input);
		input = get_input();
		if (input == NULL) // EOF / CTRL + D
			ft_exit(data->env, NULL, 0);
		root = NULL;
		tok = NULL;
		if (parsing(input, &tok, &root, data->env) != 0) // free brackets from t_token *
			continue ;
//		print_tree(root, 0);
	//	printf("\n\n");
		set_heredoc_files(root);
		execution(root, root, data);
		root = NULL;
		tok = NULL;
	//	init_exec(ft_split(input, ' '), data);
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
		if (prompt(&data) == -1)
			return (0);
	}
}
//		ft_unset(data->env, ft_split(str, ' '), ft_count_words2(str, ' '));
//		ft_export(data->env, ft_split(str, ' '), ft_count_words2(str, ' '));
//		printf("%s\n",get_env_str(data->env, "SHLVL"));
//		ft_cd(data->env,ft_split(str, ' '), ft_count_words2(str, ' '));
//		ft_echo(ft_split(str, ' '), ft_count_words2(str, ' '));
//		unset(data->env, "ABC");
