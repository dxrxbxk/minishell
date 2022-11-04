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
STD						:= -std=c99
CFLAGS					:= -Wall -Wextra -Werror -g3
LDFLAGS					?= -MMD -MF

override MKDIR			:= mkdir -pv
override RM				:= rm -rvf

### D I R E C T O R Y ' S ######################################################

NAME					:= minishell

override FILES			:=	main.c \
							env.c \
							ft_strndup.c \
							ft_putendl_fd.c \
							ft_swap_str.c \
							ft_isalpha.c \
							ft_isalnum.c \
							ft_strcmp.c \
							ft_isdigit.c \
							ft_findi.c \
							ft_strncmp.c \
							ft_strlen.c \
							ft_putstr_fd.c \
							ft_strchr.c \
							ft_putchar_fd.c \
							ft_strjoin.c \
							ft_split.c \
							ft_strlcat.c \
							ft_strdup.c \
							ft_strlcpy.c \
							unset.c \
							exit.c \
							cd.c \
							echo.c \
							export.c \
							pwd.c \
							signals.c \
							expand.c \
							ft_squotes_dollar_expand.c \
							ft_usual_dollar_expand.c \
							ft_quotes_expand.c \
							states.c \
							parser.c \
							ft_dquotes_dollar_expand.c \
							ft_tokencat.c \
							ft_dollar_expand.c \
							lexer.c \
							token.c \
							utils.c \
							env_utils.c \
							ft_error.c \
							ft_strcpy.c \
							ft_strcat.c \
							ft_words_count.c

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
	$$(CC) $$(STD) -I$$(INCDIR) $$(CFLAGS) \
	-c $$< -o $$@ \
	-MMD -MF $$(DEPDIR)/$$(*F).d;
endef

### R E C I P E S ##############################################################

.PHONY:					all clean fclean re ascii

all:					ascii $(NAME)

$(NAME):				$(OBJ)
						@$(LINK)
						$(CC) $^ -lreadline -o $@

-include $(DEP)
$(foreach DIR, $(SUB), $(eval $(call COMPILE_RULE, $(DIR))))

debug:					
						@echo $(FILES) \
						@echo $(NEWLINE) \
						@echo $(SUB) \
						@echo $(NEWLINE) \
						@echo $(OBJ) \
						@echo $(NEWLINE) \
						@echo $(INCDIR)

$(OBJDIR) $(DEPDIR):
						@$(MKDIR) $@

clean:					;
						@$(RM) $(OBJDIR) $(DEPDIR)

fclean:					clean
						@$(RM) $(NAME)

re:						fclean all

compile:				
						@$(COMPILE)

ascii:
						@echo \
						$(COLOR) \
						"███    ██████████   ████████ \n" \
						"████  █████   ███  ████		\n" \
						"██ ████ ████████████ █████		\n" \
						"██  ██  ███   ███  ████		\n" \
						"██      ███   ███   ████████	\n" \
						$(RESET);
