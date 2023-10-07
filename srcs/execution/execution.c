/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:49:54 by edelarbr          #+#    #+#             */
/*   Updated: 2023/10/07 20:08:22 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child(t_shell_memory *data, t_exec *exec_node)
{
	ft_signal(DEFAULT);
	if (dup2(exec_node->in_fd, STDIN_FILENO) == -1
		|| dup2(exec_node->out_fd, STDOUT_FILENO) == -1)
		free_n_exit(data, 1);
	if (exec_node->in_fd > 0)
		close(exec_node->in_fd);
	if (exec_node->out_fd > 1)
		close(exec_node->out_fd);
	close_pipes(data->parsing_lst);
	ft_execve(data, exec_node->cmd);
}

void	close_fd(t_exec *exec_node)
{
	if (exec_node->in_fd > 0)
		close(exec_node->in_fd);
	if (exec_node->out_fd > 1)
		close(exec_node->out_fd);
}

void	exec_node_stuff(t_shell_memory *data, t_list *exec_lst)
{
	t_exec	*exec_node;

	if (!exec_lst)
		return ;
	exec_node = exec_lst->content;
	if (exec_node->open_error == 1)
		return (close_fd(exec_node), exec_node_stuff(data, exec_lst->next));
	if (builtins_no_fork_or_fork(data, exec_lst, exec_node->cmd))
		return (close_fd(exec_node), exec_node_stuff(data, exec_lst->next));
	exec_node->pid = fork();
	if (exec_node->pid == -1)
		return (perror("fork"));
	ft_signal(OFF);
	if (exec_node->pid == 0)
		child(data, exec_node);
	close_fd(exec_node);
	exec_node_stuff(data, exec_lst->next);
	if (exec_lst->next == NULL)
	{
		waitpid(exec_node->pid, &data->exit_code, 0);
		data->exit_code = WEXITSTATUS(data->exit_code);
	}
	else
		waitpid(exec_node->pid, NULL, 0);
}

void	execution(t_shell_memory *data)
{
	data->paths = get_paths(data, data->env);
	if (!data->exec_lst || !((t_exec *)data->exec_lst->content)->cmd)
		return ;
	exec_node_stuff(data, data->exec_lst);
	close_pipes(data->parsing_lst);
	ft_signal(ON);
}
