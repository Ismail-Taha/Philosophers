NAME = philo
CC = cc

CFLAGS = -Wall -Werror -Wextra -g  -fsanitize=thread 

SRCS = main.c\
	utils_fnc.c\
	schedule.c\
	memory.c\
	philo_init.c\
	time.c\
	falasifa.c

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

