# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pruangde <pruangde@student.42bangkok.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/17 12:37:19 by pruangde          #+#    #+#              #
#    Updated: 2022/10/27 10:48:01 by pruangde         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UNAME = uname -s

ifeq ($(UNAME), Linux)
	CC = clang
else
	CC = gcc
endif

CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
NAME = pipex

LIBFT_PATH = libft
LIBFT = $(LIBFT_PATH)/libft.a

SRCS = main.c pipex_utils_1.c pipex_utils_2.c

.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(LIBFT)
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

norm:
	@echo "------------------------------------"
	@echo " !!!!!!!!   NORMINETTE   !!!!!!!!"
	@echo ""
	@norminette -R CheckForbiddenSourceHeader $(SRCS)
	@norminette -R CheckDefine *.h
	@echo ""
	@echo "------------------------------------"
