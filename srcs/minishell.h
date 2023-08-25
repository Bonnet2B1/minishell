/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 20:38:43 by edelarbr          #+#    #+#             */
/*   Updated: 2023/08/25 01:48:01 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*PARSING*/

// - gerer le heredoc avant le parsing puis le transformer en fichier temporaire
// - et l'envoyer dans l'ast ("<<" -> "< [nom du fichier temporaire]")

// - split aux 5 opérateurs (|, <, <<, >, >>) et aux whitespaces (on enleve les
// - whitespaces mais pas les operateurs)

// - Si besoin, swap les arguments autour de "<", ">" et ">>"

// - (ez) join tout ce qui est entre deux operateurs (en mettant des espaces)
// - ou alors (pa ez) faire un char ***tab avec une succesion de tableau
// - (**tab arg, **tab op, **tab arg, **tab op,...)

/*AST*/

// - mettre tous les operateurs successivement à droite de la node
// - remonter au top de l'arbre et mettre les arguments à gauche de la node
// - si on arrive à la fin de la ligne, on met le dernier argument à droite

/*EXEC*/

// - aller tout à droite, faire les liens (fusion de fd) entre les cotes d'une
// - meme node

// - monter d'un étage et reproduire le premier point

// - faire ces deux points là jusqu'à arriver au top de l'arbre

// - executer de gauche a droite

// - (ez minishell).

/*---------------------------REGLES DE COLLABORATION--------------------------*/

// ! mettre les fichiers de fonctions générales dans srcs/libs/

// ! mettre les fichiers de fonctions spécifiques au focntionnement de minishell
// ! dans srcs/utils/

/*-----------------------TRUCS A CHECKER AVANT LA FIN-------------------------*/

// - est-ce que mettre tous les whitespaces dans comme separateur dans split

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

enum						e_token
{
	PIPE,
	COMMAND,
	REDIR_IN,
	REDIR_APPEND,
	REDIR_OUT,
};

typedef struct s_pipe
{
	int						pipe_fd[2];
	struct s_cmd			*pipe_in;
	struct s_cmd			*pipe_out;
}							t_pipe;

typedef struct s_file
{
	int						fd;
	char					*file_name;
	int						fd_in;
	int						fd_out;
}							t_file;
typedef struct s_cmd
{
	char					**cmd;
	struct s_pipe			in_pipe;
	struct s_file			in_file;
	struct s_pipe			out_pipe;
	struct s_file			out_file;
}							t_cmd;

// typedef struct s_node
// {
// 	struct s_node			*prev;
// 	enum e_token			type;
// 	char					*cmd_line_split;
// 	struct s_node			*right;
// 	struct s_node			*left;
// }							t_node;


typedef struct s_shell_memory
{
	char					**ev;
	char					**history;
	char					*cmd_line;

	struct s_current_cmd	*current_cmd;
}							t_shell_memory;

// typedef struct s_current_cmd
// {
// 	char					**cmd_line_split;
// 	t_node					*first_node;
// }							t_current_cmd;

/*----------------------------------FUNCTIONS---------------------------------*/

/* TEMP */
void						print_ast(t_shell_memory *data);

/* LIB */
char						**ft_split_white_space(char const *s);
int							ft_iswhitespace(char c);
int							ft_strlen(const char *str);
char						*ft_rmchar(char *str, char c);
char						*ft_strrchr(const char *s, int c);
char						*ft_substr(char const *s, unsigned int start,
								size_t len);
char						*ft_strtrim(const char *s, const char *set);
char						*ft_strchr(const char *s, int c);

/* UTILS */
void						current_cmd_init(t_shell_memory *data);
void						ast(t_shell_memory *data);
void						current_cmd_init(t_shell_memory *data);

#endif
