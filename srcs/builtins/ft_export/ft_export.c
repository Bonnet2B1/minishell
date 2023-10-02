/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloms <rbrendle@student.42mulhouse.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 21:04:52 by gloms             #+#    #+#             */
/*   Updated: 2023/10/01 17:55:12 by gloms            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//- traiter les arguments
//- ajouter les arguments dans l'env mais ne pas les afficher si ils sont pas setup

int	lentab(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

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
	if (lentab(*tab) <= 1)
		return ;
	while (!check_tab(*tab))
	{
		while ((*tab)[++i] && i < lentab(*tab) - 1)
		{
			if (ft_strcmp((*tab)[i], (*tab)[i + 1]) > 0)
				swap_str((*tab) + i, (*tab) + i + 1);
		}
		i = -1;
	}
}
//! char **tab -> t_shell_memory *data
int	ft_export(char **tab, char **args)
{
	//int		i;
	char	**declare_x;

	if (args[1] && (!is_letter(args[1][0]) || !ft_srch(args[1])))
	{
		printf("bash: export: `%s': not a valid identifier", args[1]);
		return (1);
	}
	declare_x = ft_tabdup_join(tab);
	sort_tab(&declare_x);
	if (!args[1])
		tab_print(declare_x);
	else
	{
		tab = ft_tabdup_add_nl_free(tab, args[1]);
		tab_print(tab);
	}
	freetab(declare_x);
	return (0);
}

int main(int ac, char **av, char **env)
{
	char **tab;
	char **args;

	(void)ac;
	(void)av;
	args = malloc(sizeof(char *) * 3);
	args[0] = "export";
	args[1] = "PILPIII=123456ab6";
	args[2] = NULL;
	tab = ft_tabdup(env);
	ft_export(tab, args);

}
