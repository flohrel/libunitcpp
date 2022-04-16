###############
## Variables ##
###############

NAME		=	cpplibunit.a

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
CPPFLAGS	:=	-I./$(INCLDIR) -I./$(TESTDIR)
DEPFLAGS	=	-MT $@ -MMD -MP -MF $(DEPDIR)/$*.d
AR			=	ar
ARFLAGS		=	rcs
RM			=	/bin/rm -rf
UNAME		:=	$(shell uname -s)

DEFAULT		=	\033[0m
BLACK		=	\033[1;30m
RED			=	\033[1;31m
GREEN		=	\033[1;32m
YELLOW		=	\033[1;33m
BLUE		=	\033[1;34m
MAGENTA 	=	\033[1;35m
CYAN 		=	\033[1;36m
WHITE 		=	\033[1;107m
DELETE		=	\033[2K

###########
## Rules ##
###########

.PHONY:			all bonus clean fclean re verbose

all:			$(NAME)

$(BUILDIR)/%.o:	$(SRC) | $(DEPDIR)
				@printf "$(YELLOW)Compiling $@ and generating/checking make dependency file...$(DEFAULT)"
				@$(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@
				@printf "$(DELETE)\r$(GREEN)$@ compiled$(DEFAULT)\n"

$(NAME):		$(OBJ)
				@printf "$(YELLOW)Linking source files and generating $@ library...$(DEFAULT)"
				@$(AR) $(ARFLAGS) $@ $^
				@printf "$(DELETE)\r$(GREEN)$@ library generated$(DEFAULT)\n"

$(DEPDIR):
				@printf "$(YELLOW)Creating $@ folder...$(DEFAULT)"
				@mkdir -p $@
				@printf "$(DELETE)\r$(GREEN)$@ created$(DEFAULT)\n"
$(DEP):
-include $(wildcard $(DEP))

clean:
				@printf "$(YELLOW)Deleting object and dependency files...$(DEFAULT)"
				@$(RM) $(OBJ)
				@printf "$(DELETE)\r$(GREEN)Build files deleted$(DEFAULT)\n"

fclean:			clean
				@printf "$(YELLOW)Deleting build directory and binary...$(DEFAULT)"
				@$(RM) $(NAME) $(BUILDIR)
				@printf "$(DELETE)\r$(GREEN)Build directory and binary deleted$(DEFAULT)\n"

re:				fclean
				@make -s all
