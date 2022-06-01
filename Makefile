# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/17 05:26:46 by jrasser           #+#    #+#              #
#    Updated: 2022/06/01 17:58:29 by jrasser          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= srcs/main.c \
			srcs/execution/pipe.c \
			srcs/execution/pipe_checker.c\
			srcs/parse/parsing.c  \
			srcs/parse/ft_split_and_omit.c  \
			srcs/parse/ft_strjoin_andadd_rt.c  \
			srcs/parse/print_cmd.c \
			srcs/parse/redirection.c \
			srcs/parse/redirection2.c \
			srcs/parse/redirection3.c \
			srcs/parse/ft_split_redirection.c \
			srcs/parse/ft_replace_elements.c \
			srcs/parse/list_utils.c \
			srcs/parse/parsing_utils.c \
			srcs/parse/parsing_utils2.c \
			srcs/parse/parsing_utils3.c \
			srcs/execution/utils_pipe.c \
			srcs/execution/check_error.c \
			srcs/execution/free.c \
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
			@${CC} -g ${CFLAGS} -c ${LDFLAGS} $< -o ${<:.c=.o}

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
