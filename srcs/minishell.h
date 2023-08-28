/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 20:38:43 by edelarbr          #+#    #+#             */
/*   Updated: 2023/08/28 21:27:49 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*PARSING*/

// - creer une liste chainee de t_split

// - tokenizer les args de t_split

// - creer la liste chainee triple types de nodes

/*---------------------------REGLES DE COLLABORATION--------------------------*/

// ! mettre les fichiers de fonctions générales dans srcs/libs/

// ! mettre les fichiers de fonctions spécifiques au focntionnement de minishell
// ! dans srcs/utils/

/*-----------------------TRUCS A CHECKER AVANT LA FIN-------------------------*/

// - est-ce que mettre tous les whitespaces dans comme separateur dans split

// - free entre chaque ligne de commande recue

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

// typedef struct s_pipe
// {
// 	int						pipe_fd[2];
// 	struct s_cmd			*pipe_in;
// 	struct s_cmd			*pipe_out;
// }							t_pipe;

// typedef struct s_file
// {
// 	int						fd;
// 	char					*file_name;
// 	int						fd_in;
// 	int						fd_out;
// }							t_file;
// typedef struct s_cmd
// {
// 	char					**cmd;
// 	struct s_pipe			in_pipe;
// 	struct s_file			in_file;
// 	struct s_pipe			out_pipe;
// 	struct s_file			out_file;
// }							t_cmd;

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
}					t_split;

typedef struct s_shell_memory
{
	char			**env;
	char			*input_line;
	char			**cmd_line_split;
	t_list			*first;
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

/* UTILS */
void				input_gestion(t_shell_memory *data);
char				**ft_split_white_space(char const *s);
char				**ft_split_keep_char(const char *s1, char c);
t_split				*create_split_node(char *arg);
void				data_init(t_shell_memory *data);
void				lst_separate_operator(t_shell_memory *data, char operator);

#endif
