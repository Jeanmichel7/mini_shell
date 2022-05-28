# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/17 05:26:46 by jrasser           #+#    #+#              #
#    Updated: 2022/05/28 22:00:12 by jrasser          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= srcs/main.c \
			srcs/execution/jm_part.c \
			srcs/execution/pipe.c \
			srcs/execution/utils_pipe.c \
			srcs/execution/pipe_checker.c \
			srcs/execution/builtins/builtins1.c \
			srcs/execution/builtins/env.c

OBJS 		= ${SRCS:.c=.o}
RM			= @rm -f
NAME 		= minishell
CC			= gcc
CFLAGS		= -Wall -Wextra -g
LDFLAGS		= -I./include/ -I./libft/
DEBEUG		= -g -fsanitize=address

.c.o:		
			@${CC} ${CFLAGS} -c ${LDFLAGS} $< -o ${<:.c=.o}

${NAME}	:	${OBJS}
			@$(MAKE) --no-print-directory -C ./libft
			@gcc -o ${NAME} ${OBJS} ${DEBEUG} -lreadline -L./libft -lft

all :		${NAME}

clean :
			${RM} ${OBJS}

fclean :	clean
			${RM} ${NAME}
			@make --no-print-directory fclean -C libft/

re : 		fclean all

.PHONY:		all clean fclean re
