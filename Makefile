FILES = push_swap init utils ft_perror gc gc_utils operations1 operations2 \
         operations3 validation parser_utils parser_space libft
		 

BONUS_FILES = checker_bonus utils_bonus

NAME = push_swap
AR_NAME = push_swap.a
CHECKER_NAME = checker

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I inc -I $(LIBFT_PATH)
MFLAGS = -s -j16 -C
AR = ar rcs
RM = rm -rf

LIBFT_PATH = lib/libft/
LIBFT = $(LIBFT_PATH)libft.a
CHECKER_PATH = checker_src/
FILES_PATH = .

SRCS = $(addprefix $(FILES_PATH)/, $(addsuffix .c, $(FILES)))
BONUS = $(addprefix $(CHECKER_PATH), $(addsuffix .c, $(BONUS_FILES)))
OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LIBFT)

$(LIBFT):
	make $(MFLAGS) $(LIBFT_PATH)

$(AR_NAME): $(LIBFT) $(OBJS)
	$(AR) $(AR_NAME) $(OBJS)

bonus: $(LIBFT) $(AR_NAME) $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(AR_NAME) $(LIBFT) -o $(CHECKER_NAME)

all: $(NAME)

clean:
	$(RM) $(OBJS) $(BONUS_OBJS)

fclean: clean libclean
	$(RM) $(NAME)
	$(RM) $(AR_NAME)
	$(RM) $(CHECKER_NAME)

libclean:
	make $(MFLAGS) $(LIBFT_PATH) fclean

re: fclean all

push:
	git add .
	git commit -m "commit"
	git push

compile_libs:
	make -sC lib/libft
	make clean -sC lib/libft

get_libs:
	git submodule update --init --recursive --remote

run: re
	./$(NAME) 5 1 4 3 2 0 

.PHONY: all clean fclean re bonus push compile_libs update run