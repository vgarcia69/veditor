# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: v <v@student.42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/05 16:28:26 by vgarcia           #+#    #+#              #
#    Updated: 2025/03/15 14:53:32 by v                ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = ./ft_isalpha.c\
		./ft_isdigit.c\
		./ft_isalnum.c\
		./ft_isascii.c\
		./ft_isprint.c\
		./ft_strlen.c\
		./ft_memset.c\
		./ft_bzero.c\
		./ft_memcpy.c\
		./ft_memmove.c\
		./ft_strlcpy.c\
		./ft_strlcat.c\
		./ft_toupper.c\
		./ft_tolower.c\
		./ft_strchr.c\
		./ft_strrchr.c\
		./ft_strncmp.c\
		./ft_memchr.c\
		./ft_memcmp.c\
		./ft_strnstr.c\
		./ft_atoi.c\
		./ft_calloc.c\
		./ft_strdup.c\
		./ft_substr.c\
		./ft_strjoin.c\
		./ft_strtrim.c\
		./ft_split.c\
		./ft_itoa.c\
		./ft_strmapi.c\
		./ft_striteri.c\
		./ft_putchar_fd.c\
		./ft_putstr_fd.c\
		./ft_putendl_fd.c\
		./ft_putnbr_fd.c\
		./ft_printf_utils.c\
		./ft_printf_writechars.c\
		./ft_printf_writenbrs.c\
		./ft_printf_fd.c\
		./ft_strcpy.c\
		./ft_strinsert.c\
		./ft_maths.c\
		./ft_revptr.c\
		./get_next_line.c
SRC_BONUS = ./ft_lstadd_back.c\
		./ft_lstadd_front.c\
		./ft_lstclear.c\
		./ft_lstdelone.c\
		./ft_lstlast.c\
		./ft_lstnew.c\
		./ft_lstsize.c\
		./ft_lstiter.c\
		./ft_lstmap.c

OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)
NAME = libft.a

all: $(NAME)

$(NAME): $(OBJ)
		@ar rcs $(NAME) $(OBJ)
		@echo "Libft Compiled !"

bonus : $(NAME) .bonus

.bonus: $(OBJ) $(OBJ_BONUS)
		@ar rcs $(NAME) $(OBJ) $(OBJ_BONUS)
		@touch .bonus
		@echo "Libft bonus created"

%.o: %.c libft.h Makefile
		@$(CC) $(CFLAGS) -I . -c $< -o $@
		@echo "Compiling $<"

clean :
		@rm -f $(OBJ) $(OBJ_BONUS) .bonus

fclean : clean
		@rm -f $(NAME)
		@echo "Libft cleaned"

re : fclean all

.PHONY : re fclean clean all bonus
