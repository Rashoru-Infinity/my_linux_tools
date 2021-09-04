# **************************************************************************** #
#                                                                              #
#    Makefile                                                                  #
#                                                                              #
#    By: Keita Hagiwara <al19136@shibaura-it.ac.jp>                            #
#                                                                              #
#    Created: 2021/09/05 01:57:05 by Keita Hagiwara                            #
#    Updated: 2021/09/05 01:57:05 by Keita Hagiwara                            #
#                                                                              #
# **************************************************************************** #

CC	= gcc
CFLAGS	= -Wall -Wextra -Werror
SRCS	= printdump.c
NAME	= printdump
OBJS	= $(SRCS:.c=.o)
RM	= rm -f

all	:	$(NAME)

.c.o	:
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME)	: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) 

clean	:
	$(RM) $(OBJS)

fclean	: clean
	$(RM) $(NAME)

re	: fclean all

.PHONY	: clean fclean all re
