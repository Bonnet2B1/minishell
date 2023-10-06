/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:54:21 by gloms             #+#    #+#             */
/*   Updated: 2023/10/06 01:58:18 by edelarbr         ###   ########.fr       */
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
	int		index_pwd;
	char	*path;

	index_pwd = find(data, "PWD=", 4);
	if (chdir("/") == -1)
	{
		perror("minishell: cd: ");
		return (-1);
	}
	path = getcwd(NULL, 0);
	data->env[index_pwd] = ft_strjoin(data, "PWD=", path);
	free(path);
	return (0);
}

int	change_path(t_shell_memory *data, char *args)
{
	char	*pat;
	int		index_pwd;
	char	*path;

	index_pwd = find(data, "PWD=", 4);
	path = getcwd(NULL, 0);
	pat = ft_strjoin(data, path, "/");
	free(path);
	pat = ft_strjoin(data, pat, ft_substr(data, args, 0, ft_strlen(args)));
	if (chdir(pat) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(args, 2);
		ft_putstr_fd(": ", 2);
		perror(NULL);
		return (-1);
	}
	path = getcwd(NULL, 0);
	data->env[index_pwd] = ft_strjoin(data, "PWD=", path);
	free(path);
	return (0);
}

int	cd_home(t_shell_memory *data, char *str)
{
	char	*home;
	int		len;
	int		index_home;
	int		index_pwd;
	char	*path;

	index_home = find(data, "HOME=", 5);
	len = ft_strlen(data->env[index_home]);
	home = ft_substr(data, data->env[index_home], 5, len - 5);
	if (!home)
		return (print_error("cd", "HOME not set"), -1);
	if (chdir(home) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
		perror(NULL);
		return (-1);
	}
	index_pwd = find(data, "PWD=", 4);
	path = getcwd(NULL, 0);
	data->env[index_pwd] = ft_strjoin(data, "PWD=", path);
	free(path);
	return (0);
}

int	ft_cd(t_shell_memory *data, char **args)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	if (args[1])
	{
		if (!ft_strncmp(args[1], "~", 1))
		{
			args[1] = ft_substr(data, args[1], 1, ft_strlen(args[1]) - 1);
			if (cd_home(data, args[1]) < 0)
				return (1);
		}
		else if (!ft_strncmp(args[1], "/", 1))
		{
			args[1] = ft_substr(data, args[1], 1, ft_strlen(args[1]) - 1);
			if (cd_root(data) < 0)
				return (1);
		}
		change_path(data, args[1]);
	}
	else
		cd_home(data, args[1]);
	data->env[find(data, "OLDPWD=", 7)] = ft_strjoin(data, ft_substr(
				data, data->env[find(data, "OLDPWD=", 7)], 0, 7), tmp);
	free(tmp);
	return (0);
}
