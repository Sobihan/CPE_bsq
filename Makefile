##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

CC		=	gcc -g

RM		=	rm -f

NAME		=	bsq

SRCS		=	src/bsq.c	\
			src/main.c

OBJS		=	$(SRCS:.c=.o)

.PHONY		:	clean fclean re

all		:	$(NAME)

$(NAME)		:	$(OBJS)
			$(CC) $(OBJS) -o $(NAME)

clean		:
			$(RM) $(OBJS)

fclean		:	clean
			$(RM) $(NAME)

re		:	fclean all
