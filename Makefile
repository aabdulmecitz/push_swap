FILES = push_swap init utils error operations sort_stack sort_small \
         init_a_to_b init_b_to_a move_a_to_b move_b_to_a sort_algorithm \
         check_sorted free operations2 operations3 utils2 lis

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
FILES_PATH = src

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

update:
	git submodule update --init --recursive --remote

run: re
	./$(NAME) <sth>

.PHONY: all clean fclean re bonus push compile_libs update run