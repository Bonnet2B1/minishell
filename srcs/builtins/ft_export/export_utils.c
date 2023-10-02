/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloms <rbrendle@student.42mulhouse.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 21:52:56 by gloms             #+#    #+#             */
/*   Updated: 2023/10/02 18:50:14 by gloms            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_letter(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}
int	is_valid(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else if ((c >= '0' && c <= '9') || c == '=')
		return (1);
	return (0);
}

int	ft_srch(char *s)
{
	int	i;
	int eq;

	eq = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '=' && eq == 0)
		{
			eq = 1;
			i++;
		}
		if (!is_valid(s[i]) && eq == 0)
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

void	tab_print(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		printf("%s\n", tab[i]);
}
