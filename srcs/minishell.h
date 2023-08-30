/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 20:38:43 by edelarbr          #+#    #+#             */
/*   Updated: 2023/08/31 01:23:40 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*PARSING*/

/*---------------------------------PROTECTION---------------------------------*/

#ifndef MINISHELL_H
# define MINISHELL_H

/*---------------------------------LIBRAIRIES---------------------------------*/

# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

/*----------------------------------DEFINES-----------------------------------*/

# define TRUE 1
# define FALSE 0
# define DOUBLES 2
# define SIMPLE 1

/*----------------------------------STRUCTS-----------------------------------*/

enum				e_token
{
	PIPE,
	COMMAND,
	REDIR_IN,
	REDIR_APPEND,
	REDIR_OUT,
	FILEE,
};

typedef struct s_list
{
	void			*content;

	struct s_list	*next;
	struct s_list	*prev;
}					t_list;

typedef struct s_split
{
	enum e_token	token;
	char			*arg;

	char			**cmd;
	int				pipe_fd[2];
}					t_split;

typedef struct s_shell_memory
{
	char			**env;
	char			*input_line;
	char			**cmd_line_split;
	t_list			*parsing_lst;
	t_list			*working_node;
}					t_shell_memory;

/*----------------------------------FUNCTIONS---------------------------------*/

/* TEMP */
void				print_t_split(t_list *lst);
void				print_tab(char **tab);

/* LIB */
int					ft_iswhitespace(char c);
int					ft_isascii(int c);
int					ft_strlen(const char *str);
char				*ft_rmchar(char *str, char c);
char				*ft_strrchr(const char *s, int c);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strtrim(const char *s, const char *set);
char				*ft_strchr(const char *s, int c);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstadd_front(t_list **lst, t_list *new);
t_list				*ft_lstnew(void *content);
void				ft_lstadd_here(t_list **lst, t_list *new);
void				ft_lstdel_here(t_list **lst,
						t_list *node_to_delete);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strjoin_free_s1(char *s1, char *s2);
void				*ft_calloc(size_t size, size_t count);
int					ft_isenvchar(int c);
char				**ft_tabadd_back(char **tab, char *new_str);

/* UTILS */
void				input_gestion(t_shell_memory *data);
char				**ft_split_white_space(char const *s);
char				**ft_split_keep_char(const char *s1, char c);
t_split				*create_split_node(char *arg);
void				data_init(t_shell_memory *data);
void				lst_separate_operator(t_shell_memory *data, char operator);
void				env_var_gestion(t_shell_memory *data, t_list *lst);
void				stake_cmd_args(t_shell_memory *data, t_list *lst);

#endif
