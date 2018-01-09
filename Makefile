# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdjeghba <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/13 13:30:08 by sdjeghba          #+#    #+#              #
#    Updated: 2018/01/09 13:01:39 by sdjeghba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
INC			=	-I./includes
CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra
LIB			=	./libft/libft.a
P_LIB		=	./libft/
P_SRC		=	./srcs/
RM			=	rm -rf

SRCS		=	$(P_SRC)main.c				\
				$(P_SRC)minishell.c			\
				$(P_SRC)handle_env.c		\
				$(P_SRC)cd_built.c			\
				$(P_SRC)tools.c

OBJS		=	$(SRCS:.c=.o)

all:			$(NAME)

$(NAME):		$(OBJS)
				make -C $(P_LIB)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(INC) $(LIB)

%.o:			%.c
				$(CC) $(CFLAGS) -c $< -o $@


clean:
				make -C $(P_LIB) clean
				$(RM) $(OBJS)

fclean:			clean
				make -C $(P_LIB) fclean
				$(RM) $(NAME)

re:				fclean all
