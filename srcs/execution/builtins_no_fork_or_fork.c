/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_no_fork_or_fork.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 19:23:28 by edelarbr          #+#    #+#             */
/*   Updated: 2023/10/07 20:22:42 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	need_to_exec(t_shell_memory *data, char *cmd_name)
{
	t_exec	*node;

	node = data->exec_lst->content;
	if (node->execute == 1 && node->cmd
		&& ft_strncmp(node->cmd[0], cmd_name, ft_strlen(cmd_name)) == 0
		&& data->exec_lst->next == NULL && data->exec_lst->prev == NULL)
		return (1);
	else
		return (0);
}

int	builtins_no_fork(t_shell_memory *data, t_list *node, char **cmd)
{
	if (ft_strcmp(cmd[0], "cd") == 0 && node->next == NULL)
		return (data->exit_code = ft_cd(data, cmd), 1);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		return (ft_cd(data, cmd), 1);
	else if (ft_strcmp(cmd[0], "unset") == 0 && node->next == NULL)
		return (data->exit_code = ft_unset(data, node, cmd), 1);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		return (ft_unset(data, node, cmd), 1);
	else if (ft_strcmp(cmd[0], "export") == 0 && cmd[1] && node->next == NULL)
		return (data->exit_code = ft_export(data, cmd), 1);
	else if (ft_strcmp(cmd[0], "export") == 0 && cmd[1])
		return (ft_export(data, cmd), 1);
	else if (ft_strcmp(cmd[0], "exit") == 0 && node->next == NULL)
		return (data->exit_code = ft_exit(data, cmd), 1);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		return (ft_exit(data, cmd), 1);
	return (0);
}

int	builtins_no_fork_or_fork(t_shell_memory *data, t_list *node, char **cmd)
{
	pid_t	pid;

	if ((ft_strcmp(cmd[0], "cd") == 0 || ft_strcmp(cmd[0], "unset") == 0
			|| (ft_strcmp(cmd[0], "export") == 0 && cmd[1])
			|| ft_strcmp(cmd[0], "exit") == 0) && !need_to_exec(data, cmd[0]))
	{
		pid = fork();
		if (pid == -1)
			return (perror("fork"), 1);
		if (pid == 0)
		{
			builtins_no_fork(data, node, cmd);
			free_n_exit(data, data->exit_code);
		}
		if (node->next == NULL)
		{
			waitpid(((t_exec *)node->content)->pid, &data->exit_code, 0);
			data->exit_code = WEXITSTATUS(data->exit_code);
		}
		else
			waitpid(((t_exec *)node->content)->pid, NULL, 0);
		return (1);
	}
	else
		return (builtins_no_fork(data, node, cmd));
}
