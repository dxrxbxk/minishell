##SRCS_UTILS			=	ft_strcmp.c ft_strdup.c ft_findi.c ft_strndup.c \
						ft_strncmp.c ft_strchr.c ft_split.c ft_strlcpy.c \
						ft_putendl_fd.c ft_strlen.c ft_putstr_fd.c ft_putchar_fd. \
						$(addprefix utils/, $(SRCS_UTILS))
SRCS				=	main.c utils.c signals.c term.c lexer.c token.c builtins/echo.c builtins/cd.c \
						builtins/export.c parsing/parser.c utils/ft_strcmp.c utils/ft_strdup.c utils/ft_findi.c utils/ft_strndup.c \
						utils/ft_strncmp.c utils/ft_strchr.c utils/ft_split.c utils/ft_strlcpy.c \
						utils/ft_putendl_fd.c utils/ft_strlen.c utils/ft_putstr_fd.c utils/ft_putchar_fd.c utils/ft_isalnum.c utils/ft_isalpha.c utils/ft_isdigit.c builtins/unset.c builtins/env.c builtins/exit.c
SRCSDIR				=	src

INCDIR				=	incdir

HEADERS				=	minishell.h

CC					=	cc

CFLAGS				=	-Wall -Wextra -Werror -g3

OBJDIR				=	obj

LIBFT				=	libft/libft.a

NAME				=	a.out

FILES				=	$(addprefix $(SRCSDIR)/, $(SRCS))
OBJS				=	$(patsubst $(OBJDIR)/%.o, $(SRCSDIR)/%.c, $(FILES))

##$(OBJDIR)/%.o:		%.c | $(OBJDIR)
##					$(CC) $(CFLAGS) -c $< -o $@

all:				$(NAME)

$(NAME):	$(OBJS)
					make -s -C libft
					$(CC) $(CFLAGS) $^ -o $(NAME) -lreadline -I$(INCDIR) -I./libft -g3 #$(LIBFT)

$(OBJDIR)	:
					mkdir -p $@

clean:
					make -s -C libft clean
					rm -rf $(OBJDIR)

fclean:				clean
					make -s -C libft fclean
					rm -rf $(NAME)

re:					fclean all
