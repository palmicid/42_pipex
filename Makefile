# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pruangde <pruangde@student.42bangkok.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/17 12:37:19 by pruangde          #+#    #+#              #
#    Updated: 2022/10/27 03:47:53 by pruangde         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UNAME = uname -s

ifeq ($(UNAME), Linux)
	CC = clang
else
	CC = gcc
endif

CFLAGS = -Wall -Wextra -Werror -g
RM = rm -rf
NAME = pipex

LIBFT_PATH = libft
LIBFT = $(LIBFT_PATH)/libft.a

SRCS = main.c pipex_utils_1.c pipex_utils_2.c
#OBJS = $(SRCS:.c=.o)

.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(LIBFT) #$(OBJS)
	$(CC) $(CFLAGS) $(LIBFT) $(SRCS) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_PATH) all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make -C $(LIBFT_PATH) clean
	@$(RM) $(OBJS) $(BN_OBJS)

fclean: clean
	@make -C $(LIBFT_PATH) fclean
	@$(RM) $(NAME)

re: fclean all

test:
	$(CC) maintest.c $(NAME)
	#valgrind --vgdb=no --leak-check=full --show-leak-kinds=all ./a.out

leak:
	leaks --atExit -- ./a.out

san:
	$(CC) -fsanitize=address -fno-omit-frame-pointer maintest.c

norm:
	@echo "------------------------------------"
	@echo " !!!!!!!!   NORMINETTE   !!!!!!!!"
	@echo ""
	@norminette -R CheckForbiddenSourceHeader ft_*.c
	@norminette -R CheckDefine *.h
	@echo ""
	@echo "------------------------------------"
