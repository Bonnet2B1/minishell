/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 20:38:43 by edelarbr          #+#    #+#             */
/*   Updated: 2023/10/07 22:19:25 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*=============================== PROTECTIONS ================================*/

#ifndef MINISHELL_H
# define MINISHELL_H

/*================================ LIBRAIRIES ================================*/

# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
# include <fcntl.h>
# include <dirent.h>

/*================================= DEFINES ==================================*/

# define TRUE 1
# define FALSE 0
# define INPIPE 1
# define OUTPIPE 0
# define ON 1
# define OFF 0
# define DEFAULT 2
# define SIG_HERE_DOC 3

/*================================= STRUCTS ==================================*/

enum				e_token
{
	NONE,
	PIPE,
	COMMAND,
	REDIR_IN,
	HERE_DOC,
	REDIR_OUT,
	REDIR_APPEND,
	FILEE,
};

typedef struct s_list
{
	void			*content;

	struct s_list	*next;
	struct s_list	*prev;
}					t_list;

typedef struct s_parsing
{
	int				to_del;
	enum e_token	token;
	char			*arg;

	char			**cmd;
	int				pipe_fd[2];
	int				file_fd;
	int				open_error;
}					t_parsing;

typedef struct s_execution
{
	int				execute;
	int				open_error;
	char			**cmd;
	t_parsing		*in_struct;
	t_parsing		*out_struct;
	int				in_fd;
	int				out_fd;
	pid_t			pid;
}					t_exec;

typedef struct s_shell_memory
{
	int				exit_code;
	char			**env;
	char			**input_line;
	char			**cmd_line_split;
	t_list			*parsing_lst;
	t_list			*exec_lst;
	int				fatal_error;
	char			**paths;
	char			*cmd_path;
	t_list			*malloc_chain;
}					t_shell_memory;

/*================================ FUNCTIONS =================================*/

/* TEMP */
void				print_t_parsing(t_list *lst);
void				print_lst_size(t_list *lst);
void				print_t_exec(t_list *lst);
void				print_tab(char **tab);

/* LIB */
int					ft_str_is_num(char *str);
int					ft_tablen(char **tab);
int					ft_atoi(const char *str);
void				tab_print(char **tab);
int					ft_there_is_char(char *str, char c);
int					ft_iswhitespace(char c);
int					ft_isascii(int c);
int					ft_strlen(const char *str);
char				*ft_rmchar(t_shell_memory *data, char *str, char c);
char				*ft_strrchr(const char *s, int c);
char				*ft_substr(t_shell_memory *data, char const *s,
						unsigned int start, size_t len);
char				*ft_strtrim(t_shell_memory *data,
						const char *s, const char *set);
char				*ft_strchr(const char *s, int c);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstadd_front(t_list **lst, t_list *new);
t_list				*ft_lstnew(t_shell_memory *data, void *content);
void				ft_lstadd_here(t_list **lst, t_list *new);
void				ft_lstdel_here(t_list **first,
						t_list *node_to_delete, void (*del)(void*));
void				ft_lstclear(t_list **lst, void (*del)(void *));
char				*ft_strjoin(t_shell_memory *data,
						char const *s1, char const *s2);
void				*ft_calloc(t_shell_memory *data, size_t size, size_t count);
int					ft_isenvchar(int c);
char				**ft_tabadd_back(t_shell_memory *data,
						char **tab, char *new_str);
t_list				*ft_lstfirst(t_list *lst);
char				*ft_strdup(t_shell_memory *data, const char *src);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
char				**ft_tabdup(t_shell_memory *data, char **tab);
char				**ft_split_w_slash(t_shell_memory *data,
						const char *s, char c);
void				*ft_memset(void *memory, int c, size_t len);
char				*ft_itoa(t_shell_memory *data, int n);
void				ft_lstdelone(t_list *lst, void (*del)(void *));

/* PARSING */
int					syntax_error(t_shell_memory *data, t_list *parsing_lst);
int					is_empty_or_whitespaces(char *str);
void				epure_lst(t_list **lst);
t_exec				*create_execution_node(t_shell_memory *data);
void				setup_execution_lst(t_shell_memory *data,
						t_list *parsing_lst);
int					parsing(t_shell_memory *data);
int					quotes_gestion(t_shell_memory *data, char **input_line);
void				crazy_split(t_shell_memory *data, char **line);
int					ft_isoperator(char c);
int					take_quote(char **line, int len);
int					take_operator(char **line, int len, char operator);
int					get_len(char **line, int len);
int					get_start(char **line, int start);
t_parsing			*create_parsing_node(t_shell_memory *data, char *arg);
void				data_init(t_shell_memory *data);
void				env_var_gestion(t_shell_memory *data, char **line);
int					there_is_a_env_var(char **line);
int					there_is_exitcode(char **line);
int					env_var_len(char **line);
char				**take_before(t_shell_memory *data, char **line);
char				**take_var(t_shell_memory *data, char **line);
void				stack_cmd_args(t_shell_memory *data, t_list *lst);
void				stake_n_open_files(t_shell_memory *data, t_list *lst);
void				redir_error(t_shell_memory *data, t_list *lst);
void				stake_redir_in(t_shell_memory *data, t_list *lst);
void				stake_redir_out(t_shell_memory *data, t_list *lst);
void				stake_redir_append(t_shell_memory *data, t_list *lst);
void				setup_fd(t_shell_memory *data, t_list *exec_lst);
void				print_input_line(char **input_line);
void				rm_quotes(t_shell_memory *data, t_list *parsing_lst);
int					here_doc_gestion(t_shell_memory *data, t_list *parsing_lst);
void				tokenization(t_list *lst);
int					forbiddens_chars(t_shell_memory *data, char **input_line);

/* EXECUTION */
void				execution(t_shell_memory *data);
char				**get_paths(t_shell_memory *data, char **env);
void				ft_execve(t_shell_memory *data, char **cmd);
void				close_pipes(t_list *parsing_lst);
char				*find_cmd_path(t_shell_memory *data, char *cmd);
int					find(t_shell_memory *data, char *find, int len);
int					need_to_exec(t_shell_memory *data, char *cmd_name);
int					builtins_no_fork_or_fork(t_shell_memory *data, t_list *node,
						char **cmd);

/* BUILTINS */
int					ft_unset(t_shell_memory *data, t_list *node, char **cmd);
void				ft_env(t_shell_memory *data, char **cmd, char **env);
void				ft_pwd(t_shell_memory *data);
int					ft_cd(t_shell_memory *data, char **args);
void				ft_echo(t_shell_memory *data, char **args);
int					ft_exit(t_shell_memory *data, char **cmd);
int					ft_export(t_shell_memory *data, char **args);
int					ft_export_fork(t_shell_memory *data);
int					is_letter(int c);
int					ft_srch(char *s);
char				*rtn_arg(t_shell_memory *data, char *str);
void				swap_str(char **s1, char **s2);

/* 0THERS */
void				ft_signal(int i);
void				free_n_exit(t_shell_memory *data, int exit_code);
void				*calloc_tuning(t_list **lst, size_t size);
void				free_tuning(t_list **lst);
void				p_err(char *obj1, char *obj2, char *error);

#endif
