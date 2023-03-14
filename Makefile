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
	@$(CC) $(CFLAGS) -o $(NAME) $(INC) $(OBJS)
	@echo "Linked into executable \033[0;32mphilo\033[0m."

%.o : %.c
	@$(CC) $(CFLAGS) $(INC) -c $^ -o $@
	@echo "Compiling $<."

clean :
	@$(RM) $(OBJS)

fclean :
	@make clean
	@$(RM) $(NAME)

re :
	@make fclean
	@make all

.PHONY : all, clean, fclean, re
