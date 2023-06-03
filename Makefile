# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyunjki2 <hyunjki2@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/07 21:56:35 by jihyeole          #+#    #+#              #
#    Updated: 2023/06/03 18:18:23 by hyunjki2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRCS = main.c init.c utils.c env_utils1.c env_utils2.c make_heredoc.c \
	   error.c redirect.c expand_env.c pipe.c finalization.c check.c \
	   exec.c builtin.c read_command.c check_cmd.c count_word_with_expand.c\
	   expand_and_fill_command.c expand_env_in_parsing.c expand_env_in_parsing2.c\
	   handle_input_redirection.c handle_output_redirection.c parsing_utils.c\
	   parsing_utils2.c put_command.c sep.c split_command.c error_m.c
OBJS = $(SRCS:.c=.o)
CC = CC
CFLAGS = -Wall -Wextra -Werror -I ~/.brew/opt/readline/include
LIBS = -Llibft -lft

all : $(NAME)

$(NAME) : $(OBJS)
	make -C libft bonus
	$(CC) $(OBJS) $(LIBS) -o $(NAME) -lreadline -L ~/.brew/opt/readline/lib

%.o : %.c 
	$(CC) $(CFLAGS) -c $< -o $@ 

clean : 
	make -C libft clean
	rm -f $(OBJS)

fclean : clean
	make -C libft fclean
	rm -f $(NAME)

re : fclean all 

.PHONY : all clean fclean re
