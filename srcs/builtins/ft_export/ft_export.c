/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 21:04:52 by gloms             #+#    #+#             */
/*   Updated: 2023/10/02 18:30:52 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//- traiter les arguments
//- ajouter les arguments dans l'env mais ne pas les afficher si ils sont pas setup

void	swap_str(char **s1, char **s2)
{
	char *temp;

	temp = *s1;
	*s1 = *s2;
	*s2 = temp;
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

int	ft_export(t_shell_memory *data, char **args)
{
	char	**declare_x;

	if (args[1] && (!is_letter(args[1][0]) || !ft_srch(args[1])))
	{
		printf("minishell: export: `%s': not a valid identifier", args[1]);
		return (1);
	}
	declare_x = ft_tabdup_join(data->env);
	sort_tab(&declare_x);
	if (!args[1])
		tab_print(declare_x);
	else
	{
		data->env = ft_tabdup_add_nl_free(data->env, args[1]);
		tab_print(data->env);
	}
	freetab(declare_x);
	return (0);
}
