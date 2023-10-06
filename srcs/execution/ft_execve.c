/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 18:40:51 by edelarbr          #+#    #+#             */
/*   Updated: 2023/10/06 19:24:44 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_cmd_path(t_shell_memory *data, char *cmd)
{
	int	i;

	i = -1;
	while (data->paths && data->paths[++i])
	{
		data->cmd_path = ft_strjoin(data, data->paths[i], cmd);
		if (access(data->cmd_path, F_OK | X_OK) == 0)
			return (data->cmd_path);
	}
	if (access(cmd, F_OK | X_OK) == 0)
	{
		if (data->cmd_path)
			data->cmd_path = NULL;
		return (cmd);
	}
	return (NULL);
}

void	error_gestion(t_shell_memory *data, char **cmd)
{
	if (ft_there_is_char(cmd[0], '/') && opendir(cmd[0]))
		return (printf("minishell: %s: is a directory\n", cmd[0]),
			free_n_exit(data, 126));
	if (ft_there_is_char(cmd[0], '/') && access(cmd[0], F_OK) != 0)
		return (printf("minishell: %s: No such file or directory\n", cmd[0]),
			free_n_exit(data, 127));
	if (ft_there_is_char(cmd[0], '/') && access(cmd[0], X_OK) != 0)
		return (printf("minishell: %s: Permissions denied\n", cmd[0]),
			free_n_exit(data, 126));
}

void	ft_execve(t_shell_memory *data, char **cmd)
{
	char	*cmd_path;

	error_gestion(data, cmd);
	if (ft_strcmp(cmd[0], "echo") == 0)
		ft_echo(data, cmd);
	else if (ft_strcmp(cmd[0], "export") == 0 && cmd[1] == NULL)
		free_n_exit(data, ft_export_fork(data));
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		ft_pwd(data);
	else if (ft_strcmp(cmd[0], "env") == 0)
		ft_env(data, cmd, data->env);
	else
	{
		cmd_path = ft_strdup(data, find_cmd_path(data, cmd[0]));
		if (cmd_path == NULL && data->paths == NULL)
		{
			printf("minishell: %s: No such file or directory\n", cmd[0]);
			free_n_exit(data, 127);
		}
		if (execve(cmd_path, cmd, data->env) == -1)
		{
			printf("minishell: %s: command not found\n", cmd[0]);
			free_n_exit(data, 127);
		}
	}
}
