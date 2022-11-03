/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:31:19 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/03 16:31:27 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

// lexer.c
int lexer(t_token **token, char *input);

// token.c
void print_list(t_token *print);
void ft_tokenadd_back(t_token **first, t_token *new);
void ft_tokenadd_inside(t_token *current, t_token *new);
t_token *ft_token_new(void *content, t_type type);

#endif
