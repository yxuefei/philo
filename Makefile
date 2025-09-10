CC		= cc
CFLAGS	= -Wall -Wextra -Werror -pthread

NAME	= philo
SRCS	= main.c parse_args.c init.c utils_time.c actions.c monitor.c utils.c sync.c
OBJS	= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
