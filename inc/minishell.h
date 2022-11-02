/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:17:28 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/02 20:46:49 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <signal.h>
# include <unistd.h>

# define BRACKETS 0
# define SQUOTES 1
# define DQUOTES 2
//NOTES

//we could make pointer fonction for builtins
/*
typdedef struct s_builtins
{
	char *content;
	int		(*builtins)(struct s_cmd *)
}
*/

typedef	enum	e_type
{
	WORD,
	WHITE_SPACE,
	NLINE,
	PIPE,
	D_PIPE,
	DOLLAR,
	QUOTE,
	D_QUOTE,
	GREAT,
	D_GREAT,
	LESS,
	D_LESS,
	AND,
	LEFT_P,
	RIGHT_P,
	WILDCARDS,
}				t_type;

typedef struct s_token_type
{
	char *value;
	t_type	type;
}			t_token_type;

typedef struct s_token
{
	char 	*str; //split whitespaces
	t_type	type; //pipe, quote etc.
	struct	s_token *next;
}			t_token;

typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
}				t_env;

typedef struct s_mini
{
	char *PATH;
	char **sPATH;
	char *content;
	int	ac;
	char **av;
	t_env *env;
}				t_mini;

// src/signals.c
void inthandler(int sig);
void handle_signals(void);

// src/utils/ft_strndup.c
char *ft_strndup(const char *s1, int len);

// src/utils/ft_putendl_fd.c
void ft_putendl_fd(char *s, int fd);

// src/utils/ft_swap_str.c
void ft_swap_str(char **a, char **b);

// src/utils/ft_isalpha.c
int ft_isalpha(int c);

// src/utils/ft_isalnum.c
int ft_isalnum(int c);

// src/utils/ft_strcmp.c
int ft_strcmp(const char *s1, const char *s2);

// src/utils/ft_isdigit.c
int ft_isdigit(int c);

// src/utils/ft_findi.c
int ft_findi(char *str, char find);

// src/utils/ft_strncmp.c
int ft_strncmp(const char *s1, const char *s2, size_t n);

// src/utils/ft_strlen.c
size_t ft_strlen(const char *s);

// src/utils/ft_putstr_fd.c
void ft_putstr_fd(char *s, int fd);

// src/utils/ft_strchr.c
char *ft_strchr(const char *s, int c);

// src/utils/ft_putchar_fd.c
void ft_putchar_fd(char c, int fd);

// src/utils/ft_split.c
char **ft_split(char const *s, char c);

// src/utils/ft_strdup.c
char *ft_strdup(const char *s1);

// src/utils/ft_strlcpy.c
size_t ft_strlcpy(char *dst, const char *src, size_t dstsize);

// src/utils/ft_strlcat.c
size_t ft_strlcat(char *dst, const char *src, size_t size);

// src/utils/ft_strjoin.c
char	*ft_strjoin(char const *s1, char const *s2);

// src/lexer.c
int lexer(t_token **token, char *input);

// src/main.c
int free_data(t_mini *data);
int get_line(t_mini *data);
int get_env(t_mini *data, char **env);
int get_path(t_mini *data, char **env);

// src/builtins/unset.c
void unset(t_env *lst, char *str);

// src/builtins/exit.c
void exit_numeric(char *str);
int ft_isnum(char *str);
long result_check(long result, int sign, int over, char *nptr);
long ft_atoi2(const char *nptr);
int	ft_exit(char **av, int ac);

// src/builtins/cd.c
int		ft_cd(t_env *lst, char **av, int ac);

// src/builtins/env.c
void ft_env(t_env *lst);

// src/builtins/echo.c
int ft_cmpchar(char *str, char c);
int ft_echo_print(char **av, int ac, int i, int n);
int ft_echo(char **av, int ac);

// src/builtins/export.c
int export_key(char *str);
t_env *lst_copy(t_env *lst);
void sort_list(t_env *tosort);
int ft_export(t_env *lst, char **av, int ac);

// src/builtins/pwd.c
int ft_pwd(void);

// src/parsing/expand.c
//int ft_dollar_expansion(t_token **first, t_env *env, );

/*-----------------------------expand----------------------------------------*/

int		expand(t_token **first, t_env *env);
int		ft_tokencat(t_token **lst);
int		ft_quotes_expand(t_token *lst);
void	ft_token_delone(t_token *token);
void	ft_remove_token(t_token *a, t_token *b);
void	ft_merge_tokens(t_token *a, t_token *b);

int		ft_dollar_expand(t_token *lst, t_env *env);
void	ft_usual_dollar_expand(t_token *lst, t_env *env);
void	ft_dquotes_dollar_expand(t_token *lst, t_env *env);
void	ft_squotes_dollar_expand(t_token *lst, t_env *env);
char	*ft_extract_env_value(t_env *env, char *key);
size_t	ft_getkey_size_usual_expand(char *token);


// src/parsing/states.c
void ft_parserror(char *msg1);
int ft_checkerror(int state, t_token *lst, long separators[3]);
int ft_state_5(t_token *lst, long separators[3]);
int ft_state_4(t_token *lst, long separators[3]);
int ft_state_3(t_token *lst, long separators[3]);
int ft_state_2(t_token *lst, long separators[3]);
int ft_state_1(t_token *lst, long separators[3]);
int ft_state_0(t_token *lst, long separators[3]);

// src/parsing/parser.c
int ft_token_is_word(t_type type);
int ft_token_is_redir(t_type type);
int ft_move_wspace(t_token **lst, t_type type);
int ft_move_next(t_token **lst, t_type type, long *separator);
int parser(t_token *first);

// src/term.c
void set_terminal(int status);

// src/utils.c
void ft_error(char *msg, char *var, char *msg2);
void ft_env_addback(t_env **first, t_env *new);
t_env *ft_env_new(void *key, void *value);
void print_env(t_env *print);
char *get_env_str(t_env *lst, char *get);
void ft_replace_env(t_env *lst, char *cmp, char *value);
void print_tab(char **tab);

// src/token.c
void	print_list(t_token *print);
void	ft_tokenadd_back(t_token **first, t_token *new);
void	ft_tokenadd_inside(t_token *current, t_token *new);
t_token *ft_token_new(void *content, t_type type);
#endif
