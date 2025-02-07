NAME	=	crop

CC		=	cc
CFLAGS	=	-O3 -g

LFTDIR	=	./libft
LIBFT	=	$(LFTDIR)/libft.a

HEADERS =	./crop.h \
			./config.h

SRCDIR	=	./src
SRC		=	$(SRCDIR)/main.c \
			$(SRCDIR)/exportCrops.c \
			$(SRCDIR)/objectReport.c \
			$(SRCDIR)/readCsv.c

$(info SRC = $(SRC))

OBJDIR	=	./obj
OBJ		=	$(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: $(OBJDIR) $(NAME)

$(LIBFT):
	make -C $(LFTDIR) all -s

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(LIBFT) $(OBJDIR) $(OBJ)
	$(CC) $(OBJ) $(LIBFT) -o $(NAME) -lm

clean:
	rm -f $(OBJ)
	make -C $(LFTDIR) clean -s

fclean: clean
	rm -f $(NAME)
	rm -rf $(OBJDIR)
	rm -f $(LIBFT)

re: clean all

.PHONY: all clean fclean re