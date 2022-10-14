SRCS				= main.c utils.c signals.c term.c lexer.c token.c

SRCSDIR				= src

INCDIR				= incdir

HEADERS				= minishell.h

CC					= cc

CFLAGS				= -Wall -Wextra -Werror

OBJDIR				= obj

LIBFT				= libft/libft.a

NAME				= a.out

FILES				= $(addprefix $(SRCSDIR)/, $(SRCS))
OBJS				= $(patsubst $(OBJDIR)/%.o, $(SRCSDIR)/%.c, $(FILES))

##$(OBJDIR)/%.o:		%.c | $(OBJDIR)
##					$(CC) $(CFLAGS) -c $< -o $@

all:				$(NAME)

$(NAME):	$(OBJS)
					make -C libft
					$(CC) $^ -o $(NAME) $(LIBFT) -lreadline -I$(INCDIR)


$(OBJDIR)	:
					mkdir -p $@

clean:
					make -C libft clean
					rm -rf $(OBJDIR)

fclean:				clean
					make -C libft fclean
					rm -rf $(NAME)

re:					fclean all
