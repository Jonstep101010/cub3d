# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: muhnal <muhnal@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/12 16:16:21 by muhnal            #+#    #+#              #
#    Updated: 2024/02/26 11:04:23 by muhnal           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

NAME = libft.a

SRC_DIR = src/
OBJ_DIR = obj/

SRCS =	\
	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
	ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
	ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c \
	ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
	ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c \
	ft_isspace.c

BONUS_SRCS = \
	ft_lstnew.c ft_lstadd_front.c ft_lstadd_back.c ft_lstlast.c ft_lstsize.c ft_lstdelone.c \
	ft_lstclear.c ft_lstiter.c ft_lstmap.c

SRCS := $(addprefix $(SRC_DIR), $(SRCS))
BONUS_SRCS := $(addprefix $(SRC_DIR), $(BONUS_SRCS))

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
NC = \033[0m

OBJ = $(addprefix $(OBJ_DIR), $(notdir $(SRCS:.c=.o)))
BONUS_OBJ = $(addprefix $(OBJ_DIR), $(notdir $(BONUS_SRCS:.c=.o)))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@echo "$(RED)compiling.. $(NAME)$(NC)"

bonus: $(OBJ) $(BONUS_OBJ)
	@ar rc $(NAME) $(OBJ) $(BONUS_OBJ)
	@echo "$(RED)compiling.. $(NAME)$(NC)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@$(CC) -c -Wall -Wextra -Werror -o $@ $<

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)cleaned obj $(NAME)$(NC)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(RED)fcleaned $(NAME)$(NC)"


re: fclean all
