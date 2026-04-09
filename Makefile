UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
MLX_DIR	= minilibx_opengl
LIBS	= -lmlx ./src/libft/libft.a -framework OpenGL -framework AppKit
else
MLX_DIR	= minilibx_linux
LIBS	= -lmlx ./src/libft/libft.a -lXext -lX11 -lm -lbsd
endif

NAME	= miniRT
NAME_B  = miniRT_bonus
CC		= cc

HEADER	= ./includes
LIBFT_DIR = ./src/libft

CFLAGS	= -Wall -Wextra -Werror -O3
IFLAGS	= -I$(HEADER) -I$(MLX_DIR)
LDFLAGS	= -L$(LIBFT_DIR) -L$(MLX_DIR)

SRCS_M  = src/main.c
SRCS_B  = src/main_bonus.c
SRCS	= src/parser/check_element.c \
		  src/parser/check_range.c \
		  src/parser/free.c \
		  src/parser/ft_atof.c \
		  src/parser/init.c\
		  src/parser/make_env_data.c \
		  src/parser/make_lit_data.c \
		  src/parser/make_obj_data.c \
		  src/parser/parser.c \
		  src/parser/print_function.c \
		  src/parser/setter_getter.c \
		  src/parser/utils.c \
		  src/ui/init_window.c \
		  src/ui/close_handler.c \
		  src/calc/dot_cross.c \
		  src/calc/multi_divid_vector.c \
		  src/calc/plus_minus_vector.c \
		  src/calc/normalize.c \
		  src/calc/distance_vector.c \
		  src/calc/solve_abc.c \
		  src/raytracing/ray_intersections.c \
		  src/raytracing/cylinder.c \
		  src/raytracing/calc_screen_vector.c \
		  src/raytracing/calc_distance_obj.c \
		  src/raytracing/hit_obj_calc.c \
		  src/raytracing/calc_camera_pos.c \
		  src/raytracing/calc_shade.c \
		  src/raytracing/calc_shadow.c \
		  src/raytracing/check_light_pos.c \
		  src/raytracing/check_nearest_obj.c \
		  src/raytracing/clamp_utils.c \
		  src/raytracing/color_utils.c 
OBJS_M  = $(SRCS_M:.c=.o)
OBJS_B  = $(SRCS_B:.c=.o)
OBJS	= $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(NAME): $(OBJS_M) $(OBJS)
	@make -C $(MLX_DIR)
	make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(IFLAGS) $(LDFLAGS) $(OBJS_M) $(OBJS) $(LIBS) -o $(NAME)

all: $(NAME)

bonus: $(NAME_B)

$(NAME_B): $(OBJS_B) $(OBJS)
	@make -C $(MLX_DIR)
	make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(IFLAGS) $(LDFLAGS) $(OBJS_B) $(OBJS) $(LIBS) -o $(NAME_B)

clean:
	@make clean -C $(MLX_DIR)
	make fclean -C $(LIBFT_DIR)
	rm -f $(OBJS_M) $(OBJS_B) $(OBJS)

fclean: clean
	rm -f $(NAME) $(NAME_B)

re: fclean all

.PHONY: all re clean fclean bonus
