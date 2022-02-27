NAME =		minishell

SRCS = 		./srcs/parser/input.c \
			./srcs/parser/wildcard/wilcard_utils_2.c \
			./srcs/parser/wildcard/wildcard.c \
			./srcs/parser/wildcard/wildcar_utils.c \
			./srcs/parser/heredoc.c \
			./srcs/parser/output.c \
			./srcs/parser/parsing.c \
			./srcs/parser/args.c \
			./srcs/env/env.c \
			./srcs/memory/singleton.c \
			./srcs/main.c \
			./srcs/builtins/exec_cd.c \
			./srcs/builtins/exec_exit.c \
			./srcs/builtins/exec_pwd.c \
			./srcs/builtins/exec_echo.c \
			./srcs/builtins/exec_env.c \
			./srcs/builtins/export/exec_export.c \
			./srcs/builtins/export/exec_export2.c \
			./srcs/builtins/export/exec_export3.c \
			./srcs/builtins/export/exec_export4.c \
			./srcs/builtins/exec_unset.c \
			./srcs/errors/error_msg_2.c \
			./srcs/errors/error_msg.c \
			./srcs/errors/malloc.c \
			./srcs/list_tools/list_lexer_tools.c \
			./srcs/list_tools/list_cmd_tools.c \
			./srcs/list_tools/list_env_tools.c \
			./srcs/lexer/lexer_quotes.c \
			./srcs/lexer/lexer.c \
			./srcs/lexer/token_utils_lexer.c \
			./srcs/lexer/token_utils_lexer_2.c \
			./srcs/lexer/lexer_checker.c \
			./srcs/signals/signals.c \
			./srcs/io/switch_io.c \
			./srcs/io/pipes.c \
			./srcs/io/close_files.c \
			./srcs/prompt/prompt.c \
			./srcs/exec/wait_pid.c \
			./srcs/exec/exec.c \
			./srcs/exec/exec_builtins.c \
			./srcs/trimer/trimer.c


OBJS = ${SRCS:.c=.o}
INCS	=	-I ./includes -I ./libft/includes
LIBC	=	libft/libft.a
CC		=	clang
CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm -rf
SYSTEM	=	${shell uname}

ifeq (${SYSTEM}, Darwin)
_END=$'\x1b[0m
_BOLD=$'\x1b[1m
_UNDER=$'\x1b[4m
_REV=$'\x1b[7m
_GREY=$'\x1b[30m
_RED=$'\x1b[31m
_GREEN=$'\x1b[32m
_YELLOW=$'\x1b[33m
_BLUE=$'\x1b[34m
_PURPLE=$'\x1b[35m
_CYAN=$'\x1b[36m
_WHITE=$'\x1b[37m
endif

ifeq (${SYSTEM}, Linux)
_GREY=	$'\033[30m
_RED=	$'\033[31m
_GREEN=	$'\033[32m
_YELLOW=$'\033[33m
_BLUE=	$'\033[34m
_PURPLE=$'\033[35m
_CYAN=	$'\033[36m
_WHITE=	$'\033[37m
_END= $'\033[37m
endif

.c.o:
			@printf "%-15s ${_YELLOW}${_BOLD}$<${_END}...\n" "Compiling"
			@${CC} ${CFLAGS} ${INCS} -c $< -o $@

all:		${NAME}

${NAME}:	${OBJS}
			@printf "%-15s ${_CYAN}${_BOLD}libft${_END}...\n" "Compiling"
			@${MAKE} -C libft > /dev/null
			@printf "%-15s ${_PURPLE}${_BOLD}${NAME}${_END}...\n" "Compiling"
			@${CC} ${CFLAGS} -lreadline ${INCS} ${OBJS} -o ${NAME} ${LIBC}
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