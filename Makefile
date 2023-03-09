NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

SRCS = $(addprefix src/, main.c \
		init.c \
		start_philo.c \
		philo_act.c \
		time.c \
		util.c)

OBJS = $(SRCS:.c=.o)

INC = -I./inc

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(INC) $(OBJS)

%.o : %.c
	$(CC) $(CFLAGS) $(INC) -c $^ -o $@

clean :
	$(RM) $(OBJS)

fclean :
	@make clean
	$(RM) $(NAME)

re :
	@make fclean
	@make all

.PHONY : all, clean, fclean, re
