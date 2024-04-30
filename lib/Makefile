# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: muhnal <muhnal@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/26 10:35:11 by muhnal            #+#    #+#              #
#    Updated: 2024/02/26 10:59:23 by muhnal           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

NAME = lib

#FT_PRINTF_DIR = ./ft_printf/
LIBFT_DIR = ./libft/
GNL_DIR = ./gnl/

all: $(NAME)

$(NAME):
#	@$(MAKE) -C $(FT_PRINTF_DIR)
	@$(MAKE) -C $(LIBFT_DIR)
	@$(MAKE) -C $(GNL_DIR)

clean:
#	@$(MAKE) clean -C $(FT_PRINTF_DIR)
	@$(MAKE) clean -C $(LIBFT_DIR)
	@$(MAKE) clean -C $(GNL_DIR)

fclean:
#	@$(MAKE) fclean -C $(FT_PRINTF_DIR)
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@$(MAKE) fclean -C $(GNL_DIR)

re: fclean all

.PHONY: all, clean, fclean, re
