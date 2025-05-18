NAME = philo
CC = cc

CFLAGS = -Wall -Werror -Wextra -g  -fsanitize=thread 

SRCS = main.c\
	functions_utils.c\
	routine.c\
	memory_management.c\
	philo_create_init.c\
	time_manager.c\
	life_philos.c

OBJS = $(SRCS:.c=.o)

%.o : %.c
	${CC} ${CFLAGS} -c $< -o $@

all: ${NAME}

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o ${NAME}

clean:
	rm -rf ${OBJS}

fclean: clean
	rm -rf ${NAME}

re: fclean all

