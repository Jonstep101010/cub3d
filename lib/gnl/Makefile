# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: muhnal <muhnal@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/26 09:49:32 by muhnal            #+#    #+#              #
#    Updated: 2024/02/26 11:03:21 by muhnal           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

NAME = gnl.a
CFLAGS = -Wall -Wextra -Werror

R = \033[0;31m
G = \033[0;32m
YELLOW = \033[0;33m
B = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
NC = \033[0m

# Kaynak dosyalarını ve hedef obje dosyalarını tanımlayın
SRC = get_next_line.c get_next_line_utils.c
OBJS_DIR = ./obj/
OBJS = $(addprefix $(OBJS_DIR), $(SRC:.c=.o))

HEADER = get_next_line.h

all: $(NAME)

# Statik kütüphane oluşturma kuralı
$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)
	echo "$(G)gnl.a successfully created! $(NC)"

# Obj dosyalarını derlemek için genel kural
$(OBJS_DIR)%.o: %.c $(HEADER)
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Temizleme kuralları
clean:
	rm -rf $(OBJS_DIR)
	echo "$(G)$(NAME) Object files removed! $(NC)"

fclean: clean
	rm -f $(NAME)
	echo "$(G)$(NAME) Library removed! $(NC)"

re: fclean all

# Hedefleri sahte hedefler olarak işaretle
.PHONY: all clean fclean re
