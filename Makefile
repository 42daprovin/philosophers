NAME	= philo

SRCS	= srcs/main.c \
		  srcs/utils.c \
		  srcs/ft_atoi.c \
		  srcs/utils2.c \
		  srcs/utils3.c

OBJS	= ${SRCS:.c=.o}

CFLAGS = -Wall -Werror -Wextra

LFLAG =

UNAME = $(shell uname)

ifeq ($(UNAME), Linux)
	LFLAG += -lpthread
endif

.c.o:
	gcc ${CFLAGS} -c -I includes $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	gcc ${CFLAGS} ${OBJS} ${LFLAG} -o ${NAME}

all: ${NAME}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all
