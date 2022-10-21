SRCS				= main.c utils.c signals.c term.c lexer.c token.c ft_strcmp.c builtins/echo.c builtins/cd.c builtins/export.c

SRCSDIR				= src

INCDIR				= incdir

HEADERS				= minishell.h

CC					= cc

CFLAGS				= -Wall -Wextra -Werror -g3

OBJDIR				= obj

LIBFT				= libft/libft.a

NAME				= a.out

FILES				= $(addprefix $(SRCSDIR)/, $(SRCS))
OBJS				= $(patsubst $(OBJDIR)/%.o, $(SRCSDIR)/%.c, $(FILES))

##$(OBJDIR)/%.o:		%.c | $(OBJDIR)
##					$(CC) $(CFLAGS) -c $< -o $@

all:				$(NAME)

$(NAME):	$(OBJS)
					make -s -C libft
					$(CC) $(CFLAGS) $^ -o $(NAME) -lreadline -I$(INCDIR) -I./libft $(LIBFT)

$(OBJDIR)	:
					mkdir -p $@

clean:
					make -s -C libft clean
					rm -rf $(OBJDIR)

fclean:				clean
					make -s -C libft fclean
					rm -rf $(NAME)

re:					fclean all
