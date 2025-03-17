EDITORFILES=refresh.c draw.c draw_selection.c
PROCESSFILES=input.c arrow.c insert.c delete.c mouse.c command.c delete_selection.c
SHORTCUTFILES=shortcut.c shortcut_2.c
UTILSFILES=utils_2.c buffer_utils.c utils.c utils_3.c cpy_utils.c paste_utils.c
SRCFILES=main.c error.c file.c termios.c init.c buffer.c update.c

SHORTCUTDIR=shortcut
OUTPUTDIR=output
BUFFERDIR=buffer
WINDOWDIR=window
UTILSDIR=utils
PROCESSDIR=process
EDITORDIR=editor
SRCDIR=src
FILES=$(addprefix $(SRCDIR)/, $(SRCFILES))\
	$(addprefix $(SRCDIR)/$(PROCESSDIR)/, $(PROCESSFILES))\
	$(addprefix $(SRCDIR)/$(PROCESSDIR)/$(SHORTCUTDIR)/, $(SHORTCUTFILES))\
	$(addprefix $(SRCDIR)/$(UTILSDIR)/, $(UTILSFILES))\
	$(addprefix $(SRCDIR)/$(EDITORDIR)/, $(EDITORFILES))
OBJDIR=.obj
OBJ=$(addprefix $(OBJDIR)/, $(FILES:.c=.o))
CC=cc
FLAGS= -Wextra -Wall -g3 #-Werror
INC=editor.h
NAME=editor
PATHLIB=libft/
LIBFT = $(PATHLIB)libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) -o $(NAME) $(LIBFT)
$(LIBFT): libft

$(LIBFT):
	$(MAKE) --no-print-directory -C $(PATHLIB)

$(OBJDIR)/%.o: %.c $(INC) Makefile $(OBJDIR)
	$(CC) $(FLAGS) -I$(OBJDIR) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)
	mkdir -p $(OBJDIR)/$(SRCDIR)
	mkdir -p $(OBJDIR)/$(SRCDIR)/$(UTILSDIR)
	mkdir -p $(OBJDIR)/$(SRCDIR)/$(PROCESSDIR)
	mkdir -p $(OBJDIR)/$(SRCDIR)/$(PROCESSDIR)/$(SHORTCUTDIR)
	mkdir -p $(OBJDIR)/$(SRCDIR)/$(EDITORDIR)

clean:
	rm -rf $(OBJDIR)

lclean:
	$(MAKE) --no-print-directory fclean -C $(PATHLIB)

fclean: lclean clean
	rm -f $(NAME)

re : fclean all

.PHONY : fclean clean re all lclean libft
