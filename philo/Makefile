NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
SRCS = main.c \
       inp_check.c \
       prog_init.c \
	   falasifa_act.c \
	   falasifa_rout.c \
	   three_philo_rout.c \
	   philo_init.c \
	   time_utils.c \
	   utils_func.c \



OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS) falasifa.h
	$(CC) $(CFLAGS) $(OBJS) -o $@

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.SECONDARY : $(OBJS)