
CC= cc -Wall -Wextra -Werror
NAME=pipex
NAME_BONUS=pipex_bonus

COMMON_SRCS=ft_char_print_utils.c ft_command_.c ft_command.c ft_get_next_line.c \
ft_number_print_utils.c ft_pipe.c ft_pipex_.c ft_pipex.c ft_printf.c ft_utilities.c \
ft_string_builder_.c ft_string_builder.c ft_string_utils.c ft_utilities_.c

INCLUDES=ft_command.h ft_get_next_line.h ft_pipe.h ft_pipex.h ft_printf.h \
ft_string_builder.h ft_string_utils.h ft_utilities.h

MANADATORY_SRCS=$(COMMON_SRCS) ft_pipex_main.c
BONUS_SRCS=$(COMMON_SRCS) ft_pipex_bonus.c

MANADATORY_OBJS=$(MANADATORY_SRCS:.c=.o)
BONUS_OBJS=$(BONUS_SRCS:.c=.o)

$(NAME): $(MANADATORY_OBJS)
	$(CC) $^ -o $@

%.o: %.c $(INCLUDES)
	$(CC) -c $< -o $@

all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(BONUS_OBJS)
	$(CC) $^ -o $(NAME)

clean:
	rm -rf $(MANADATORY_OBJS) $(BONUS_OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
