
NAME = fdf

CC = gcc

CFLAGS = -Wall -Wextra -Werror -O3

GL = -lm -lmlx -framework OpenGL -framework AppKit

INCLUDES = fdf.h

SRCS =      fdf_help.c \
        	ft_atoi_base.c \
        	ft_isdigit.c \
        	set_cord.c \
        	keyboard.c \
        	calculation.c \
        	draw_line.c \
        	points_cord.c \
        	fdf.c

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME) : $(OBJ) 
	$(CC) $(CFLAGS) $(GL) $(OBJ) -o $(NAME)

%.o: %.c $(INCLUDES) 
	$(CC) $(CFLAGS) -c -o $@ $< -I $(INCLUDES)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
