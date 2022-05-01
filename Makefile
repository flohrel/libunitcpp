###############
## Variables ##
###############

NAME		=	libunitcpp.a

VPATH		=	src
INCLDIR		=	include
BUILDIR		=	build
DEPDIR		=	$(BUILDIR)/.deps

SRC			=	TestUnit.cpp \
				TestSuite.cpp \
				TestCase.cpp \
				TestRunner.cpp \
				ResultCollector.cpp
OBJ			=	$(SRC:%.cpp=$(BUILDIR)/%.o)
DEP			=	$(SRC:%.cpp=$(DEPDIR)/%.d)

CXX			=	c++
CXXFLAGS	=	-Wall -Wextra -Werror -std=c++98
CPPFLAGS	:=	-I./$(INCLDIR)
DEPFLAGS	=	-MT $@ -MMD -MP -MF $(DEPDIR)/$*.d
AR			=	ar
ARFLAGS		=	rcs
RM			=	/bin/rm -rf
UNAME		:=	$(shell uname -s)

# FG COLORS
DEFAULT		=	\033[0m
BLACK		=	\033[1;30m
RED			=	\033[1;31m
GREEN		=	\033[1;32m
YELLOW		=	\033[1;33m
BLUE		=	\033[1;34m
MAGENTA 	=	\033[1;35m
CYAN 		=	\033[1;36m
WHITE 		=	\033[1;107m

# TERMCAPS
UP			=	\033[1A
DELETE		=	\033[2K
DELPREV		=	$(UP)$(DELETE)\r

# EMOJI
CHECK		=	\xE2\x9C\x94
CROSS		=	\xE2\x9D\x8C

# HEADER
HEAD_SIZE	=	32
NAME_SIZE	=	$(shell NAME='$(NAME)'; printf "$${#NAME}")
PAD_WIDTH	=	$(shell printf "$$((($(HEAD_SIZE) - $(NAME_SIZE)) / 2))")
PAD_PREC	=	$(shell printf "$$(($(PAD_WIDTH) / 2))")
PAD_CHAR	=	\*
PAD_STR		=	$(shell printf '$(PAD_CHAR)%.0s' {1..$(PAD_WIDTH)})
LEFT_PAD	=	$(shell printf '%-*.*s' $(PAD_WIDTH) $(PAD_PREC) $(PAD_STR))
RIGHT_PAD	=	$(shell printf '%*.*s' $(PAD_WIDTH) $$(($(PAD_PREC) - $(NAME_SIZE) % 2)) $(PAD_STR))
BODY_WIDTH	=	$(shell printf "$$(($(HEAD_SIZE) - 1))")


###########
## Rules ##
###########

.PHONY:			all bonus clean fclean header re verbose

all:			header $(NAME)

$(BUILDIR)/%.o:	%.cpp | $(DEPDIR)
				@printf "$(YELLOW)Compiling $@ and generating/checking make dependency file...$(DEFAULT)\n"
				@$(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@
				@printf '$(DELPREV)%-*s$(GREEN)$(CHECK)$(DEFAULT)\n' $(BODY_WIDTH) $(notdir $@)

$(NAME):		$(OBJ)
				@printf "$(YELLOW)Generating $@...$(DEFAULT)\n"
				@$(AR) $(ARFLAGS) $@ $^
				@printf "$(DELPREV)$(GREEN)Library generated$(DEFAULT)\n"

$(DEPDIR):
				@printf "$(YELLOW)Creating $@ folder...$(DEFAULT)\n"
				@mkdir -p $@
				@printf "$(DELPREV)"
$(DEP):
-include $(wildcard $(DEP))

header:
				@printf '$(LEFT_PAD)$(BLUE)$(NAME)$(DEFAULT)$(RIGHT_PAD)\n'

clean:
				@printf "$(YELLOW)Deleting object and dependency files...$(DEFAULT)\n"
				@$(RM) $(OBJ)
				@printf "$(DELPREV)Build files deleted\n"

fclean:			clean
				@printf "$(YELLOW)Deleting build directory and library...$(DEFAULT)\n"
				@$(RM) $(NAME) $(BUILDIR)
				@printf "$(DELPREV)Build directory and library deleted\n"

re:				fclean
				@make -s all
