NAME	= philo

SRCS	= srcs/main_no_join.c \
		  srcs/utils.c \
		  srcs/ft_atoi.c \
		  srcs/utils2.c

OBJS	= ${SRCS:.c=.o}

.c.o:
	gcc -c -I includes $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	gcc ${OBJS} -o ${NAME}

all: ${NAME}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all
