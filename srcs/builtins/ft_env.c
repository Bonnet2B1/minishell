/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 17:43:35 by edelarbr          #+#    #+#             */
/*   Updated: 2023/09/26 17:21:53 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_shell_memory *data, char **cmd, char **env)
{
	int	i;

	i = 0;
	while (cmd[++i])
	{
		if (cmd[i][ft_strlen(cmd[i]) - 1] == '/')
			return (printf("env: %s: Not a directory\n", cmd[i]), ft_exit(data, 126));
		if (ft_there_is_char(cmd[i], '/') && opendir(cmd[i]))
			return (printf("env: %s: Permission denied\n", cmd[i]), ft_exit(data, 126));
		else
			return (printf("env: %s: No such file or directory\n", cmd[i]), ft_exit(data, 127));
	}
	i = -1;
	while (env[++i])
		printf("%s\n", env[i]);
	ft_exit(data, 0);
}
