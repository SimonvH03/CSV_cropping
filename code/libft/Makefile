NAME	=	libft.a

CFLAGS	=	-Wall -Werror -Wextra -O3
CFLAGS	+=	-g

SRC		=	ft_arrclear.c \
			ft_atoi.c \
			ft_bzero.c \
			ft_free_null.c \
			ft_get_next_line.c \
			ft_intlen.c \
			ft_itoa.c \
			ft_putstr_fd.c \
			ft_split.c \
			ft_strchr_null.c \
			ft_strchr.c \
			ft_strdup_d.c \
			ft_strjoin.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen_null.c \
			ft_strlen.c \
			ft_strncmp.c

OBJDIR	=	./obj
OBJ		=	$(SRC:%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.c $(OBJDIR)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
