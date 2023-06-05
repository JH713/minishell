# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/07 21:56:35 by jihyeole          #+#    #+#              #
#    Updated: 2023/06/05 23:34:16 by jihyeole         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRCS = main.c init.c utils.c env_utils1.c env_utils2.c make_heredoc.c \
	   error.c redirect.c expand_env.c pipe.c finalization.c check.c \
	   exec.c builtin.c read_command.c check_cmd.c count_word_with_expand.c\
	   expand_and_fill_command.c expand_env_in_parsing.c expand_env_in_parsing2.c\
	   handle_input_redirection.c handle_output_redirection.c parsing_utils.c\
	   parsing_utils2.c put_command.c check_sep.c split_command.c error_m.c free_info.c\
	   signal.c single_builtin.c single_builtin2.c redirect_fd.c env_utils3.c\
	   builtin_echo.c builtin_export1.c builtin_export2.c utils2.c builtin_cd.c
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
