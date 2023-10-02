/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 20:38:43 by edelarbr          #+#    #+#             */
/*   Updated: 2023/10/02 18:28:58 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*================================ BUGS/CRASH ================================*/

// ! crash
// @nevaspid

// @Bonnet2B1
// minishell-3.2$ rm outfile

// - bug
// @nevaspid
// echo -nnnn -n -nnn -nm fdsa devrait donner "-nm fsda"
// print "exit\n" quand ctrl + D
// minishell-3.2$ cd gjnuesoif
// minishell-3.2$ cd ../minishell/correction.pdf

// @Bonnet2B1
// minishell-3.2$ cat ""

// ? trus à gerer si on a vraaaaaaaiment le temps
// @nevaspid
// Essayez ctrI-C après avoir lancé une commande bloquante, comme cat ou grep sans argument.
// Essayez ctr-\ après avoir lancé une commande bloquante, comme cat ou grep sans argument.
// Essayez ctrI-D après avoir lancé une commande bloquante, comme cat ou grep sans argument.

// @Bonnet2B1
// cat <<l | cat <<b | cat << c>

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
# define CLR_RMV \033[0m
# define RED \033[1;31m
# define GREEN \033[1;32m
# define YELLOW \033[1;33m
# define BLUE \033[1;34m
# define CYAN \033[1;36m
# define MAGENTA \033[1;35m
# define BOLD \033[1m

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
}					t_parsing;

typedef struct s_execution
{
	int				execute;
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
	// exec data
	char			**paths;
	char			*cmd_path;
}					t_shell_memory;

/*================================ FUNCTIONS =================================*/

/* TEMP */
void				print_t_parsing(t_list *lst);
void				print_lst_size(t_list *lst);
void				print_t_exec(t_list *lst);
void				print_tab(char **tab);

/* LIB */
int					ft_tablen(char **tab);
int					ft_atoi(const char *str);
void				tab_print(char **tab);
int					ft_there_is_char(char *str, char c);
int					ft_iswhitespace(char c);
int					ft_isascii(int c);
int					ft_strlen(const char *str);
char				*ft_rmchar(char *str, char c);
char				*ft_strrchr(const char *s, int c);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_substr_free(char *s, unsigned int start, size_t len);
char				*ft_strtrim(const char *s, const char *set);
char				*ft_strchr(const char *s, int c);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstadd_front(t_list **lst, t_list *new);
t_list				*ft_lstnew(void *content);
void				ft_lstadd_here(t_list **lst, t_list *new);
void				ft_lstdel_here(t_list **first, t_list *node_to_delete, void (*del)(void*));
void				ft_lstclear(t_list **lst, void (*del)(void *));
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strjoin_free_s1(char *s1, char *s2);
char				*ft_strjoin_freeall(char *s1, char *s2);
void				*ft_calloc(size_t size, size_t count);
int					ft_isenvchar(int c);
char				**ft_tabadd_back(char **tab, char *new_str);
t_list				*ft_lstfirst(t_list *lst);
char				*ft_strdup(const char *src);
void				ft_putstr_fd(char *s, int fd);
char 				**ft_tabdup(char **tab);
char				**ft_split_w_slash(const char *s, char c);
char				**freetab(char **tab);
void				*ft_memset(void *memory, int c, size_t len);
char				*ft_itoa(int n);
void				ft_lstdelone(t_list *lst, void (*del)(void *));

/* PARSING */
int					is_empty_or_whitespaces(char *str);
void				epure_lst(t_list **lst);
t_exec				*create_execution_node(void);
void				setup_execution_lst(t_shell_memory *data, t_list *parsing_lst);
int					parsing(t_shell_memory *data);
int					quotes_gestion(char **input_line);
void				crazy_split(t_shell_memory *data, char **line);
t_parsing			*create_parsing_node(char *arg);
void				data_init(t_shell_memory *data);
void				env_var_gestion(t_shell_memory *data, char **line);
void				stack_cmd_args(t_shell_memory *data, t_list *lst);
void				*free_parsing_node(t_parsing *node);
void				*free_exec_node(t_exec *node);
void				stake_n_open_files(t_shell_memory *data, t_list *lst);
void				setup_fd(t_shell_memory *data, t_list *exec_lst);
void				print_input_line(char **input_line);
void				rm_quotes(char **line);
int					here_doc_gestion(t_shell_memory *data, t_list *parsing_lst);

/* EXECUTION */
void				execution(t_shell_memory *data);
char				**get_paths(char **env);
void				ft_execve(t_shell_memory *data, char **cmd);
void				close_pipes(t_list *parsing_lst);
char				*find_cmd_path(t_shell_memory *data, char *cmd);
int					find(t_shell_memory *data, char *find, int len);

/* BUILTINS */
int					ft_unset(t_shell_memory *data, t_list *node, char **cmd);
void				ft_env(t_shell_memory *data, char **cmd, char **env);
void				ft_pwd(t_shell_memory *data);
int					ft_cd(t_shell_memory *data, char **args);
void				ft_echo(t_shell_memory *data,char  **args);
int					ft_exit(t_shell_memory *data, char **cmd);
char				**ft_tabdup_join(char **tab);
char				**ft_tabdup_add_nl_free(char **tab, char *str);
int					is_letter(int c);
int					ft_srch(char *s);

/* 0THERS */
void				ft_signal(int i);
void				*freeall(t_shell_memory *data);
void				free_n_exit(t_shell_memory *data, int exit_code);

#endif
