SRCS			= main.c utils.c signals.c term.c

HEADERS			= minishell.h

CC          	= cc

CFLAGS      	= -Wall -Wextra -Werror

OBJDIR 			= obj

LIBFT = libft/libft.a

NAME			= a.out 

OBJS		= $(SRCS:%.c=$(OBJDIR)/%.o)


$(OBJDIR)/%.o:%.c $(HEADERS) | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	make -C libft
	$(CC) $^ -o $(NAME) $(LIBFT) -lreadline

$(OBJDIR) :
	mkdir -p $@

clean:
	make -C libft clean
	rm -rf $(OBJDIR)

fclean:	clean
	make -C libft fclean
	rm -rf $(NAME)

re:         fclean all

.PHONY:     all clean fclean re
