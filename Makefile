NAME	=	sobel_filter
CC		=	gcc
CFLAGS	=	-Wall -Wextra -I./inc/ -g3 -lpthread

SRCDIR	=	src
BUILDDIR=	build

SRC		=	main.c \
			print_help.c \
			get_image.c \
			sobel.c \
			greyscale.c \
			save.c \

SRCS	=	$(addprefix $(SRCDIR)/, $(SRC))
OBJ		=	$(addprefix $(BUILDDIR)/, $(SRC:.c=.o))

vpath %.c	$(SRCDIR):$(SRCDIR)/error_h:$(SRCDIR)/image_h:$(SRCDIR)/parser:$(SRCDIR)/utils

all: $(NAME)

$(NAME):	$(OBJ)
		$(CC) $(CFLAGS) $^ -o $@ $(LIB)

$(BUILDDIR)/%.o: %.c
		mkdir -p $(dir $@)
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re: fclean all