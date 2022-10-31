#
#
#                          M A K E F I L E
################################################################################

.DELETE_ON_ERROR:
.DEFAULT_GOAL			:= all
SHELL					:= $(shell which zsh)
.SHELLFLAGS				:= -eu -o pipefail -c

### C O M P I L E R   F L A G S ################################################

CC						:= cc #$(shell which gcc)
STD						?=
CFLAGS					:= -Wall -Wextra -Werror
LDFLAGS					?=

override MKDIR			:= mkdir -pv
override RM				:= rm -rvf

### D I R E C T O R Y ' S ######################################################

NAME					:= minishell
override FILES			:= signals.c ft_strndup.c ft_putendl_fd.c ft_swap_str.c ft_isalpha.c ft_isalnum.c \
						   ft_strcmp.c ft_isdigit.c ft_findi.c ft_strncmp.c ft_strlen.c ft_putstr_fd.c \
						   ft_strchr.c ft_putchar_fd.c ft_split.c ft_strdup.c ft_strlcpy.c lexer.c \
						   main.c unset.c exit.c cd.c env.c echo.c export.c pwd.c states.c token.c\
						   parser.c term.c utils.c 

SRCDIR					:= src
INCDIR					:= inc
OBJDIR					:= _obj
DEPDIR					:= _dep

### P A T T E R N   R U L E S ##################################################

override SUB			:= $(shell find $(SRCDIR) -type d)
override OBJ			:= $(FILES:%.c=$(OBJDIR)/%.o)
override DEP			:= $(patsubst $(OBJDIR)/%.o, $(DEPDIR)/%.d, $(OBJ))

### U T I L I T Y ##############################################################

COLOR					:= "\033[1;32m"
RESET					:= "\033[m"
NEWLINE					:= echo "\n\n"
LINK					:= echo $(COLOR)L1NK$(RESET)
LIBRARY					:= echo $(COLOR)L1BRARY$(RESET)
COMPILE					:= echo $(COLOR)C0MPILATI0N$(RESET)

### C O M P I L A T I O N   F U N C T I O N ####################################

define COMPILE_RULE
$(OBJDIR)/%.o:			$(1)/%.c Makefile | $(OBJDIR) $(DEPDIR)
	@$$(COMPILE);
	$$(CC) $$(STD) $$(CFLAGS) -I$$(INCDIR) \
	-c $$< -o $$@ \
	-MMD -MF $$(DEPDIR)/$$(*F).d;
endef

### R E C I P E S ##############################################################

.PHONY:					all clean fclean re ascii

all:					ascii $(NAME)

$(NAME):				$(OBJ)
						@$(LINK)
						$(CC) $+ $(LDFLAGS) -o $@ -lreadline

-include $(DEP)
$(foreach DIR, $(SUB), $(eval $(call COMPILE_RULE, $(DIR))))


$(OBJDIR) $(DEPDIR):
						@$(MKDIR) $@

clean:					;
						@$(RM) $(OBJDIR) $(DEPDIR)

fclean:					clean
						@$(RM) $(NAME)

re:						fclean all

ascii:
						@echo \
						$(COLOR) \
						"     _______  ________  ________  ________ \n" \
						"   ╱╱       ╲╱        ╲╱        ╲╱        ╲ \n" \
						"  ╱╱        ╱         ╱         ╱         ╱ \n" \
						" ╱       --╱         ╱       --╱         ╱   \n" \
						" ╲________╱╲___╱____╱╲________╱╲___╱____╱ \n " \
						$(RESET);
