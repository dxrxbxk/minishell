SRCS_UTILS			=	ft_strcmp.c ft_strdup.c ft_findi.c ft_strndup.c \
						ft_strncmp.c ft_strchr.c ft_split.c ft_strlcpy.c \
						ft_putendl_fd.c ft_strlen.c ft_putstr_fd.c ft_putchar_fd.c 

SRCS				=	main.c utils.c signals.c term.c lexer.c token.c parsing/parser.c	\
						$(addprefix utils/, $(SRCS_UTILS))

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
