/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:54:21 by gloms             #+#    #+#             */
/*   Updated: 2023/10/04 01:14:28 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find(t_shell_memory *data, char *find, int len)
{
	int	i;

	i = -1;
	while (data->env[++i])
	{
		if (ft_strncmp(data->env[i], find, len) == 0)
			return (i);
	}
	return (-1);
}

int	cd_root(t_shell_memory *data)
{
	int	index_pwd;

	index_pwd = find(data, "PWD=", 4);
	if (chdir("/") == -1)
	{
		perror("cd");
		return (-1);
	}
	free(data->env[index_pwd]);
	data->env[index_pwd] = ft_strjoin("PWD=", getcwd(NULL, 0));
	return (0);
}

int	change_path(t_shell_memory *data, char *args)
{
	char	*pat;
	int		index_pwd;

	index_pwd = find(data, "PWD=", 4);
	pat = ft_strjoin(getcwd(NULL, 0), "/");
	pat = ft_strjoin_free_s1(pat, ft_substr(args, 0, ft_strlen(args)));
	if (chdir(pat) == -1)
	{
		perror("cd");
		return (-1);
	}
	free(data->env[index_pwd]);
	data->env[index_pwd] = ft_strjoin("PWD=", getcwd(NULL, 0));
	free(pat);
	return (0);
}

int	cd_home(t_shell_memory *data)
{
	char	*home;
	int		len;
	int		index_home;

	index_home = find(data, "HOME=", 5);
	len = ft_strlen(data->env[index_home]);
	home = ft_substr(data->env[index_home], 5, len - 5);
	if (!home)
	{
		printf("minishell: cd: HOME not set\n");
		return (-1);
	}
	if (chdir(home) == -1)
	{
		perror("cd");
		return (-1);
	}
	free(data->env[index_home]);
	data->env[index_home] = ft_strjoin("PWD=", getcwd(NULL, 0));
	free(home);
	return (0);
}

int	ft_cd(t_shell_memory *data, char **args)
{
	int		ind;
	char	*tmp;

	((void)0, tmp = getcwd(NULL, 0), ind = find(data, "OLDPWD=", 7));
	if (args[1])
	{
		if (!ft_strncmp(args[1], "~", 1))
		{
			args[1] = ft_substr(args[1], 1, ft_strlen(args[1]) - 1);
			if (cd_home(data) < 0)
				return (1);
		}
		else if (!ft_strncmp(args[1], "/", 1))
		{
			args[1] = ft_substr(args[1], 1, ft_strlen(args[1]) - 1);
			if (cd_root(data) < 0)
				return (1);
		}
		change_path(data, args[1]);
	}
	else
		cd_home(data);
	data->env[ind] = ft_strjoin(ft_substr_free(data->env[ind], 0, 7), tmp);
	free(tmp);
	return (0);
}
