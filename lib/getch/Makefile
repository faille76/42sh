##
## Makefile for example in /home/alies_a/perso/simple-getch
##
## Made by alies_a
## Login   <alies_a@epitech.net>
##
## Started on  Mon May  9 15:35:25 2016 alies_a
## Last update Sat Jun  4 18:12:28 2016 Frederic ODDOU
##

ECHO		=	/bin/echo -e
DEFAULT		=	"\033[00m"
GREEN		=	"\033[0;32m"
TEAL		=	"\033[1;36m"
RED		=	"\033[0;31m"
BLUE		=	"\033[0;34m"

NAME	=	libgetch.a

CC	=	gcc

INC	=	./include/

RM	=	rm -f

SRC	=	./src/

CH	=	./src/ch/

RD	=	./src/rd/

HISTORY	=	./src/history/

CFLAGS	=	-I$(INC) \
		-Wall -Wextra -W

SRCS	=	$(CH)get.c \
		$(CH)key.c \
		$(CH)ch.c \
		$(CH)stradd.c \
		$(RD)line.c \
		$(RD)char.c \
		$(RD)key.c \
		$(RD)left.c \
		$(RD)right.c \
		$(RD)up.c \
		$(RD)back.c \
		$(RD)down.c \
		$(RD)tab.c \
		$(RD)del.c \
		$(RD)ctrl_l.c \
		$(RD)put.c \
		$(RD)add_char.c \
		$(RD)rm_char.c \
		$(RD)disp.c \
		$(RD)free.c \
		$(HISTORY)history.c \
		$(HISTORY)down.c \
		$(HISTORY)up.c \

OBJS	=	$(SRCS:.c=.o)

all:		message $(NAME)

$(NAME):	$(OBJS)
		@ar rc $(NAME) $(OBJS) && \
	 	$(ECHO) $(GREEN) "[AR]" $(TEAL) $(NAME) $(DEFAULT) || \
	 	$(ECHO) $(RED) "[XX]" $(TEAL) $(NAME)
		@ranlib $(NAME) && \
	 	$(ECHO) $(GREEN) "[AR]" $(TEAL) $(NAME) $(DEFAULT) || \
	 	$(ECHO) $(RED) "[XX]" $(TEAL) $(NAME)

message:
	@$(ECHO) $(BLUE) "  _____      _    _____ _    _ " $(DEFAULT)
	@$(ECHO) $(BLUE) " / ____|    | |  / ____| |  | |" $(DEFAULT)
	@$(ECHO) $(BLUE) "| |  __  ___| |_| |    | |__| |" $(DEFAULT)
	@$(ECHO) $(BLUE) "| | |_ |/ _ \ __| |    |  __  |" $(DEFAULT)
	@$(ECHO) $(BLUE) "| |__| |  __/ |_| |____| |  | |" $(DEFAULT)
	@$(ECHO) $(BLUE) " \_____|\___|\__|\_____|_|  |_|" $(DEFAULT)

clean:
		@$(RM) $(OBJS)

fclean:		clean
		@$(RM) $(NAME)

re:		fclean all

.c.o:
		@gcc $(CFLAGS) $(LDFLAGS) -c $< -o $@ && \
		$(ECHO) $(GREEN) "[OK]" $(TEAL) $< $(DEFAULT) || \
		$(ECHO) $(RED) "[XX]" $(TEAL) $< $(DEFAULT)

.PHONY: all clean fclean re $(NAME) message .c.o
