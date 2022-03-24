# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtrietz <mtrietz@student.42wolfsburg.de>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/16 07:50:46 by mtrietz           #+#    #+#              #
#    Updated: 2022/03/22 09:13:29 by mtrietz          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wextra -Wall -Werror
LIBFT_DIR = ./libft

NAME = minishell

SRCS =	minishell.c error_helpers_1.c get_next_line.c \
		manage_commands_2.c  split_commands_1.c fd_handle_1.c \
		helpers_functions_1.c test_paths_1.c \
		free_helpers.c ft_devide_command.c libft_helpers1.c manage_commands_1.c \
		pipes_helpers_1.c check_builtsin.c  libft_helpers_2.c env_init.c \
		env_env.c echo.c exit_shell.c env_set_value.c ft_is_bashname.c \
		ft_strcmp.c ft_arrlen.c fs_utils.c env_export.c env_unset.c \
		conversion_helpers.c sig_handler.c ft_lst2arr.c chk_inval_opt.c \
		conversion_helpers_2.c ft_devide_command_helpers_1.c \
		env_print.c ft_get_key.c manage_commands_3.c errmsg.c \
		ft_isstrnum.c ft_pipes_utils.c manage_pipes_1.c free_helpers_1.c \
		struct_helpers.c parse_helpers.c exec_helpers.c exec_helpers_2.c \
		ft_devide_command_helpers_2.c ft_devide_command_helpers_3.c

OBJS = $(SRCS:.c=.o)

LIBS = -L$(LIBFT_DIR) -lft -lreadline -L /opt/homebrew/opt/readline/lib -I /opt/homebrew/opt/readline/include

all: $(LIBFT_DIR)/libft.a $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -I/opt/homebrew/opt/readline/include -o $@ $<

$(LIBFT_DIR)/libft.a:
	make -C $(LIBFT_DIR) bonus
	make -C $(LIBFT_DIR) clean

clean:
	make -C $(LIBFT_DIR) clean
	$(RM) $(OBJS)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
