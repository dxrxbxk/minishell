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
CFLAGS					:= -Wall -Wextra -Werror -g3 -D_GNU_SOURCE
LDFLAGS					?= -MMD -MF

override MKDIR			:= mkdir -pv
override RM				:= rm -rvf

### D I R E C T O R Y ' S ######################################################

NAME					:= minishell

override FILES			:=	$(addsuffix .c, \
							main \
							ft_env \
							ft_strndup \
							ft_putendl_fd \
							ft_swap_str \
							ft_isalpha \
							ft_isalnum \
							ft_strcmp \
							ft_isdigit \
							ft_findi \
							ft_strncmp \
							ft_strlen \
							ft_putstr_fd \
							ft_strchr \
							ft_putchar_fd \
							ft_strjoin \
							ft_split \
							ft_strlcat \
							ft_strdup \
							ft_strlcpy \
							ft_calloc \
							ft_bzero \
							unset \
							exit \
							cd \
							echo \
							export \
							pwd \
							signals \
							expand \
							ft_squotes_dollar_expand \
							ft_usual_dollar_expand \
							ft_quotes_expand \
							states \
							states_2 \
							parser \
							ft_dquotes_dollar_expand \
							ft_tokencat \
							ft_dollar_expand \
							ast_init	\
							ast_utils	\
							ast_utils_2	\
							lexer \
							parsing	\
							token \
							exec_builtins \
							builtins_redirections	\
							manage_builtins			\
							child_utils	\
							manage_child	\
							exec_child	\
							execution	\
							exec_utils	\
							ft_find_cmd_path	\
							ft_interpret_child_status	\
							ft_wait_children	\
							exec_pipe_child		\
							manage_pipe_child	\
							manage_pipe_fds		\
							pipe_redirections	\
							manage_redirections	\
							redirections_utils	\
							set_heredoc_files	\
							apply_heredoc	\
							ft_free_children	\
							free_tab			\
							utils \
							env \
							env_utils \
							ft_error \
							ft_strcpy \
							ft_strcat \
							ft_words_count \
							ft_atoi \
							env_utils_2 \
							ft_lst_to_tab \
							ft_mega_join \
							get_next_line \
							get_input \
							ft_memptr \
							ft_itoa)

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
PURPLE_1				:= "\e[38;2;113;31;149m"
PURPLE_2				:= "\e[38;2;101;25;134m"
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

all:					ascii2 $(NAME)

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

leak:
						@echo -e "{\nleak readline\nMemcheck:Leak\n...\nfun:readline\n}\n{\nleak add_history\nMemcheck:Leak\n...\nfun:add_history\n}" > rl_leaks.txt


compile:				
						@$(COMPILE)

ascii2:			
			@echo				"                                 \n"	\
					$(PURPLE_1)	"█▀▄▀█ █ █▄░█ █ █▀ █░█ █▀▀ █░░ █░░\n"	\
					$(PURPLE_2)	"█░▀░█ █ █░▀█ █ ▄█ █▀█ ██▄ █▄▄ █▄▄\n"	\
					$(RESET);

ascii:                  
						@echo \
						$(COLOR) \
						"███    ██████████   ████████ \n" \
						"████  █████   ███  ████		\n" \
						"██ ████ ████████████ █████		\n" \
						"██  ██  ███   ███  ████		\n" \
						"██      ███   ███   ████████	\n" \
						$(RESET);
