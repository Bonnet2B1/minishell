/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_fork.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 18:58:26 by gloms             #+#    #+#             */
/*   Updated: 2023/10/05 01:56:04 by edelarbr         ###   ########.fr       */
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

char	**ft_tabdup_join(t_shell_memory *data, char **tab)
{
	int		i;
	char	**new_tab;

	i = 0;
	while (tab[i])
		i++;
	new_tab = calloc_tuning(&data->malloc_chain, sizeof(char *) * (i + 1));
	if (!new_tab)
		return (perror("Malloc"), NULL);
	i = 0;
	while (tab[i])
	{
		new_tab[i] = ft_strjoin_putkot(data, "declare -x ", tab[i]);
		i++;
	}
	new_tab[i] = NULL;
	return (new_tab);
}

char	**ft_tabdup_add_nl(t_shell_memory *data, char **tab, char *str)
{
	int		i;
	char	**new_tab;

	i = 0;
	while (tab[i])
		i++;
	new_tab = calloc_tuning(&data->malloc_chain, sizeof(char *) * (i + 2));
	if (!new_tab)
		return (perror("Malloc"), NULL);
	i = 0;
	while (tab[i])
	{
		new_tab[i] = ft_strdup(data, tab[i]);
		i++;
	}
	new_tab[i] = ft_strdup(data, str);
	new_tab[i + 1] = NULL;
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
				swap_str((*tab) + i, (*tab) + i + 1);
		}
		i = -1;
	}
}

int	ft_export_fork(t_shell_memory *data)
{
	char	**declare_x;

	declare_x = ft_tabdup_join(data, data->env);
	sort_tab(&declare_x);
	tab_print(declare_x);
	return (0);
}
