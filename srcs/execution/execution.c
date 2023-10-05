/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:49:54 by edelarbr          #+#    #+#             */
/*   Updated: 2023/10/05 02:11:15 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtins_no_fork(t_shell_memory *data, t_list *node, char **cmd)
{
	if (ft_strcmp(cmd[0], "cd") == 0)
	{
		data->exit_code = ft_cd(data, cmd);
		return (1);
	}
	else if (ft_strcmp(cmd[0], "unset") == 0)
	{
		data->exit_code = ft_unset(data, node, cmd);
		return (1);
	}
	else if (ft_strcmp(cmd[0], "export") == 0 && cmd[1])
	{
		data->exit_code = ft_export(data, cmd);
		return (1);
	}
	else if (ft_strcmp(cmd[0], "exit") == 0)
	{
		data->exit_code = ft_exit(data, cmd);
		return (1);
	}
	return (0);
}

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
	int		exit_code;

	if (!exec_lst)
		return ;
	exec_node = exec_lst->content;
	if (exec_node->execute == 0)
		return (data->exit_code = 1, exec_node_stuff(data, exec_lst->next));
	if (builtins_no_fork(data, exec_lst, exec_node->cmd))
		return (exec_node_stuff(data, exec_lst->next));
	exec_node->pid = fork();
	if (exec_node->pid == -1)
		return (perror("fork"));
	ft_signal(OFF);
	if (exec_node->pid == 0)
		child(data, exec_node);
	close_fd(exec_node);
	exec_node_stuff(data, exec_lst->next);
	close_pipes(data->parsing_lst);
	exit_code = 0;
	waitpid(exec_node->pid, &exit_code, 0);
	if (exec_lst->next == NULL)
		data->exit_code = WEXITSTATUS(exit_code);
	ft_signal(ON);
}

void	execution(t_shell_memory *data)
{
	data->paths = get_paths(data, data->env);
	if (!((t_exec *)data->exec_lst->content)->cmd)
		return ;
	exec_node_stuff(data, data->exec_lst);
}
