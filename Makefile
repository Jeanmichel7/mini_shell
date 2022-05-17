# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/17 05:26:46 by jrasser           #+#    #+#              #
#    Updated: 2022/05/17 07:49:28 by jrasser          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= srcs/main.c 

OBJS 		= ${SRCS:.c=.o}
RM			= rm -f
NAME 		= minishell
CC			= gcc
CFLAGS		= -Wall -Wextra
LDFLAGS		= -I./include/ -I./libft/

${NAME}	:	${OBJS}
			$(MAKE) -C ./libft
			gcc -o ${NAME} ${OBJS} -L./libft -lft

all :		${NAME}

clean :
			${RM} ${OBJS}

fclean :	clean
			${RM} ${NAME}
			make fclean -C libft/

re : 		fclean all

.PHONY:		all clean fclean re
