/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 17:43:35 by edelarbr          #+#    #+#             */
/*   Updated: 2023/09/23 18:06:06 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(char **cmd, char **env)
{
	int	i;

	i = 0;
	while (cmd[++i])
	{
		if (cmd[i][ft_strlen(cmd[i]) - 1] == '/')
			return (printf("env: %s: Not a directory\n", cmd[i]), exit(126));
		if (ft_there_is_char(cmd[i], '/') && opendir(cmd[i]))
			return (printf("env: %s: Permission denied\n", cmd[i]), exit(126));
		else
			return (printf("env: %s: No such file or directory\n", cmd[i]), exit(127));
	}
	i = -1;
	while (env[++i])
		printf("%s\n", env[i]);
	exit(0);
}
