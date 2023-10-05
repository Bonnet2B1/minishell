/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_gestion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 18:55:33 by edelarbr          #+#    #+#             */
/*   Updated: 2023/10/05 22:01:04 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_hd(t_shell_memory *data, char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = -1;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	str = ft_calloc(data, (ft_strlen(s1) + ft_strlen(s2)) + 1, sizeof(char));
	if (!str)
		return (NULL);
	while (s1[++i])
		str[i] = s1[i];
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}

int	str_is_here_doc_char(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '<' || str[i] == '>' || str[i] == '|')
			return (0);
	}
	return (1);
}

void	fill_here_doc(t_shell_memory *data, int fd, char *delimiter)
{
	pid_t	pid;
	char	*line;

	(void)data;
	ft_signal(OFF);
	pid = fork();
	if (pid == 0)
	{
		ft_signal(SIG_HERE_DOC);
		if (!str_is_here_doc_char(delimiter))
			return (free_n_exit(data, 258));
		while (1)
		{
			line = readline("> ");
			if (!line)
				return (printf("\033[1A\033[2Cexit\n"), free_n_exit(data, 0));
			if (!ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1))
				return (free(line), free_n_exit(data, 0));
			line = ft_strjoin_hd(data, line, "\n");
			ft_putstr_fd(line, fd);
		}
}
	waitpid(pid, 0, 0);
	ft_signal(ON);
}

int	here_doc_gestion(t_shell_memory *data, t_list *parsing_lst)
{
	t_parsing	*node;

	(void)data;
	while (parsing_lst)
	{
		node = parsing_lst->content;
		if (node->token == HERE_DOC)
		{
			pipe(node->pipe_fd);
			fill_here_doc(data, node->pipe_fd[INPIPE], node->arg);
			close(node->pipe_fd[INPIPE]);
			node->token = REDIR_IN;
			node->file_fd = node->pipe_fd[OUTPIPE];
			if (!str_is_here_doc_char(node->arg))
				return (0);
		}
		parsing_lst = parsing_lst->next;
	}
	return (1);
}
