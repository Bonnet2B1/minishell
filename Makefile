# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/22 16:59:43 by edelarbr          #+#    #+#              #
#    Updated: 2023/09/24 19:17:53 by edelarbr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	minishell

# ------------------------------ Sources -----------------------------

# SRCS		:=	srcs/*.c \
# 				srcs/*/*.c \

SRCS		:=	srcs/temp/print.c \
				srcs/signals/signals.c \
				srcs/builtins/ft_unset.c \
				srcs/builtins/ft_env.c \
				srcs/execution/ft_execve.c \
				srcs/execution/execution.c \
				srcs/execution/close_pipes.c \
				srcs/execution/get_path.c \
				srcs/lib/ft_isenvchar.c \
				srcs/lib/ft_lstadd_back.c \
				srcs/lib/ft_putstr_fd.c \
				srcs/lib/ft_lstnew.c \
				srcs/lib/ft_strjoin_free_s1.c \
				srcs/lib/ft_strlen.c \
				srcs/lib/ft_lstlast.c \
				srcs/lib/ft_rmchar.c \
				srcs/lib/ft_strjoin_freeall.c \
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
				srcs/lib/freetab.c \
				srcs/lib/ft_strcmp.c \
				srcs/parsing/here_doc_gestion.c \
				srcs/parsing/env_variable.c \
				srcs/parsing/stake_cmd_args.c \
				srcs/parsing/struct_init.c \
				srcs/parsing/setup_fd.c \
				srcs/parsing/stake_n_open_redirections.c \
				srcs/parsing/rm_quotes.c \
				srcs/parsing/crazy_split.c \
				srcs/parsing/parser.c \
				srcs/parsing/quotes_gestion.c \
				srcs/parsing/free_structs.c \
				srcs/parsing/execution_lst.c \
				srcs/minishell.c \

OBJS		:=	$(SRCS:.c=.o)

# ------------------------------ Flags -------------------------------

READLINE	:=	$(shell brew --prefix readline)
INC_RL		:= -I /opt/homebrew/Cellar/readline/8.2.1/include/
LINK_RL		:= -lreadline -L /opt/homebrew/Cellar/readline/8.2.1/lib
CC			:=	gcc
FLAGS		:=	-Wall -Wextra -Werror -g3 -fsanitize=address

.c.o:
	@ $(CC) $(FLAGS) $(INC_RL) -c $< -o $(<:.c=.o)

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
				@ $(RM) $(OBJS)
				@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"

fclean:			clean
				@ $(RM) $(NAME) $(RM)
				@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"

re:				fclean all

.PHONY:			all bonus clean fclean re
