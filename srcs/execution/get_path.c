/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 17:25:39 by edelarbr          #+#    #+#             */
/*   Updated: 2023/10/06 01:03:28 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_paths(t_shell_memory *data, char **env)
{
	int		i;
	char	**path;

	i = find(data, "PATH=", 5);
	if (i == -1)
		return (NULL);
	path = ft_split_w_slash(data, env[i] + 5, ':');
	return (path);
}

// char	**get_paths(t_shell_memory *data, char **env)
// {
// 	int		i;
// 	char	**path;

// 	i = -1;
// 	path = NULL;
// 	while (env && env[++i])
// 	{
// 		if (ft_strncmp(env[i], "PATH=", 5) == 0)
// 			path = ft_split_w_slash(data, env[i] + 5, ':');
// 	}
// 	return (path);
// }
