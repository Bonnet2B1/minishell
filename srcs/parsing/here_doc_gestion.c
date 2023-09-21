/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_gestion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 18:55:33 by edelarbr          #+#    #+#             */
/*   Updated: 2023/09/21 23:29:06 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_name(t_shell_memory *data, t_list *parsing_lst)
{
	t_parsing	*node;
	char		*name;

	name = ft_strdup(".here_doc");
	while (parsing_lst)
	{
		node = parsing_lst->content;
		if ((node->token == REDIR_IN
			|| node->token == REDIR_APPEND
			|| node->token == HERE_DOC
			|| node->token == REDIR_OUT)
			&& (!ft_strncmp(name, node->arg, ft_strlen(name) + 1)
			|| access(name, F_OK) == 0))
		{
			name = ft_strjoin_free_s1(name, "_");
			parsing_lst = data->parsing_lst;
		}
		parsing_lst = parsing_lst->next;
	}
	return (name);
}

void	fill_here_doc(int fd, char *delimiter)
{
	char	*line;

	// - desactiver les signaux
	// - activer les signaux here_doc
	while (1)
	{
		line = readline("> ");
		if (!ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1))
			return (free(line));
		line = ft_strjoin_free_s1(line, "\n");
		ft_putstr_fd(line, fd);
		free(line);
	}
	// - desactiver les signaux here_doc
	// - activer les signaux
}

char	*get_full_path(char *name)
{
	char	*path;

	path = getcwd(NULL, 0);
	path = ft_strjoin_free_s1(path, "/");
	path = ft_strjoin_freeall(path, name);
	return (path);
}

void	here_doc_gestion(t_shell_memory *data, t_list *parsing_lst)
{
	t_parsing	*node;
	char		*name;

	while (parsing_lst)
	{
		node = parsing_lst->content;
		if (node->token == HERE_DOC)
		{
			name = find_name(data, parsing_lst);
			node->file_fd = open(name ,O_RDWR | O_CREAT | O_TRUNC, 0644);
			fill_here_doc(node->file_fd, node->arg);
			close(node->file_fd);
			node->token = REDIR_IN;
			node->arg = get_full_path(name);
			node->to_unlink = 1;
			node->file_fd = open(node->arg, O_RDONLY);
		}
		parsing_lst = parsing_lst->next;
	}
}
