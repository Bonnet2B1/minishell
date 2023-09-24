/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:49:54 by edelarbr          #+#    #+#             */
/*   Updated: 2023/09/24 21:57:34 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_node_stuff(t_shell_memory *data, t_list *exec_lst)
{
	t_exec *exec_node;
	int		exit_code;

	if (!exec_lst)
		return ;
	exec_node = exec_lst->content;
	exit_code = 0;
	exec_node->pid = fork();
	if (exec_node->pid == -1)
		return (perror("fork"));
	ft_signal(OFF);
	if (exec_node->pid == 0)
	{
		ft_signal(DEFAULT);
		if (dup2(exec_node->in_fd, STDIN_FILENO) == -1
			|| dup2(exec_node->out_fd, STDOUT_FILENO) == -1)
			exit(1);
		if (exec_node->in_fd > 0)
			close(exec_node->in_fd);
		if (exec_node->out_fd > 1)
			close(exec_node->out_fd);
		close_pipes(data->parsing_lst);
		ft_execve(data, exec_node->cmd);
	}
	if (exec_node->in_fd > 0)
		close(exec_node->in_fd);
	if (exec_node->out_fd > 1)
		close(exec_node->out_fd);
	exec_node_stuff(data, exec_lst->next);
	waitpid(exec_node->pid, &exit_code, 0);
	ft_signal(ON);
	data->exit_status = WEXITSTATUS(exit_code);
}

void	execution(t_shell_memory *data)
{
	if (!((t_exec *)data->exec_lst->content)->cmd)
		return ;
	exec_node_stuff(data, data->exec_lst);
	close_pipes(data->parsing_lst);
	// pipex_minishell(data, data->exec_lst);
	data->paths = freetab(data->paths);
}
