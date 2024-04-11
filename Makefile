#------------------------------------------------------------------------------#
#                                  GENERICS                                    #
#------------------------------------------------------------------------------#

DEFAULT_GOAL: all
.DELETE_ON_ERROR: $(NAME)
.PHONY: all clean fclean re valgrind run 
HIDE = @


#------------------------------------------------------------------------------#
#                                VARIABLES                                     #
#------------------------------------------------------------------------------#

# Compiler and flags
CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra -I. -I./$(INCDIR) -pthread -g3 
RM		=	rm -fr

# Output file name
NAME	=	philo

# Sources are all .c files
SRCDIR	=	src/
SRCS	=	src/init.c \
			src/utils.c \
			src/monitor.c \
			src/routine.c \
			src/utils2.c \
			src/main.c

# Objects are all .o files
OBJDIR	=	bin/
OBJS	=	$(patsubst $(SRCDIR)%.c,$(OBJDIR)%.o,$(SRCS))

# Includes are all .h files
INCDIR	=	include/
INC		=	$(INCDIR)philo.h


#------------------------------------------------------------------------------#
#                                 TARGETS                                      #
#------------------------------------------------------------------------------#

all: $(NAME)

$(NAME): $(OBJS)
	$(HIDE)$(CC) $(CFLAGS) -o $@ $^

$(OBJS): $(OBJDIR)%.o : $(SRCDIR)%.c $(INC) | $(OBJDIR)
	$(HIDE)$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	$(HIDE)mkdir -p $@

clean:
	$(HIDE)$(RM) $(OBJDIR)

fclean: clean
	$(HIDE)$(RM) $(NAME)

re: fclean all

run: all
	$(HIDE)./$(NAME) 4 810 200 200


