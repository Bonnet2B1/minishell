/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 18:40:51 by edelarbr          #+#    #+#             */
/*   Updated: 2023/09/17 00:52:44 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_cmd_path(t_shell_memory *data, char *cmd)
{
	int	i;

	i = -1;
	while (data->paths[++i])
	{
		data->cmd_path = ft_strjoin(data->paths[i], cmd);
		if (access(data->cmd_path, F_OK | X_OK) == 0)
			return (data->cmd_path);
		else if (data->cmd_path)
		{
			free(data->cmd_path);
			data->cmd_path = NULL;
			if (access(cmd, F_OK | X_OK) == 0)
				return (cmd);
		}
	}
	return (NULL);
}

void	ft_execve(t_shell_memory *data, char **cmd)
{
	// if (ft_strcmp(cmd[0], "echo") == 0)
	// 	ft_echo();
	// else if (ft_strcmp(cmd[0], "cd") == 0)
	// 	ft_cd();
	// else if (ft_strcmp(cmd[0], "pwd") == 0)
	// 	ft_pwd();
	// else if (ft_strcmp(cmd[0], "export") == 0)
	// 	ft_export();
	// else if (ft_strcmp(cmd[0], "unset") == 0)
	// 	ft_unset();
	// else if (ft_strcmp(cmd[0], "env") == 0)
	// 	ft_env();
	// else if (ft_strcmp(cmd[0], "exit") == 0)
	// 	ft_exit();
	// else
	if (execve(find_cmd_path(data, cmd[0]), cmd, NULL) == -1)
		perror("execve");
	exit(0);
}
