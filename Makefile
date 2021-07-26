NAME	= philo

SRCS	= srcs/main.c \
		  srcs/utils.c \
		  srcs/ft_atoi.c \
		  srcs/utils2.c

OBJS	= ${SRCS:.c=.o}

CFLAGS = -Wall -Werror -Wextra

UNAME = $(shell uname)

ifeq ($(UNAME), Linux)
	CFLAGS += -lpthread
endif

.c.o:
	gcc ${CFLAGS} -c -I includes $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	gcc ${CFLAGS} ${OBJS} -o ${NAME}

all: ${NAME}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all
