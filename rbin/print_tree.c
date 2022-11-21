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