##
## Makefile for lol in /home/tetra/rendu/psu/PSU_2016_strace
## 
## Made by Arthur Josso
## Login   <arthur.josso@epitech.eu>
## 
## Started on  Mon Apr  3 10:46:34 2017 Arthur Josso
## Last update Sat Apr 22 16:01:53 2017 Arthur Josso
##

NAME	=	ftrace

CC	=	gcc

INC	=	./inc/

CFLAGS	+=	-I$(INC)		\
		-Wall -Wextra

LDFLAGS	+=	-lelf -lm

SRC	=	./src/

ELF	=	./src/elf/

GRAPH	=	./src/graph/

BRANCH	=	./src/branch/

SRCS	=	$(SRC)main.c		\
		$(SRC)misc.c		\
		$(SRC)trace.c		\
		$(SRC)syscalls.c	\
		$(SRC)path_finder.c	\
		$(SRC)func_stack.c	\
		$(SRC)parsing.c		\
		$(SRC)print.c		\
		$(SRC)signal.c		\
		$(BRANCH)core.c		\
		$(BRANCH)test.c		\
		$(BRANCH)exec.c		\
		$(ELF)init.c		\
		$(ELF)fini.c		\
		$(ELF)init_funcs.c	\
		$(ELF)init_str_funcs.c	\
		$(ELF)getter.c		\
		$(GRAPH)management.c	\
		$(GRAPH)generation.c	\
		$(GRAPH)fini.c

OBJS	=	$(SRCS:.c=.o)

RM	=	rm -f

all:		$(NAME)

$(NAME):	$(OBJS)
		@$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
		@$(RM) $(OBJS)

fclean:		clean
		@$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
