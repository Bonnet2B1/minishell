/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_gestion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 18:55:33 by edelarbr          #+#    #+#             */
/*   Updated: 2023/09/23 17:13:27 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	here_doc_gestion(t_shell_memory *data, t_list *parsing_lst)
{
	t_parsing	*node;

	(void)data;
	while (parsing_lst)
	{
		node = parsing_lst->content;
		if (node->token == HERE_DOC)
		{
			pipe(node->pipe_fd);
			fill_here_doc(node->pipe_fd[INPIPE], node->arg);
			close(node->pipe_fd[INPIPE]);
			node->token = REDIR_IN;
			node->file_fd = node->pipe_fd[OUTPIPE];
		}
		parsing_lst = parsing_lst->next;
	}
}
