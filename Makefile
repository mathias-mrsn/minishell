NAME =		minishell

#			MAIN
SRCS = 		srcs/main.c \
			
#			PARSING
SRCS +=		srcs/parsing/trim_quotes.c \
			srcs/parsing/trim_quotes_utils.c \
			srcs/parsing/delete_quotes.c \
			srcs/parsing/split_cmd.c \
			srcs/parsing/mini_split.c \
			srcs/parsing/split_pip.c \
			srcs/parsing/parsing_pip.c \

#			MEMORY
SRCS +=		srcs/memory/s_init.c \

OBJS = ${SRCS:.c=.o}
INCS	=	-I ./includes -I ./libft/includes
LIBC	=	libft/libft.a
CC		=	clang
CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm -rf

_END=$'\x1b[0m
_BOLD=$'\x1b[1m
_UNDER=$'\x1b[4m
_REV=$'\x1b[7m

# Colors
_GREY=$'\x1b[30m
_RED=$'\x1b[31m
_GREEN=$'\x1b[32m
_YELLOW=$'\x1b[33m
_BLUE=$'\x1b[34m
_PURPLE=$'\x1b[35m
_CYAN=$'\x1b[36m
_WHITE=$'\x1b[37m

.c.o:
			@printf "%-15s ${_YELLOW}${_BOLD}$<${_END}...\n" "Compiling"
			@${CC} ${CFLAGS} ${INCS} -c $< -o $@

all:		${NAME}

${NAME}:	${OBJS}
			@printf "%-15s ${_CYAN}${_BOLD}libft${_END}...\n" "Compiling"
			@${MAKE} -C libft > /dev/null
			@printf "%-15s ${_PURPLE}${_BOLD}${NAME}${_END}...\n" "Compiling"
			@${CC} ${CFLAGS} -fsanitize=address -g3 -lreadline ${INCS} ${OBJS} -o ${NAME} ${LIBC}
			@printf "\n${_GREEN}${_BOLD}Compilation done !${_END}\n"

clean:
			@printf "%-15s ${_RED}${_BOLD}libft binary files${_END}...\n" "Deleting"
			@${MAKE} -C libft clean > /dev/null
			@printf "%-15s ${_RED}${_BOLD}${NAME} binary files${_END}...\n" "Deleting"
			@${RM} ${OBJS}

fclean:		clean
			@printf "%-15s ${_RED}${_BOLD}libft librairy${_END}...\n" "Deleting"
			@${MAKE} -C libft fclean > /dev/null
			@printf "%-15s ${_RED}${_BOLD}${NAME}${_END}...\n" "Deleting"
			@${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re