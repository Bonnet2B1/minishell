/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_gestion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 18:55:33 by edelarbr          #+#    #+#             */
/*   Updated: 2023/09/30 00:34:17 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	rewind_line(t_shell_memory *data)
{
	pid_t	pid;
	char 	*cmd[5];

	pid = fork();
	if (pid == 0)
	{
		cmd[0] = "tput";
		cmd[1] = "-T";
		cmd[2] = "xterm";
		cmd[3] = "cuu1";
		cmd[4] = NULL;
		execve(find_cmd_path(data, cmd[0]), cmd, NULL);
	}
	waitpid(pid, NULL, 0);
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
		if (!str_is_here_doc_char(delimiter))
			return (free_n_exit(data, 258));
		ft_signal(SIG_HERE_DOC);
		while (1)
		{
			line = readline("> ");
			if (!line)
				return (rewind_line(data), printf("> "), free_n_exit(data, 0));
			if (!ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1))
				return (free(line), free_n_exit(data, 0));
			line = ft_strjoin_free_s1(line, "\n");
			ft_putstr_fd(line, fd);
			free(line);
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
