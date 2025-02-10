NAME	=	autocrop

CC		=	cc
CFLAGS	=	-O3 -g

LFTDIR	=	./libft
LIBFT	=	$(LFTDIR)/libft.a

HEADERS =	./crop.h \
			../config.h

SRCDIR	=	./src
SRC		=	$(SRCDIR)/main.c \
			$(SRCDIR)/autoCrop/0_autoCrop.c \
			$(SRCDIR)/autoCrop/1_readCsv.c \
			$(SRCDIR)/autoCrop/2_objectDetection.c \
			$(SRCDIR)/autoCrop/3_exportCrops.c \
			$(SRCDIR)/centralCrop/0_centralCrop.c \

OBJDIR	=	./obj
OBJ		=	$(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: $(OBJDIR) $(NAME)

$(LIBFT):
	@make -C $(LFTDIR) all -s

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $< -I .

$(NAME): $(LIBFT) $(OBJDIR) $(OBJ)
	@echo "  make: compiling $(NAME)..."
	@$(CC) $(OBJ) $(LIBFT) -o $(NAME) -lm

clean:
	@echo "  make: cleaning..."
	@rm -f $(OBJ)
	@make -C $(LFTDIR) clean -s

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(OBJDIR)
	@rm -f $(LIBFT)

re: clean all

.PHONY: all clean fclean re