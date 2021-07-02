NAME =	philo

SRCS =	philo.c \
		utils.c \
		start_actions.c

OBJS =	$(SRCS:.c=.o)

SRC_D =	$(SRCS:.c=.d)

CC =	gcc

FLAGS =	-g -MMD -Wall -pthread

.c.o:
		$(CC) $(FLAGS) -c $< -o ${<:.c=.o}

$(NAME): $(OBJS)
		$(CC) $(FLAGS) $(OBJS) -o $(NAME)
		@echo "Philo created"

all:	$(NAME)

clean:
		rm -f $(OBJS)
		rm -f $(SRC_D)
		@echo "Object files were deleted"

fclean:	clean
		rm -f $(NAME)
		@echo "Everithing was deleted"

re:		fclean all

-include $(SRC_D)
#.SILENT: