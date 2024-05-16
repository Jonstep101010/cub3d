NAME		  := cub3D
.DEFAULT_GOAL := all

# ---------------------------- handle architecture --------------------------- #

ARCH = $(shell uname -m)
ifeq ($(ARCH), arm64)
	GLFW = /opt/homebrew/Cellar/glfw/3.4/lib
else ifeq ($(ARCH), i386 | x86_64)
	GLFW = /Users/$(USER)/.brew/Cellar/glfw/3.3.8/
endif

# --------------------------------- includes --------------------------------- #

INCS		= ./include \
				./libs/libft/ \
				./libs/gnl/ \
				./libs/utils/include \
				./libs/MLX42/include/MLX42/ \
				$(GLFW)/include

LIB			:= ft utils gnl m mlx42
LIB_MLX		:= libs/MLX42/build/libmlx42.a

BUILD_DIR	:= .build

# ---------------------------------------------------------------------------- #
#                                 source files                                 #
# ---------------------------------------------------------------------------- #

VPATH		:= src/:src/dda_ray:src/input:src/input/map:src/input/textures:src/utils

SRC			:= main.c
SRC_DDA		:= dda_raycast.c draw_map.c rotate.c move.c draw_calc.c draw_fc.c
SRC_INPUT	:= parse_file.c parse_fc_color.c parse_non_map.c
SRC_INPUT_MAP	:= parse_map.c player.c checks_basic.c check_walls.c build_map_lines.c
SRC_INPUT_TEX	:= parse_textures.c tex_utils.c
SRC_UTILS	:= free_data.c key_hooks.c

SRCS		:= $(SRC) $(SRC_DDA) $(SRC_INPUT) $(SRC_INPUT_MAP) $(SRC_INPUT_TEX) $(SRC_UTILS)

# ---------------------------------------------------------------------------- #
#                             compilation arguments                            #
# ---------------------------------------------------------------------------- #

OBJS		:= $(addprefix $(BUILD_DIR)/, $(SRCS:%.c=%.o))
DEPS		:= $(OBJS:.o=.d)

CC			:= cc
CFLAGS		?= -g3 -Wall -Wextra -Werror
FRAMEWORKS	:= $(addprefix -framework, $(IOKit) $(Cocoa) $(OpenGL))
CPPFLAGS	:= $(addprefix -I,$(INCS)) -MMD -MP
LDFLAGS		:= $(addprefix -L,$(GLFW) "libs/gnl" "libs/libft" "libs/utils")
LDLIB		:= $(addprefix -l,"glfw" "gnl" "ft" "utils" "m")

MAKEFLAGS	+= --no-print-directory --silent

DONE		= printf "\033[0;32m\xE2\x9C\x93\033[0m "
DONE_NL		= printf "\033[0;32m\xE2\x9C\x93\n\033[0m"

WIDTH = 1000
HEIGHT = 1000

# ---------------------------------------------------------------------------- #
#                             building the program                             #
# ---------------------------------------------------------------------------- #

update:
	git submodule update --init --recursive
	make -C libs/libft; make -C libs/gnl; make -C libs/utils

all: update $(NAME)

$(LIB_MLX):
	cd libs/MLX42 && cmake -B build
	cmake --build $(@D) -j4

$(NAME): $(OBJS) $(LIB_MLX) $(LIBS)
	$(info creating $(NAME) executable)
	$(CC) $(CFLAGS) $(OBJS) -D WIDTH=$(WIDTH) -D HEIGHT=$(HEIGHT) \
	$(LIB_MLX) $(CPPFLAGS) $(LDLIB) $(LDFLAGS) $(FRAMEWORKS) -pthread -o $(NAME)
	$(DONE_NL)

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $< && $(DONE)
	echo $(notdir $<)

$(BUILD_DIR):
	mkdir -p .build

# ---------------------------------------------------------------------------- #
#                                     rules                                    #
# ---------------------------------------------------------------------------- #

clean:
	$(info Cleaning...)
	make -C libs/libft clean; make -C libs/gnl clean; make -C libs/utils clean; rm -rf $(BUILD_DIR)
	rm -rf libs/MLX42/build; $(DONE_NL)

fclean: clean
	make -C libs/libft fclean; make -C libs/gnl fclean; make -C libs/utils fclean;
	rm -fv $(LIB_MLX); rm -fv $(NAME);

re:
	$(MAKE) fclean all

.PHONY: run update re clean fclean