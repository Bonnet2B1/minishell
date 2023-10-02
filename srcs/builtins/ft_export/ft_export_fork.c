/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_fork.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloms <rbrendle@student.42mulhouse.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 18:58:26 by gloms             #+#    #+#             */
/*   Updated: 2023/10/02 23:55:14 by gloms            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

char	**ft_tabdup_join(char **tab)
{
	int i;
	char **new_tab;

	i = 0;
	while (tab[i])
		i++;
	new_tab = malloc(sizeof(char *) * (i + 1));
	if (!new_tab)
		return (perror("Malloc"), NULL);
	i = 0;
	while (tab[i])
	{
		new_tab[i] = ft_strjoin("declare -x ", tab[i]);
		i++;
	}
	new_tab[i] = NULL;
	return (new_tab);
}

char	**ft_tabdup_add_nl_free(char **tab, char *str)
{
	int i;
	char **new_tab;

	i = 0;
	while (tab[i])
		i++;
	new_tab = malloc(sizeof(char *) * (i + 2));
	if (!new_tab)
		return (perror("Malloc"), NULL);
	i = 0;
	while (tab[i])
	{
		new_tab[i] = ft_strdup(tab[i]);
		i++;
	}
	new_tab[i] = ft_strdup(str);
	new_tab[i + 1] = NULL;
	freetab(tab);
	return (new_tab);
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
				swap_str((*tab) + i, (*tab) + i + 1, 0);
		}
		i = -1;
	}
}

int	ft_export_fork(t_shell_memory *data)
{
	char	**declare_x;

	declare_x = ft_tabdup_join(data->env);
	sort_tab(&declare_x);
	tab_print(declare_x);
	freetab(declare_x);
	return (0);
}
