# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/22 16:59:43 by edelarbr          #+#    #+#              #
#    Updated: 2023/10/06 01:34:37 by edelarbr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	minishell

# ------------------------------ Sources -----------------------------

SRCS		:=	srcs/others/signals.c \
				srcs/others/free_n_exit.c \
				srcs/others/tuning_memory.c \
				srcs/builtins/ft_unset.c \
				srcs/builtins/ft_env.c \
				srcs/builtins/ft_cd.c \
				srcs/builtins/ft_pwd.c \
				srcs/builtins/ft_echo.c \
				srcs/builtins/ft_exit.c \
				srcs/builtins/ft_export/ft_export.c \
				srcs/builtins/ft_export/ft_export_fork.c \
				srcs/builtins/ft_export/export_utils.c \
				srcs/execution/ft_execve.c \
				srcs/execution/execution.c \
				srcs/execution/close_pipes.c \
				srcs/execution/get_path.c \
				srcs/lib/ft_tablen.c \
				srcs/lib/ft_atoi.c \
				srcs/lib/ft_isenvchar.c \
				srcs/lib/ft_lstclear.c \
				srcs/lib/ft_lstadd_back.c \
				srcs/lib/ft_putstr_fd.c \
				srcs/lib/ft_lstnew.c \
				srcs/lib/ft_strlen.c \
				srcs/lib/ft_lstlast.c \
				srcs/lib/ft_rmchar.c \
				srcs/lib/ft_tabdup.c \
				srcs/lib/ft_strchr.c \
				srcs/lib/ft_lstdel_here.c \
				srcs/lib/ft_strjoin.c \
				srcs/lib/ft_isascii.c \
				srcs/lib/ft_lstfirst.c \
				srcs/lib/ft_there_is_char.c \
				srcs/lib/ft_lstadd_front.c \
				srcs/lib/ft_strrchr.c \
				srcs/lib/ft_tabadd_back.c \
				srcs/lib/ft_memset.c \
				srcs/lib/ft_substr.c \
				srcs/lib/ft_strncmp.c \
				srcs/lib/ft_strtrim.c \
				srcs/lib/ft_calloc.c \
				srcs/lib/ft_lstadd_here.c \
				srcs/lib/ft_strdup.c \
				srcs/lib/ft_split_w_slash.c \
				srcs/lib/ft_iswhitespace.c \
				srcs/lib/ft_itoa.c \
				srcs/lib/ft_strcmp.c \
				srcs/lib/ft_lstdelone.c \
				srcs/lib/ft_str_is_num.c \
				srcs/parsing/is_empty_or_whitespaces.c \
				srcs/parsing/syntax_error.c \
				srcs/parsing/rm_quotes.c \
				srcs/parsing/tokenization.c \
				srcs/parsing/forbiddens_chars.c \
				srcs/parsing/here_doc_gestion.c \
				srcs/parsing/env_variable.c \
				srcs/parsing/env_variable_utils.c \
				srcs/parsing/stake_cmd_args.c \
				srcs/parsing/struct_init.c \
				srcs/parsing/setup_fd.c \
				srcs/parsing/stake_n_open_redirections.c \
				srcs/parsing/stake_n_open_redirections_utils.c \
				srcs/parsing/crazy_split.c \
				srcs/parsing/crazy_split_utils.c \
				srcs/parsing/parser.c \
				srcs/parsing/quotes_gestion.c \
				srcs/parsing/execution_lst.c \
				srcs/minishell.c \
				srcs/temp/print.c \

OBJ_DIR		:=	.objs
OBJS		:=	$(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

# ------------------------------ Flags -------------------------------

BREW		:=	$(shell brew --prefix)
INC_RL		:=	-I $(BREW)/Cellar/readline/8.2.1/include/
LINK_RL		:=	-lreadline -L $(BREW)/Cellar/readline/8.2.1/lib
CC			:=	gcc
FLAGS		:=	-Wall -Wextra -Werror #-g3 -fsanitize=address
RM			:=	rm -rf

$(OBJ_DIR)/%.o :%.c
	@ mkdir -p $(dir $@)
	@ $(CC) $(FLAGS) $(INC_RL) -c $< -o $@

# ------------------------------ Colors ------------------------------

CLR_RMV		:=	\033[0m
RED			:=	\033[1;31m
GREEN		:=	\033[1;32m
YELLOW		:=	\033[1;33m
BLUE		:=	\033[1;34m
CYAN 		:=	\033[1;36m

# ------------------------------ Compilation -------------------------

all:			$(NAME)

$(NAME):		$(OBJS)
				@ echo "$(GREEN)Compilation $(CLR_RMV)of $(YELLOW)$(NAME) $(CLR_RMV)..."
				@ $(CC) $(FLAGS) $(INC_RL) $(LINK_RL) -o $(NAME) $(OBJS)
				@ echo "$(YELLOW)$(NAME) $(GREEN)created $(CLR_RMV)✔️"

# -------------------------------- Rules -----------------------------

clean:
				@ $(RM) $(OBJ_DIR)
				@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"

fclean:			clean
				@ $(RM) $(NAME) $(RM)
				@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"

re:				fclean all

.PHONY:			all bonus clean fclean re
