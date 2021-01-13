NAME			=	$(shell pwd | rev | cut -d'/' -f1 | rev)
CC				=	gcc
OBJS			=	$(SRCS:.c=.o)
CFLAGS			=	-Wall -Werror -Wextra
LDFLAGS			=	-fsanitize=address -fsanitize=leak -g

SRCS			=	main.c		\
					print.c		\
					utils.c		\
					init.c		\

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
