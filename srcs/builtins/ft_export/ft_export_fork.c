/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_fork.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 18:58:26 by gloms             #+#    #+#             */
/*   Updated: 2023/10/06 19:46:04 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*copy_w_quotes(t_shell_memory *data, char *str)
{
	char	*copy;
	int		i;
	int		j;

	if (!strchr(str, '='))
		return (ft_strdup(data, str));
	copy = calloc_tuning(&data->malloc_chain,
			sizeof(char) * (ft_strlen(str) + 3));
	if (!copy)
		return (perror("malloc"), NULL);
	i = 0;
	j = 0;
	while (str[i] && str[i] != '=')
		copy[j++] = str[i++];
	if (str[i] == '=')
	{
		copy[j++] = str[i++];
		copy[j++] = '"';
	}
	while (str[i])
		copy[j++] = str[i++];
	copy[j++] = '"';
	copy[j] = '\0';
	return (copy);
}

char	**create_declare_x(t_shell_memory *data, char **env)
{
	char	**new;
	int		i;
	int		_;

	_ = find(data, "_=", 2);
	new = calloc_tuning(&data->malloc_chain,
			sizeof(char *) * (ft_tablen(env) + 1));
	if (!new)
		return (perror("malloc"), NULL);
	i = -1;
	while (env[++i])
	{
		if (i == _)
			continue ;
		new[i] = ft_strjoin(data, new[i], "declare -x ");
		new[i] = ft_strjoin(data, new[i], copy_w_quotes(data, env[i]));
	}
	return (new);
}

int	check_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i + 1])
	{
		if (ft_strcmp(tab[i], tab[i + 1]) > 0)
			return (0);
		i++;
	}
	return (1);
}

void	sort_tab(char ***tab)
{
	int	i;

	i = -1;
	if (ft_tablen(*tab) <= 1)
		return ;
	while (!check_tab(*tab))
	{
		while ((*tab)[++i] && i < ft_tablen(*tab) - 1)
		{
			if (ft_strcmp((*tab)[i], (*tab)[i + 1]) > 0)
				swap_str((*tab) + i, (*tab) + i + 1);
		}
		i = -1;
	}
}

int	ft_export_fork(t_shell_memory *data)
{
	char	**declare_x;

	declare_x = create_declare_x(data, data->env);
	sort_tab(&declare_x);
	tab_print(declare_x);
	return (0);
}
