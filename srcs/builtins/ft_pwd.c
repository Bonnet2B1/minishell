/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:03:15 by gloms             #+#    #+#             */
/*   Updated: 2023/09/26 18:19:25 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(t_shell_memory *data)
{
	char	*path;

	path = getcwd(NULL, 0);
	printf("%s\n", data->env[find(data, "PWD=", 4)]);
	if (!path)
	{
		perror("pwd");
		ft_exit(data, -1);
	}
	printf("%s\n", path);
	free(path);
	ft_exit(data, 0);
}
