/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:49:54 by edelarbr          #+#    #+#             */
/*   Updated: 2023/09/16 18:11:24 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_node_stuff(t_shell_memory *data, t_exec *exec_node)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("fork"));
	if (pid == 0)
	{
		dup2(exec_node->in_fd, STDIN_FILENO);
		dup2(exec_node->out_fd, STDOUT_FILENO);
		if (exec_node->in_fd > 1)
			close(exec_node->in_fd);
		if (exec_node->out_fd > 1)
			close(exec_node->out_fd);
		close_pipes(data->parsing_lst);
		ft_execve(data, exec_node->cmd);
	}
	waitpid(pid, NULL, 0);
	if (exec_node->in_fd > 1)
		close(exec_node->in_fd);
	if (exec_node->out_fd > 1)
		close(exec_node->out_fd);
}

void	pipex_minishell(t_shell_memory *data, t_list *exec_lst)
{
	while(exec_lst)
	{
		exec_node_stuff(data, exec_lst->content);
		exec_lst = exec_lst->next;
	}
	close_pipes(data->parsing_lst);
}

void	execution(t_shell_memory *data)
{
	data->paths = get_paths(data->env);
	pipex_minishell(data, data->exec_lst);
	data->paths = freetab(data->paths);
}
