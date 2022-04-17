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


###########
## Rules ##
###########

.PHONY:			all bonus clean fclean header re verbose

all:			header $(NAME)

$(BUILDIR)/%.o:	%.cpp | $(DEPDIR)
				@printf "$(YELLOW)Compiling $@ and generating/checking make dependency file...$(DEFAULT)\n"
				@$(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@
				@printf "$(DELPREV)%-25s%*s$(GREEN)$(CHECK)$(DEFAULT)\n" $@ $(shell printf $(NAME) | wc -c)

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
				@printf "**********%3$1s$(BLUE)$(NAME)$(DEFAULT)%3$1s**********\n" ""

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
