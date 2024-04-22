NAME		  := cubed
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
				./include/libft/ \
				./include/MLX42/include/MLX42 \
				$(GLFW)/include

LIB			:= ft m mlx42
# LIB_FT		:= include/libft/libft.a
LIB_MLX		:= include/MLX42/build/libmlx42.a

BUILD_DIR	:= .build

# ---------------------------------------------------------------------------- #
#                                 source files                                 #
# ---------------------------------------------------------------------------- #

VPATH		:= src/

SRC			:= main.c

SRCS		:= $(SRC)

# ---------------------------------------------------------------------------- #
#                             compilation arguments                            #
# ---------------------------------------------------------------------------- #

OBJS		:= $(addprefix $(BUILD_DIR)/, $(SRCS:%.c=%.o))
DEPS		:= $(OBJS:.o=.d)

CC			:= clang
CFLAGS		?= -g3 -Wall -Wextra -Werror #-Wpedantic
FRAMEWORKS	:= $(addprefix -framework, $(IOKit) $(Cocoa) $(OpenGL))
CPPFLAGS	:= $(addprefix -I,$(INCS)) -MMD -MP
LDFLAGS		:= $(addprefix -L,$(GLFW))
LDLIB		:= $(addprefix -l,"glfw")

MAKEFLAGS	+= --no-print-directory --silent

DONE		= printf "\033[0;32m\xE2\x9C\x93\033[0m "
DONE_NL		= printf "\033[0;32m\xE2\x9C\x93\n\033[0m"

WIDTH = 1000
HEIGHT = 1000

# ---------------------------------------------------------------------------- #
#                             building the program                             #
# ---------------------------------------------------------------------------- #

all: update $(NAME)

# $(LIB_FT):
# 	$(MAKE) -C $(@D) -B

$(LIB_MLX):
	cd include/MLX42 && cmake -B build
	cmake --build $(@D) -j4

$(NAME): $(OBJS) $(LIB_MLX)
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

clean: $(MAKE)
	$(info Cleaning...)
	make -C $(dir $(LIB_FT)) clean; rm -rf .build; $(DONE_NL)

fclean: clean
	rm -fv $(LIB_FT); rm -fv $(LIB_MLX); rm -fv $(NAME);

# update:
# 	git submodule update --init --recursive

re:
	$(MAKE) fclean all

run: all
	./$(NAME) shift

norme: $(clear)
	-norminette src/ | grep Error; norminette include/*.h | grep Error; norminette include/libft | grep Error

.PHONY: run update re clean fclean
-include $(DEPS)