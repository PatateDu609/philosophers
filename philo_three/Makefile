NAME			=	$(shell pwd | rev | cut -d'/' -f1 | rev)
CC				=	gcc
OBJS			=	$(SRCS:.c=.o)
CFLAGS			=	-Wall -Werror -Wextra -O3
LDFLAGS			=	-pthread

SRCS			=	main.c			\
					print.c			\
					utils.c			\
					init.c			\
					clear.c			\
					simulation.c	\
					actions.c		\
					# debug.c			\

%.o:			%.cpp
				echo $(NAME)
				$(CC) $(CFLAGS) -c $< -o $@

$(NAME):		$(OBJS)
				$(CC) $(LDFLAGS) $(OBJS) -o $(NAME)

all:			$(NAME)

clean:
				rm -f $(OBJS)

fclean:			clean
				rm -f $(NAME)

re:				fclean all

.PHONY:			all clean fclean re
# $(shell pwd | rev | cut -d'/' -f1 | rev)
